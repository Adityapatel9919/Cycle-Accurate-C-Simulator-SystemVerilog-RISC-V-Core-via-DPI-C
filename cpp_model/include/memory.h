#ifndef MEMORY_H
#define MEMORY_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// ============================================================
// RV32I MEMORY MODEL
// ============================================================
//
// Byte-addressable, little-endian memory.
//
// In addition to normal memory accesses, this class tracks the
// address range occupied by the currently loaded program.
//
// Program range:
//
//     [programStart, programEnd)
//
// programEnd is exclusive.
//
// Example:
//
//     6 instructions loaded at address 0:
//
//     programStart = 0x00000000
//     programEnd   = 0x00000018
//
// Valid instruction PCs:
//
//     0x00
//     0x04
//     0x08
//     0x0C
//     0x10
//     0x14
//
// PC 0x18 is outside the loaded program.
//
// ============================================================

class Memory
{
public:

    // ========================================================
    // DEFAULT MEMORY SIZE
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

    bool loadHexFile(
        const std::string& filename,
        uint32_t baseAddress = 0
    );


    // ========================================================
    // PROGRAM INFORMATION
    // ========================================================

    uint32_t getProgramStart() const;

    uint32_t getProgramEnd() const;

    std::size_t getProgramWordCount() const;


    // ========================================================
    // PROGRAM ADDRESS CHECK
    // ========================================================
    //
    // Returns true when address points inside the loaded
    // program range:
    //
    //     programStart <= address < programEnd
    //
    // ========================================================

    bool isProgramAddress(
        uint32_t address
    ) const;


    // ========================================================
    // MEMORY READS
    // ========================================================

    uint8_t read8(
        uint32_t address
    ) const;

    uint16_t read16(
        uint32_t address
    ) const;

    uint32_t read32(
        uint32_t address
    ) const;


    // ========================================================
    // MEMORY WRITES
    // ========================================================

    void write8(
        uint32_t address,
        uint8_t value
    );

    void write16(
        uint32_t address,
        uint16_t value
    );

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


    // ========================================================
    // LOADED PROGRAM METADATA
    // ========================================================

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