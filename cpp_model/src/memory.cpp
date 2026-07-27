
#include "memory.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

// ============================================================
// Constructor
// ============================================================

Memory::Memory(std::size_t size)
    : data(size, 0),
      programStart(0),
      programEnd(0),
      programWordCount(0)
{
}

// ============================================================
// Reset
// ============================================================

void Memory::reset()
{
    std::fill(data.begin(), data.end(), 0);

    programStart = 0;
    programEnd = 0;
    programWordCount = 0;
}
// ============================================================
// Address validation
// ============================================================

bool Memory::isValidAddress(
    uint32_t address,
    std::size_t accessSize
) const
{
    std::size_t addr = static_cast<std::size_t>(address);

    if (accessSize == 0)
        return false;

    if (addr >= data.size())
        return false;

    if (accessSize > data.size() - addr)
        return false;

    return true;
}

// ============================================================
// Internal bounds checker
// ============================================================

void Memory::checkAddress(
    uint32_t address,
    std::size_t accessSize
) const
{
    if (!isValidAddress(address, accessSize)) {
        throw std::out_of_range("Memory access out of range");
    }
}

// ============================================================
// Read byte
// ============================================================

uint8_t Memory::read8(uint32_t address) const
{
    checkAddress(address, 1);

    return data[address];
}

// ============================================================
// Read halfword
// ============================================================

uint16_t Memory::read16(uint32_t address) const
{
    checkAddress(address, 2);

    uint16_t value = 0;

    value |= static_cast<uint16_t>(data[address]);

    value |=
        static_cast<uint16_t>(data[address + 1]) << 8;

    return value;
}

// ============================================================
// Read word
// ============================================================

uint32_t Memory::read32(uint32_t address) const
{
    checkAddress(address, 4);

    uint32_t value = 0;

    value |=
        static_cast<uint32_t>(data[address]);

    value |=
        static_cast<uint32_t>(data[address + 1]) << 8;

    value |=
        static_cast<uint32_t>(data[address + 2]) << 16;

    value |=
        static_cast<uint32_t>(data[address + 3]) << 24;

    return value;
}

// ============================================================
// Write byte
// ============================================================

void Memory::write8(
    uint32_t address,
    uint8_t value
)
{
    checkAddress(address, 1);

    data[address] = value;
}

// ============================================================
// Write halfword
// ============================================================

void Memory::write16(
    uint32_t address,
    uint16_t value
)
{
    checkAddress(address, 2);

    data[address] =
        static_cast<uint8_t>(value & 0xFF);

    data[address + 1] =
        static_cast<uint8_t>((value >> 8) & 0xFF);
}

// ============================================================
// Write word
// ============================================================

void Memory::write32(
    uint32_t address,
    uint32_t value
)
{
    checkAddress(address, 4);

    data[address] =
        static_cast<uint8_t>(value & 0xFF);

    data[address + 1] =
        static_cast<uint8_t>((value >> 8) & 0xFF);

    data[address + 2] =
        static_cast<uint8_t>((value >> 16) & 0xFF);

    data[address + 3] =
        static_cast<uint8_t>((value >> 24) & 0xFF);
}

// ============================================================
// Memory size
// ============================================================

std::size_t Memory::size() const
{
    return data.size();
}

// ============================================================
// HEX loader
// ============================================================

bool Memory::loadHexFile(
    const std::string& filename,
    uint32_t baseAddress
)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr
            << "ERROR: Cannot open "
            << filename
            << '\n';

        return false;
    }

    // ========================================================
    // INITIALISE PROGRAM METADATA
    // ========================================================

    programStart = baseAddress;
    programEnd = baseAddress;
    programWordCount = 0;


    std::string line;

    uint32_t address = baseAddress;

    std::size_t wordsLoaded = 0;


    // ========================================================
    // LOAD HEX FILE
    // ========================================================

    while (std::getline(file, line)) {

        // Ignore empty lines
        if (line.empty()) {
            continue;
        }

        // Ignore comment lines
        if (line[0] == '#') {
            continue;
        }


        uint32_t instruction = 0;

        std::stringstream ss;

        ss << std::hex << line;
        ss >> instruction;


        if (ss.fail()) {

            std::cerr
                << "ERROR: Invalid HEX instruction: "
                << line
                << '\n';

            return false;
        }


        // ----------------------------------------------------
        // Bounds check
        // ----------------------------------------------------

        if (!isValidAddress(address, 4)) {

            std::cerr
                << "ERROR: Program exceeds memory size\n";

            return false;
        }


        // ----------------------------------------------------
        // Store instruction
        // ----------------------------------------------------

        write32(
            address,
            instruction
        );


        address += 4;

        ++wordsLoaded;
    }


    // ========================================================
    // SAVE PROGRAM METADATA
    // ========================================================

    programStart = baseAddress;

    programEnd = address;

    programWordCount = wordsLoaded;


    // ========================================================
    // REPORT
    // ========================================================

    std::cout
        << "Loaded "
        << wordsLoaded
        << " instructions from "
        << filename
        << '\n';


    return true;
}
uint32_t Memory::getProgramStart() const
{
    return programStart;
}


uint32_t Memory::getProgramEnd() const
{
    return programEnd;
}


std::size_t Memory::getProgramWordCount() const
{
    return programWordCount;
}
// ============================================================
// Check whether address belongs to loaded program
// ============================================================

bool Memory::isProgramAddress(uint32_t address) const
{
    return programWordCount != 0 &&
           address >= programStart &&
           address < programEnd;
}