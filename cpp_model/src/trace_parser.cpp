#include "trace_parser.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// ============================================================
// Parse complete trace file
// ============================================================

bool TraceParser::parseFile(
    const std::string& filename,
    std::vector<Commit>& commits
)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr
            << "ERROR: Cannot open trace file: "
            << filename
            << '\n';

        return false;
    }

    commits.clear();

    std::string line;
    std::size_t lineNumber = 0;

    while (std::getline(file, line)) {

        ++lineNumber;

        // Ignore everything except COMMIT records.
        if (line.find("COMMIT") == std::string::npos) {
            continue;
        }

        Commit commit{};

        if (!parseLine(line, commit)) {

            std::cerr
                << "ERROR: Invalid COMMIT record at "
                << filename
                << ':'
                << lineNumber
                << '\n'
                << "       "
                << line
                << '\n';

            return false;
        }

        commits.push_back(commit);
    }

    if (commits.empty()) {

        std::cerr
            << "ERROR: No COMMIT records found in "
            << filename
            << '\n';

        return false;
    }

    return true;
}


// ============================================================
// Parse one COMMIT line
// ============================================================

bool TraceParser::parseLine(
    const std::string& line,
    Commit& commit
)
{
    // --------------------------------------------------------
    // Must actually be a COMMIT record
    // --------------------------------------------------------

    if (line.find("COMMIT") == std::string::npos) {
        return false;
    }

    commit = Commit{};

    std::string field;


    // ========================================================
    // Required field: PC
    // ========================================================

    if (!extractField(line, "PC", field)) {
        return false;
    }

    if (!parseHex32(field, commit.pc)) {
        return false;
    }


    // ========================================================
    // Required field: INSTR
    // ========================================================

    if (!extractField(line, "INSTR", field)) {
        return false;
    }

    if (!parseHex32(field, commit.instruction)) {
        return false;
    }


    // ========================================================
    // Optional register write
    // ========================================================

    std::string rdField;
    std::string valueField;

    const bool hasRD =
        extractField(line, "RD", rdField);

    const bool hasValue =
        extractField(line, "VALUE", valueField);

    // RD and VALUE must appear together.
    if (hasRD != hasValue) {
        return false;
    }

    if (hasRD) {

        // Allow:
        //
        // RD=-
        // VALUE=-
        //
        // for instructions without register writes.

        if (rdField == "-" &&
            valueField == "-") {

            commit.regWrite = false;
        }
        else {

            if (rdField == "-" ||
                valueField == "-") {
                return false;
            }

            if (!parseRegister(
                    rdField,
                    commit.rd
                )) {
                return false;
            }

            if (!parseHex32(
                    valueField,
                    commit.rdValue
                )) {
                return false;
            }

            commit.regWrite = true;
        }
    }


    // ========================================================
    // Optional memory write
    // ========================================================

    std::string memAddressField;
    std::string memValueField;
    std::string memSizeField;

    const bool hasMemAddress =
        extractField(
            line,
            "MEM_ADDR",
            memAddressField
        );

    const bool hasMemValue =
        extractField(
            line,
            "MEM_VALUE",
            memValueField
        );

    const bool hasMemSize =
        extractField(
            line,
            "MEM_SIZE",
            memSizeField
        );

    // All memory fields must appear together.
    if (
        hasMemAddress ||
        hasMemValue ||
        hasMemSize
    ) {

        if (
            !hasMemAddress ||
            !hasMemValue ||
            !hasMemSize
        ) {
            return false;
        }

        if (!parseHex32(
                memAddressField,
                commit.memAddress
            )) {
            return false;
        }

        if (!parseHex32(
                memValueField,
                commit.memValue
            )) {
            return false;
        }


        // ----------------------------------------------------
        // MEM_SIZE is decimal
        // ----------------------------------------------------

        try {

            std::size_t position = 0;

            const unsigned long size =
                std::stoul(
                    memSizeField,
                    &position,
                    10
                );

            if (position != memSizeField.size()) {
                return false;
            }

            if (
                size != 1 &&
                size != 2 &&
                size != 4
            ) {
                return false;
            }

            commit.memWriteSize =
                static_cast<uint8_t>(size);
        }
        catch (...) {
            return false;
        }

        commit.memWrite = true;
    }


    // ========================================================
    // Optional NEXT_PC
    // ========================================================

    if (extractField(
            line,
            "NEXT_PC",
            field
        )) {

        if (!parseHex32(
                field,
                commit.nextPC
            )) {
            return false;
        }
    }
    else {

        // If the trace does not explicitly contain NEXT_PC,
        // leave it at zero.
        //
        // We will initially compare PC / instruction /
        // architectural side effects and can make NEXT_PC
        // mandatory later.
        commit.nextPC = 0;
    }


    commit.valid = true;

    return true;
}


// ============================================================
// Extract KEY=value
// ============================================================

bool TraceParser::extractField(
    const std::string& line,
    const std::string& key,
    std::string& value
)
{
    const std::string token =
        key + "=";

    const std::size_t start =
        line.find(token);

    if (start == std::string::npos) {
        return false;
    }

    std::size_t valueStart =
        start + token.length();

    if (valueStart >= line.length()) {
        return false;
    }

    std::size_t valueEnd =
        line.find_first_of(
            " \t\r\n",
            valueStart
        );

    if (valueEnd == std::string::npos) {
        valueEnd = line.length();
    }

    value =
        line.substr(
            valueStart,
            valueEnd - valueStart
        );

    return !value.empty();
}


// ============================================================
// Parse 32-bit hexadecimal value
// ============================================================

bool TraceParser::parseHex32(
    const std::string& text,
    uint32_t& value
)
{
    if (text.empty()) {
        return false;
    }

    std::string number = text;

    // Remove optional 0x / 0X prefix.
    if (
        number.length() >= 2 &&
        number[0] == '0' &&
        (
            number[1] == 'x' ||
            number[1] == 'X'
        )
    ) {
        number.erase(0, 2);
    }

    if (number.empty()) {
        return false;
    }

    // uint32_t cannot contain more than eight hexadecimal
    // digits.
    if (number.length() > 8) {
        return false;
    }

    try {

        std::size_t position = 0;

        const unsigned long parsed =
            std::stoul(
                number,
                &position,
                16
            );

        if (position != number.length()) {
            return false;
        }

        if (parsed > 0xFFFFFFFFul) {
            return false;
        }

        value =
            static_cast<uint32_t>(parsed);
    }
    catch (...) {
        return false;
    }

    return true;
}


// ============================================================
// Parse register
// ============================================================

bool TraceParser::parseRegister(
    const std::string& text,
    uint8_t& reg
)
{
    if (text.empty()) {
        return false;
    }

    std::string number = text;

    // Accept both:
    //
    // x5
    // 5

    if (
        number[0] == 'x' ||
        number[0] == 'X'
    ) {
        number.erase(0, 1);
    }

    if (number.empty()) {
        return false;
    }

    try {

        std::size_t position = 0;

        const unsigned long parsed =
            std::stoul(
                number,
                &position,
                10
            );

        if (position != number.length()) {
            return false;
        }

        if (parsed > 31) {
            return false;
        }

        reg =
            static_cast<uint8_t>(parsed);
    }
    catch (...) {
        return false;
    }

    return true;
}