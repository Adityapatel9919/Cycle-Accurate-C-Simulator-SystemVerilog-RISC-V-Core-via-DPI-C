// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vdpi_tb__pch.h"

Vdpi_tb__Syms::Vdpi_tb__Syms(VerilatedContext* contextp, const char* namep, Vdpi_tb* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(477);
    // Setup sub module instances
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscopep_dpi_tb = new VerilatedScope{this, "dpi_tb", "dpi_tb", "<null>", -9, VerilatedScope::SCOPE_OTHER};
    // Setup export functions - final: 0
    // Setup export functions - final: 1
}

Vdpi_tb__Syms::~Vdpi_tb__Syms() {
    // Tear down scopes
    VL_DO_CLEAR(delete __Vscopep_dpi_tb, __Vscopep_dpi_tb = nullptr);
    // Tear down sub module instances
}
