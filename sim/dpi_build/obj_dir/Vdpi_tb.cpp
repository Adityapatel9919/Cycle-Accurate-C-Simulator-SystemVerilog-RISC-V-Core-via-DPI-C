// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vdpi_tb__pch.h"

//============================================================
// Constructors

Vdpi_tb::Vdpi_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vdpi_tb__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vdpi_tb::Vdpi_tb(const char* _vcname__)
    : Vdpi_tb(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vdpi_tb::~Vdpi_tb() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vdpi_tb___024root___eval_debug_assertions(Vdpi_tb___024root* vlSelf);
#endif  // VL_DEBUG
void Vdpi_tb___024root___eval_static(Vdpi_tb___024root* vlSelf);
void Vdpi_tb___024root___eval_initial(Vdpi_tb___024root* vlSelf);
void Vdpi_tb___024root___eval_settle(Vdpi_tb___024root* vlSelf);
void Vdpi_tb___024root___eval(Vdpi_tb___024root* vlSelf);

void Vdpi_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vdpi_tb::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vdpi_tb___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vdpi_tb___024root___eval_static(&(vlSymsp->TOP));
        Vdpi_tb___024root___eval_initial(&(vlSymsp->TOP));
        Vdpi_tb___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vdpi_tb___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vdpi_tb::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vdpi_tb::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vdpi_tb::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vdpi_tb___024root___eval_final(Vdpi_tb___024root* vlSelf);

VL_ATTR_COLD void Vdpi_tb::final() {
    contextp()->executingFinal(true);
    Vdpi_tb___024root___eval_final(&(vlSymsp->TOP));
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vdpi_tb::hierName() const { return vlSymsp->name(); }
const char* Vdpi_tb::modelName() const { return "Vdpi_tb"; }
unsigned Vdpi_tb::threads() const { return 1; }
void Vdpi_tb::prepareClone() const { contextp()->prepareClone(); }
void Vdpi_tb::atClone() const {
    contextp()->threadPoolpOnClone();
}
