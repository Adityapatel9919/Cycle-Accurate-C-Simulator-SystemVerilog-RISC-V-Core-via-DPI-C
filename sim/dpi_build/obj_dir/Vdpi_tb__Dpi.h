// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VDPI_TB__DPI_H_
#define VERILATED_VDPI_TB__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at tb/dpi/dpi_tb.sv:54:33
    extern int dpi_check_commit(unsigned int rtl_pc, unsigned int rtl_instruction, int rtl_reg_write, unsigned int rtl_rd, unsigned int rtl_rd_value);
    // DPI import at tb/dpi/dpi_tb.sv:64:33
    extern int dpi_finish();
    // DPI import at tb/dpi/dpi_tb.sv:50:33
    extern int dpi_init(const char* program_file);
    // DPI import at tb/dpi/dpi_tb.sv:62:33
    extern int dpi_reference_finished();

#ifdef __cplusplus
}
#endif

#endif  // guard
