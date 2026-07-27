// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VDPI_TB__SYMS_H_
#define VERILATED_VDPI_TB__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vdpi_tb.h"

// INCLUDE MODULE CLASSES
#include "Vdpi_tb___024root.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vdpi_tb__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vdpi_tb* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vdpi_tb___024root              TOP;

    // SCOPE NAMES
    VerilatedScope* __Vscopep_dpi_tb;

    // CONSTRUCTORS
    Vdpi_tb__Syms(VerilatedContext* contextp, const char* namep, Vdpi_tb* modelp);
    ~Vdpi_tb__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
