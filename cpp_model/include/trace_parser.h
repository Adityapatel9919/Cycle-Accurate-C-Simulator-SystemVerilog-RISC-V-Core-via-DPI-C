#ifndef TRACE_PARSER_H
#define TRACE_PARSER_H

#include "commit.h"

#include <cstddef>
#include <string>
#include <vector>

// ============================================================
// TRACE PARSER
// ============================================================
//
// Reads architectural COMMIT records from a text trace.
//
// Expected format:
//
// COMMIT PC=0x00000000 INSTR=0x00a00093
//        RD=x1 VALUE=0x0000000a
//        NEXT_PC=0x00000004
//
// Register writes may be absent:
//
// COMMIT PC=0x00000010 INSTR=0x00000013
//        NEXT_PC=0x00000014
//
// Store commits may additionally contain:
//
// MEM_ADDR=0x00000100
// MEM_VALUE=0x0000002a
// MEM_SIZE=4
//
// ============================================================

class TraceParser
{
public:

    // --------------------------------------------------------
    // Parse complete trace file
    // --------------------------------------------------------

    static bool parseFile(
        const std::string& filename,
        std::vector<Commit>& commits
    );


    // --------------------------------------------------------
    // Parse one COMMIT line
    //
    // Returns:
    //   true  -> valid COMMIT line parsed
    //   false -> line is not a valid COMMIT record
    // --------------------------------------------------------

    static bool parseLine(
        const std::string& line,
        Commit& commit
    );


private:

    // --------------------------------------------------------
    // Extract:
    //
    // KEY=value
    //
    // Example:
    //
    // PC=0x00000010
    //
    // result:
    //
    // value = "0x00000010"
    // --------------------------------------------------------

    static bool extractField(
        const std::string& line,
        const std::string& key,
        std::string& value
    );


    // --------------------------------------------------------
    // Convert hexadecimal string to uint32_t
    //
    // Accepts:
    //
    // 0000000a
    // 0x0000000a
    // --------------------------------------------------------

    static bool parseHex32(
        const std::string& text,
        uint32_t& value
    );


    // --------------------------------------------------------
    // Parse register field
    //
    // Accepts:
    //
    // 1
    // x1
    //
    // Rejects registers > x31.
    // --------------------------------------------------------

    static bool parseRegister(
        const std::string& text,
        uint8_t& reg
    );
};

#endif