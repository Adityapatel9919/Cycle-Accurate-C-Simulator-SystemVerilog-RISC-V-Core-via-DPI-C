// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdpi_tb.h for the primary calling header

#include "Vdpi_tb__pch.h"

void Vdpi_tb___024root___ctor_var_reset(Vdpi_tb___024root* vlSelf);

Vdpi_tb___024root::Vdpi_tb___024root(Vdpi_tb__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vdpi_tb___024root___ctor_var_reset(this);
}

void Vdpi_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vdpi_tb___024root::~Vdpi_tb___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
