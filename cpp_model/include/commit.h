#ifndef COMMIT_H
#define COMMIT_H

#include <cstdint>

struct Commit
{
    
    bool valid = false;

    uint32_t pc = 0;
    uint32_t instruction = 0;

   
    uint32_t nextPC = 0;

    

    bool regWrite = false;

    uint8_t rd = 0;

    uint32_t rdValue = 0;

    

    bool memWrite = false;

    uint32_t memAddress = 0;

    uint32_t memValue = 0;

    // Number of bytes written:
    // SB = 1
    // SH = 2
    // SW = 4
    uint8_t memWriteSize = 0;
};

#endif