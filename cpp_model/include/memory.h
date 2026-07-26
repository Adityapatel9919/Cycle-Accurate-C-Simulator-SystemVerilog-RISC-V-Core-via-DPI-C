#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

// ============================================================
// RV32I MEMORY MODEL
// ============================================================
//
// Byte-addressable memory:
//
// Address:
//   0x00000000 -> byte 0
//   0x00000001 -> byte 1
//   0x00000002 -> byte 2
//   0x00000003 -> byte 3
//
// RV32I is little-endian.
//
// Example:
//
// Word = 0x12345678
//
// Address +0 -> 0x78
// Address +1 -> 0x56
// Address +2 -> 0x34
// Address +3 -> 0x12
//
// ============================================================

class Memory
{
public:
    uint32_t getProgramStart() const;
uint32_t getProgramEnd() const;
std::size_t getProgramWordCount() const;

    // ========================================================
    // DEFAULT MEMORY SIZE
    // ========================================================
    //
    // 1 MiB is more than enough for our current directed tests.
    // ========================================================

    static constexpr std::size_t DEFAULT_SIZE =
        1024 * 1024;


    // ========================================================
    // CONSTRUCTOR
    // ========================================================

    explicit Memory(
        std::size_t size = DEFAULT_SIZE
    );


    // ========================================================
    // RESET MEMORY
    // ========================================================

    void reset();


    // ========================================================
    // HEX PROGRAM LOADER
    // ========================================================
    //
    // Loads the same .hex files currently used by the RTL.
    //
    // Example file:
    //
    // 00a00093
    // 01400113
    // 002081b3
    //
    // Each line represents one 32-bit instruction.
    //
    // The first instruction is placed at address 0x00000000,
    // the second at 0x00000004, etc.
    //
    // ========================================================

    bool loadHexFile(
        const std::string& filename,
        uint32_t baseAddress = 0
    );


    // ========================================================
    // 8-BIT READ
    // ========================================================

    uint8_t read8(
        uint32_t address
    ) const;


    // ========================================================
    // 16-BIT READ
    // ========================================================

    uint16_t read16(
        uint32_t address
    ) const;


    // ========================================================
    // 32-BIT READ
    //
    // Used for instruction fetch and LW.
    // ========================================================

    uint32_t read32(
        uint32_t address
    ) const;


    // ========================================================
    // 8-BIT WRITE
    //
    // Used by SB.
    // ========================================================

    void write8(
        uint32_t address,
        uint8_t value
    );


    // ========================================================
    // 16-BIT WRITE
    //
    // Used by SH.
    // ========================================================

    void write16(
        uint32_t address,
        uint16_t value
    );


    // ========================================================
    // 32-BIT WRITE
    //
    // Used by SW.
    // ========================================================

    void write32(
        uint32_t address,
        uint32_t value
    );


    // ========================================================
    // MEMORY INFORMATION
    // ========================================================

    std::size_t size() const;


    // ========================================================
    // ADDRESS VALIDATION
    // ========================================================

    bool isValidAddress(
        uint32_t address,
        std::size_t accessSize = 1
    ) const;


private:

    // ========================================================
    // BYTE-ADDRESSABLE MEMORY
    // ========================================================

    std::vector<uint8_t> data;

uint32_t programStart;
uint32_t programEnd;
std::size_t programWordCount;
    // ========================================================
    // INTERNAL BOUNDS CHECK
    // ========================================================

    void checkAddress(
        uint32_t address,
        std::size_t accessSize
    ) const;
};

#endif // MEMORY_H