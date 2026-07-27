// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdpi_tb.h for the primary calling header

#include "Vdpi_tb__pch.h"

extern "C" int dpi_init(const char* program_file);

void Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_init_TOP(std::string program_file, IData/*31:0*/ &dpi_init__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_init_TOP\n"); );
    // Body
    const char* program_file__Vcvt;
    program_file__Vcvt = program_file.c_str();
    int dpi_init__Vfuncrtn__Vcvt;
    dpi_init__Vfuncrtn__Vcvt = dpi_init(program_file__Vcvt);
    dpi_init__Vfuncrtn = (dpi_init__Vfuncrtn__Vcvt);
}

extern "C" int dpi_check_commit(unsigned int rtl_pc, unsigned int rtl_instruction, int rtl_reg_write, unsigned int rtl_rd, unsigned int rtl_rd_value);

void Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_check_commit_TOP(IData/*31:0*/ rtl_pc, IData/*31:0*/ rtl_instruction, IData/*31:0*/ rtl_reg_write, IData/*31:0*/ rtl_rd, IData/*31:0*/ rtl_rd_value, IData/*31:0*/ &dpi_check_commit__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_check_commit_TOP\n"); );
    // Body
    unsigned int rtl_pc__Vcvt;
    rtl_pc__Vcvt = rtl_pc;
    unsigned int rtl_instruction__Vcvt;
    rtl_instruction__Vcvt = rtl_instruction;
    int rtl_reg_write__Vcvt;
    rtl_reg_write__Vcvt = rtl_reg_write;
    unsigned int rtl_rd__Vcvt;
    rtl_rd__Vcvt = rtl_rd;
    unsigned int rtl_rd_value__Vcvt;
    rtl_rd_value__Vcvt = rtl_rd_value;
    int dpi_check_commit__Vfuncrtn__Vcvt;
    dpi_check_commit__Vfuncrtn__Vcvt = dpi_check_commit(rtl_pc__Vcvt, rtl_instruction__Vcvt, rtl_reg_write__Vcvt, rtl_rd__Vcvt, rtl_rd_value__Vcvt);
    dpi_check_commit__Vfuncrtn = (dpi_check_commit__Vfuncrtn__Vcvt);
}

extern "C" int dpi_reference_finished();

void Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_reference_finished_TOP(IData/*31:0*/ &dpi_reference_finished__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_reference_finished_TOP\n"); );
    // Body
    int dpi_reference_finished__Vfuncrtn__Vcvt;
    dpi_reference_finished__Vfuncrtn__Vcvt = dpi_reference_finished();
    dpi_reference_finished__Vfuncrtn = (dpi_reference_finished__Vfuncrtn__Vcvt);
}

extern "C" int dpi_finish();

void Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_finish_TOP(IData/*31:0*/ &dpi_finish__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_finish_TOP\n"); );
    // Body
    int dpi_finish__Vfuncrtn__Vcvt;
    dpi_finish__Vfuncrtn__Vcvt = dpi_finish();
    dpi_finish__Vfuncrtn = (dpi_finish__Vfuncrtn__Vcvt);
}

extern const VlWide<64>/*2047:0*/ Vdpi_tb__ConstPool__CONST_h5089d25d_0;
VlCoroutine Vdpi_tb___024root___eval_initial__TOP__Vtiming__0(Vdpi_tb___024root* vlSelf);
VlCoroutine Vdpi_tb___024root___eval_initial__TOP__Vtiming__1(Vdpi_tb___024root* vlSelf);

void Vdpi_tb___024root___eval_initial(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_initial\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vinline__eval_initial__TOP_dpi_tb__DOT__dut__DOT__imem_inst__DOT____VlemExpr_0;
    IData/*31:0*/ __Vinline__eval_initial__TOP_dpi_tb__DOT__dut__DOT__imem_inst__DOT__i;
    __Vinline__eval_initial__TOP_dpi_tb__DOT__dut__DOT__imem_inst__DOT__i = 0;
    // Body
    __Vinline__eval_initial__TOP_dpi_tb__DOT__dut__DOT__imem_inst__DOT__i = 0U;
    while (VL_GTS_III(32, 0x00000400U, __Vinline__eval_initial__TOP_dpi_tb__DOT__dut__DOT__imem_inst__DOT__i)) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__memory[(0x000003ffU 
                                                                 & __Vinline__eval_initial__TOP_dpi_tb__DOT__dut__DOT__imem_inst__DOT__i)] = 0x00000013U;
        __Vinline__eval_initial__TOP_dpi_tb__DOT__dut__DOT__imem_inst__DOT__i 
            = ((IData)(1U) + __Vinline__eval_initial__TOP_dpi_tb__DOT__dut__DOT__imem_inst__DOT__i);
    }
    __Vinline__eval_initial__TOP_dpi_tb__DOT__dut__DOT__imem_inst__DOT____VlemExpr_0 
        = VL_VALUEPLUSARGS_INW(2048, "PROGRAM=%s"s, 
                               vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__program_file);
    if ((! __Vinline__eval_initial__TOP_dpi_tb__DOT__dut__DOT__imem_inst__DOT____VlemExpr_0)) {
        VL_ASSIGN_W(2048, vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__program_file, Vdpi_tb__ConstPool__CONST_h5089d25d_0);
    }
    VL_WRITEF_NX("\nLoading program: %s\n\n",1, '#',2048,vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__program_file.data());
    VL_READMEM_N(true, 32, 1024, 0, VL_CVT_PACK_STR_NW(64, vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__program_file)
                 ,  &(vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__memory)
                 , 0, ~0ULL);
    Vdpi_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vdpi_tb___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

VlCoroutine Vdpi_tb___024root___eval_initial__TOP__Vtiming__0(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.dpi_tb__DOT__clk = 0U;
    while (true) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "tb/dpi/dpi_tb.sv", 
                                             92);
        vlSelfRef.dpi_tb__DOT__clk = (1U & (~ (IData)(vlSelfRef.dpi_tb__DOT__clk)));
    }
    co_return;
}

void Vdpi_tb___024root____VbeforeTrig_h57ac7983__0(Vdpi_tb___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vdpi_tb___024root___eval_initial__TOP__Vtiming__1(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ dpi_tb__DOT____VlemExpr_0;
    IData/*31:0*/ dpi_tb__DOT__unnamedblk1_1__DOT____Vrepeat0;
    dpi_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ __Vfunc_dpi_tb__DOT__dpi_init__0__Vfuncout;
    __Vfunc_dpi_tb__DOT__dpi_init__0__Vfuncout = 0;
    // Body
    vlSelfRef.dpi_tb__DOT__rst = 1U;
    vlSelfRef.dpi_tb__DOT__cycle_count = 0U;
    vlSelfRef.dpi_tb__DOT__commit_count = 0U;
    vlSelfRef.dpi_tb__DOT__reference_finished = 0U;
    dpi_tb__DOT____VlemExpr_0 = VL_VALUEPLUSARGS_INN(64, "PROGRAM=%s"s, 
                                                     vlSelfRef.dpi_tb__DOT__program_file);
    if (VL_UNLIKELY(((! dpi_tb__DOT____VlemExpr_0)))) {
        VL_WRITEF_NX("[%0t] %%Fatal: dpi_tb.sv:123: Assertion failed in %m: [DPI TB] Missing +PROGRAM=<file.hex>\n",3, 'M',vlSymsp->name(),"dpi_tb", 'T',-9
                     , '#',64,VL_TIME_UNITED_Q(1000));
        VL_STOP_MT("tb/dpi/dpi_tb.sv", 123, "", false);
    }
    VL_WRITEF_NX("\n==================================================\n       RV32I DPI LOCKSTEP VERIFICATION\n==================================================\n\n[DPI TB] Program: %s\n",1
                 , 'S',&(vlSelfRef.dpi_tb__DOT__program_file));
    Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_init_TOP(vlSelfRef.dpi_tb__DOT__program_file, __Vfunc_dpi_tb__DOT__dpi_init__0__Vfuncout);
    vlSelfRef.dpi_tb__DOT__dpi_status = __Vfunc_dpi_tb__DOT__dpi_init__0__Vfuncout;
    if (VL_UNLIKELY(((0U == vlSelfRef.dpi_tb__DOT__dpi_status)))) {
        VL_WRITEF_NX("[%0t] %%Fatal: dpi_tb.sv:151: Assertion failed in %m: [DPI TB] Failed to initialize C++ golden model\n",3, 'M',vlSymsp->name(),"dpi_tb", 'T',-9
                     , '#',64,VL_TIME_UNITED_Q(1000));
        VL_STOP_MT("tb/dpi/dpi_tb.sv", 151, "", false);
    }
    dpi_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 5U;
    while (VL_LTS_III(32, 0U, dpi_tb__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vdpi_tb___024root____VbeforeTrig_h57ac7983__0(vlSelf, 
                                                      "@(posedge dpi_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h57ac7983__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge dpi_tb.clk)", 
                                                             "tb/dpi/dpi_tb.sv", 
                                                             163);
        dpi_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (dpi_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.dpi_tb__DOT__rst = 0U;
    VL_WRITEF_NX("[DPI TB] Reset released\n\n",0);
    co_return;
}

void Vdpi_tb___024root___eval_triggers_vec__act(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_triggers_vec__act\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 2U) 
                                                     | ((((IData)(vlSelfRef.dpi_tb__DOT__rst) 
                                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__dpi_tb__DOT__rst__0))) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.dpi_tb__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__dpi_tb__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__dpi_tb__DOT__clk__0 
        = vlSelfRef.dpi_tb__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__dpi_tb__DOT__rst__0 
        = vlSelfRef.dpi_tb__DOT__rst;
}

bool Vdpi_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vdpi_tb___024root___nba_sequent__TOP__0(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___nba_sequent__TOP__0\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vfunc_dpi_tb__DOT__dpi_check_commit__1__Vfuncout;
    __Vfunc_dpi_tb__DOT__dpi_check_commit__1__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_dpi_tb__DOT__dpi_reference_finished__2__Vfuncout;
    __Vfunc_dpi_tb__DOT__dpi_reference_finished__2__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_dpi_tb__DOT__dpi_finish__3__Vfuncout;
    __Vfunc_dpi_tb__DOT__dpi_finish__3__Vfuncout = 0;
    IData/*31:0*/ __Vdly__dpi_tb__DOT__cycle_count;
    __Vdly__dpi_tb__DOT__cycle_count = 0;
    IData/*31:0*/ __VdlyMask__dpi_tb__DOT__cycle_count;
    __VdlyMask__dpi_tb__DOT__cycle_count = 0;
    // Body
    vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0 = 0U;
    vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v0 = 0U;
    vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32 = 0U;
    if (((~ (IData)(vlSelfRef.dpi_tb__DOT__rst)) & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_valid))) {
        if (((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_reg_write) 
             & (0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd)))) {
            VL_WRITEF_NX("COMMIT PC=0x%08h INSTR=0x%08h RD=x%0d VALUE=0x%08h\n",4
                         , '#',32,vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc
                         , '#',32,vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_instr
                         , '#',5,(IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd)
                         , '#',32,vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data);
        } else {
            VL_WRITEF_NX("COMMIT PC=0x%08h INSTR=0x%08h RD=- VALUE=-\n",2
                         , '#',32,vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc
                         , '#',32,vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_instr);
        }
    }
    if (vlSelfRef.dpi_tb__DOT__rst) {
        __Vdly__dpi_tb__DOT__cycle_count = 0U;
        __VdlyMask__dpi_tb__DOT__cycle_count = 0xffffffffU;
    } else {
        __Vdly__dpi_tb__DOT__cycle_count = ((IData)(1U) 
                                            + vlSelfRef.dpi_tb__DOT__cycle_count);
        __VdlyMask__dpi_tb__DOT__cycle_count = 0xffffffffU;
        if (VL_UNLIKELY((VL_LTES_III(32, 0x000003e8U, vlSelfRef.dpi_tb__DOT__cycle_count)))) {
            VL_WRITEF_NX("[%0t] %%Fatal: dpi_tb.sv:198: Assertion failed in %m: [DPI TB] TIMEOUT after %0d cycles\n",4, 'M',vlSymsp->name(),"dpi_tb", 'T',-9
                         , '#',64,VL_TIME_UNITED_Q(1000)
                         , '~',32,vlSelfRef.dpi_tb__DOT__cycle_count);
            VL_STOP_MT("tb/dpi/dpi_tb.sv", 198, "", false);
        }
    }
    if (((~ (IData)(vlSelfRef.dpi_tb__DOT__rst)) & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_valid))) {
        vlSelfRef.dpi_tb__DOT__commit_count = ((IData)(1U) 
                                               + vlSelfRef.dpi_tb__DOT__commit_count);
        Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_check_commit_TOP(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc, vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_instr, 
                                                                          ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_valid) 
                                                                           & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)), (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd), vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data, __Vfunc_dpi_tb__DOT__dpi_check_commit__1__Vfuncout);
        vlSelfRef.dpi_tb__DOT__dpi_status = __Vfunc_dpi_tb__DOT__dpi_check_commit__1__Vfuncout;
        if (VL_UNLIKELY(((0U == vlSelfRef.dpi_tb__DOT__dpi_status)))) {
            VL_WRITEF_NX("\n[DPI TB] Lockstep failure at commit %0d\n[%0t] %%Fatal: dpi_tb.sv:248: Assertion failed in %m: [DPI TB] RTL / C++ architectural mismatch\n",4, 'M',vlSymsp->name(),"dpi_tb", 'T',-9
                         , '~',32,vlSelfRef.dpi_tb__DOT__commit_count
                         , '#',64,VL_TIME_UNITED_Q(1000));
            VL_STOP_MT("tb/dpi/dpi_tb.sv", 248, "", false);
        }
        Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_reference_finished_TOP(__Vfunc_dpi_tb__DOT__dpi_reference_finished__2__Vfuncout);
        vlSelfRef.dpi_tb__DOT__reference_finished = __Vfunc_dpi_tb__DOT__dpi_reference_finished__2__Vfuncout;
        if (VL_UNLIKELY(((0U != vlSelfRef.dpi_tb__DOT__reference_finished)))) {
            Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_finish_TOP(__Vfunc_dpi_tb__DOT__dpi_finish__3__Vfuncout);
            vlSelfRef.dpi_tb__DOT__dpi_status = __Vfunc_dpi_tb__DOT__dpi_finish__3__Vfuncout;
            if (VL_UNLIKELY(((0U == vlSelfRef.dpi_tb__DOT__dpi_status)))) {
                VL_WRITEF_NX("[%0t] %%Fatal: dpi_tb.sv:276: Assertion failed in %m: [DPI TB] Golden model final check failed\n",3, 'M',vlSymsp->name(),"dpi_tb", 'T',-9
                             , '#',64,VL_TIME_UNITED_Q(1000));
                VL_STOP_MT("tb/dpi/dpi_tb.sv", 276, "", false);
            }
            VL_WRITEF_NX("\n==================================================\n              DPI TEST PASSED\n==================================================\nCycles  : %0d\nCommits : %0d\n==================================================\n\n",2
                         , '~',32,vlSelfRef.dpi_tb__DOT__cycle_count
                         , '~',32,vlSelfRef.dpi_tb__DOT__commit_count);
            VL_FINISH_MT("tb/dpi/dpi_tb.sv", 303, "");
        }
    }
    if (vlSelfRef.dpi_tb__DOT__rst) {
        vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v0 = 1U;
    } else if (((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_reg_write) 
                & (0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd)))) {
        vlSelfRef.__VdlyVal__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data;
        vlSelfRef.__VdlyDim0__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd;
        vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32 = 1U;
    }
    if (((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_mem_write) 
         & (0x00000400U > (vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_alu_result 
                           >> 2U)))) {
        vlSelfRef.__VdlyVal__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rs2_data;
        vlSelfRef.__VdlyDim0__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0 
            = (0x000003ffU & (vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_alu_result 
                              >> 2U));
        vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0 = 1U;
    }
    vlSelfRef.dpi_tb__DOT__cycle_count = ((__Vdly__dpi_tb__DOT__cycle_count 
                                           & __VdlyMask__dpi_tb__DOT__cycle_count) 
                                          | (vlSelfRef.dpi_tb__DOT__cycle_count 
                                             & (~ __VdlyMask__dpi_tb__DOT__cycle_count)));
    __VdlyMask__dpi_tb__DOT__cycle_count = 0U;
}

extern const VlUnpacked<CData/*0:0*/, 128> Vdpi_tb__ConstPool__TABLE_hd1ea5af5_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vdpi_tb__ConstPool__TABLE_h93bfbd5d_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vdpi_tb__ConstPool__TABLE_h094b32f0_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vdpi_tb__ConstPool__TABLE_h9042c495_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vdpi_tb__ConstPool__TABLE_h343c9294_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vdpi_tb__ConstPool__TABLE_ha0edcdc0_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vdpi_tb__ConstPool__TABLE_h87d4bd01_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vdpi_tb__ConstPool__TABLE_hd9357a73_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vdpi_tb__ConstPool__TABLE_h01cc072a_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vdpi_tb__ConstPool__TABLE_h15806f02_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vdpi_tb__ConstPool__TABLE_h6ddb05e1_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vdpi_tb__ConstPool__TABLE_h1490e233_0;

void Vdpi_tb___024root___nba_sequent__TOP__1(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___nba_sequent__TOP__1\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ dpi_tb__DOT__dut__DOT__uses_rs1_id;
    dpi_tb__DOT__dut__DOT__uses_rs1_id = 0;
    CData/*0:0*/ dpi_tb__DOT__dut__DOT__uses_rs2_id;
    dpi_tb__DOT__dut__DOT__uses_rs2_id = 0;
    CData/*0:0*/ dpi_tb__DOT__dut__DOT__id_ex_flush_hazard;
    dpi_tb__DOT__dut__DOT__id_ex_flush_hazard = 0;
    CData/*1:0*/ dpi_tb__DOT__dut__DOT__forward_a;
    dpi_tb__DOT__dut__DOT__forward_a = 0;
    CData/*1:0*/ dpi_tb__DOT__dut__DOT__forward_b;
    dpi_tb__DOT__dut__DOT__forward_b = 0;
    CData/*0:0*/ dpi_tb__DOT__dut__DOT__hazard_inst__DOT__load_use_hazard;
    dpi_tb__DOT__dut__DOT__hazard_inst__DOT__load_use_hazard = 0;
    CData/*6:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    IData/*31:0*/ __Vdly__dpi_tb__DOT__dut__DOT__pc_current;
    __Vdly__dpi_tb__DOT__dut__DOT__pc_current = 0;
    // Body
    __Vdly__dpi_tb__DOT__dut__DOT__pc_current = vlSelfRef.dpi_tb__DOT__dut__DOT__pc_current;
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_src 
        = ((1U & (~ ((IData)(vlSelfRef.dpi_tb__DOT__rst) 
                     | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush)))) 
           && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_src_id));
    if (((IData)(vlSelfRef.dpi_tb__DOT__rst) | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush))) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_op = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_a_sel = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct7 = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3 = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs1 = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs2 = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs1_data = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs2_data = 0U;
    } else {
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_op 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__alu_op_id;
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_a_sel 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__alu_a_sel_id;
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct7 
            = (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
               >> 0x00000019U);
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3 
            = (7U & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                     >> 0x0000000cU));
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs1 
            = (0x0000001fU & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                              >> 0x0000000fU));
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs2 
            = (0x0000001fU & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                              >> 0x00000014U));
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs1_data 
            = ((((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd) 
                 == (0x0000001fU & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                    >> 0x0000000fU))) 
                & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0))
                ? vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data
                : (vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs
                   [(0x0000001fU & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                    >> 0x0000000fU))] 
                   & (- (IData)((0U != (0x0000001fU 
                                        & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                           >> 0x0000000fU)))))));
        vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs2_data 
            = ((((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd) 
                 == (0x0000001fU & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                    >> 0x00000014U))) 
                & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0))
                ? vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data
                : (vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs
                   [(0x0000001fU & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                    >> 0x00000014U))] 
                   & (- (IData)((0U != (0x0000001fU 
                                        & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                           >> 0x00000014U)))))));
    }
    if (vlSelfRef.dpi_tb__DOT__rst) {
        __Vdly__dpi_tb__DOT__dut__DOT__pc_current = 0U;
    } else if (vlSelfRef.dpi_tb__DOT__dut__DOT__pc_write) {
        __Vdly__dpi_tb__DOT__dut__DOT__pc_current = 
            ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_flush)
              ? ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_jalr)
                  ? (0xfffffffeU & (vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_immediate 
                                    + vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs1))
                  : (vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_pc 
                     + vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_immediate))
              : ((IData)(4U) + vlSelfRef.dpi_tb__DOT__dut__DOT__pc_current));
    }
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_immediate 
        = (((IData)(vlSelfRef.dpi_tb__DOT__rst) | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush))
            ? 0U : ((0x00000040U & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction)
                     ? ((- (IData)((1U & (~ (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                             >> 4U))))) 
                        & (((8U & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction)
                             ? (((((0x00000ffeU & (
                                                   (- (IData)(
                                                              (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                               >> 0x0000001fU))) 
                                                   << 1U)) 
                                   | (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                      >> 0x0000001fU)) 
                                  << 0x00000014U) | 
                                 ((((0x000001feU & 
                                     (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                      >> 0x0000000bU)) 
                                    | (1U & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                             >> 0x00000014U))) 
                                   << 0x0000000bU) 
                                  | (0x000007feU & 
                                     (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                      >> 0x00000014U)))) 
                                & (- (IData)((7U == 
                                              (7U & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction)))))
                             : ((4U & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction)
                                 ? vlSelfRef.__VdfgRegularize_hebeb780c_0_3
                                 : ((((- (IData)((vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                  >> 0x0000001fU))) 
                                      << 0x0000000dU) 
                                     | ((((2U & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                 >> 0x0000001eU)) 
                                          | (1U & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                   >> 7U))) 
                                         << 0x0000000bU) 
                                        | ((0x000007e0U 
                                            & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                               >> 0x00000014U)) 
                                           | (0x0000001eU 
                                              & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                 >> 7U))))) 
                                    & (- (IData)((3U 
                                                  == 
                                                  (3U 
                                                   & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction))))))) 
                           & (- (IData)((1U & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                               >> 5U))))))
                     : ((0x00000020U & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction)
                         ? ((0x00000010U & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction)
                             ? ((- (IData)((IData)(
                                                   (4U 
                                                    == 
                                                    (0x0000000cU 
                                                     & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction))))) 
                                & vlSelfRef.__VdfgRegularize_hebeb780c_0_7)
                             : ((((- (IData)((vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                              >> 0x0000001fU))) 
                                  << 0x0000000cU) | 
                                 ((0x00000fe0U & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                  >> 0x00000014U)) 
                                  | (0x0000001fU & 
                                     (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                      >> 7U)))) & (- (IData)((IData)(
                                                                     (3U 
                                                                      == 
                                                                      (0x0000000fU 
                                                                       & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction)))))))
                         : ((0x00000010U & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction)
                             ? (((4U & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction)
                                  ? vlSelfRef.__VdfgRegularize_hebeb780c_0_7
                                  : vlSelfRef.__VdfgRegularize_hebeb780c_0_3) 
                                & (- (IData)((1U & 
                                              (~ (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                  >> 3U))))))
                             : (vlSelfRef.__VdfgRegularize_hebeb780c_0_3 
                                & ((- (IData)((1U & 
                                               (~ (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                   >> 3U))))) 
                                   & (- (IData)((1U 
                                                 & (~ 
                                                    (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                     >> 2U)))))))))));
    if (vlSelfRef.dpi_tb__DOT__rst) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_alu_result = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_wb_sel = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc_plus4 = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_memory_data = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_instr = 0x00000013U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rs2_data = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_wb_sel = 0U;
    } else {
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_alu_result 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_alu_result;
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_wb_sel 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_wb_sel;
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc_plus4 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_pc_plus4;
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_memory_data 
            = (((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_mem_read) 
                & (0x00000400U > (vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_alu_result 
                                  >> 2U))) ? vlSelfRef.dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem
               [(0x000003ffU & (vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_alu_result 
                                >> 2U))] : 0U);
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_pc;
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_instr 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_instr;
        vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rs2_data 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs2;
        vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_wb_sel 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_wb_sel;
    }
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_wb_sel = 
        (((IData)(vlSelfRef.dpi_tb__DOT__rst) | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush))
          ? 0U : (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__wb_sel_id));
    vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_pc_plus4 
        = ((IData)(vlSelfRef.dpi_tb__DOT__rst) ? 0U
            : vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_pc_plus4);
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_pc_plus4 
        = (((IData)(vlSelfRef.dpi_tb__DOT__rst) | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush))
            ? 0U : ((IData)(4U) + vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_pc));
    if (vlSelfRef.dpi_tb__DOT__rst) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_alu_result = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_pc = 0U;
    } else {
        vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_alu_result 
            = ((8U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex))
                ? ((- (IData)((1U & (~ ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex) 
                                        >> 1U))))) 
                   & (((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex))
                        ? (1U & (- (IData)((vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_a 
                                            < vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_b))))
                        : (1U & (- (IData)(VL_LTS_III(32, vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_a, vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_b))))) 
                      & (- (IData)((1U & (~ ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex) 
                                             >> 2U)))))))
                : ((4U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex))
                    ? ((2U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex))
                        ? ((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex))
                            ? VL_SHIFTRS_III(32,32,5, vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_a, 
                                             (0x0000001fU 
                                              & vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_b))
                            : (vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_a 
                               >> (0x0000001fU & vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_b)))
                        : ((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex))
                            ? (vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_a 
                               << (0x0000001fU & vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_b))
                            : (vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_a 
                               ^ vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_b)))
                    : ((2U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex))
                        ? ((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex))
                            ? (vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_a 
                               | vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_b)
                            : (vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_a 
                               & vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_b))
                        : ((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex))
                            ? (vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_a 
                               - vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_b)
                            : (vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_a 
                               + vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_b)))));
        vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rd;
        vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_pc 
            = vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_pc;
    }
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_pc = (((IData)(vlSelfRef.dpi_tb__DOT__rst) 
                                                  | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush))
                                                  ? 0U
                                                  : vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_pc);
    vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_instr = 
        ((IData)(vlSelfRef.dpi_tb__DOT__rst) ? 0x00000013U
          : vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_instr);
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_instr = 
        (((IData)(vlSelfRef.dpi_tb__DOT__rst) | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush))
          ? 0x00000013U : vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction);
    vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rd = ((IData)(vlSelfRef.dpi_tb__DOT__rst)
                                                   ? 0U
                                                   : (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rd));
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rd = (((IData)(vlSelfRef.dpi_tb__DOT__rst) 
                                                  | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush))
                                                  ? 0U
                                                  : 
                                                 (0x0000001fU 
                                                  & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                     >> 7U)));
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_branch = 
        ((1U & (~ ((IData)(vlSelfRef.dpi_tb__DOT__rst) 
                   | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush)))) 
         && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__branch_id));
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_jump = (
                                                   (1U 
                                                    & (~ 
                                                       ((IData)(vlSelfRef.dpi_tb__DOT__rst) 
                                                        | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush)))) 
                                                   && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__jump_id));
    vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_valid = 
        ((1U & (~ (IData)(vlSelfRef.dpi_tb__DOT__rst))) 
         && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_valid));
    vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_mem_write 
        = ((1U & (~ (IData)(vlSelfRef.dpi_tb__DOT__rst))) 
           && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_mem_write));
    vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_reg_write 
        = ((1U & (~ (IData)(vlSelfRef.dpi_tb__DOT__rst))) 
           && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_reg_write));
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_jalr = (
                                                   (1U 
                                                    & (~ 
                                                       ((IData)(vlSelfRef.dpi_tb__DOT__rst) 
                                                        | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush)))) 
                                                   && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__jalr_id));
    vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data 
        = ((0U == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_wb_sel))
            ? vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_alu_result
            : ((1U == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_wb_sel))
                ? vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_memory_data
                : (vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc_plus4 
                   & (- (IData)((2U == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_wb_sel)))))));
    vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_mem_read 
        = ((1U & (~ (IData)(vlSelfRef.dpi_tb__DOT__rst))) 
           && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_mem_read));
    vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_valid = 
        ((1U & (~ (IData)(vlSelfRef.dpi_tb__DOT__rst))) 
         && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_valid));
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_mem_write 
        = ((1U & (~ ((IData)(vlSelfRef.dpi_tb__DOT__rst) 
                     | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush)))) 
           && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_write_id));
    vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_reg_write 
        = ((1U & (~ (IData)(vlSelfRef.dpi_tb__DOT__rst))) 
           && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_reg_write));
    vlSelfRef.dpi_tb__DOT__dut__DOT__alu_ctrl_ex = 
        (((1U == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_op))
           ? 1U : (((4U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                     ? ((2U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                         ? ((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                             ? 2U : 3U) : ((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                                            ? ((0x20U 
                                                == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct7))
                                                ? 7U
                                                : 6U)
                                            : 4U)) : 
                    ((2U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                      ? ((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                          ? 9U : 8U) : ((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                                         ? 5U : (1U 
                                                 & (- (IData)(
                                                              (0x20U 
                                                               == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct7)))))))) 
                   & (- (IData)((2U == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_op)))))) 
         & (- (IData)((0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_op)))));
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_mem_read 
        = ((1U & (~ ((IData)(vlSelfRef.dpi_tb__DOT__rst) 
                     | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush)))) 
           && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_read_id));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_0 = ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_reg_write) 
                                                & (0U 
                                                   != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd)));
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_valid = 
        ((1U & (~ ((IData)(vlSelfRef.dpi_tb__DOT__rst) 
                   | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush)))) 
         && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_valid));
    if (vlSelfRef.dpi_tb__DOT__rst) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_valid = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_pc = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction = 0x00000013U;
    } else if (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_flush) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_valid = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_pc = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction = 0x00000013U;
    } else if (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_write) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_valid = 1U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_pc = vlSelfRef.dpi_tb__DOT__dut__DOT__pc_current;
        vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
            = ((0x00000400U > (vlSelfRef.dpi_tb__DOT__dut__DOT__pc_current 
                               >> 2U)) ? vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__memory
               [(0x000003ffU & (vlSelfRef.dpi_tb__DOT__dut__DOT__pc_current 
                                >> 2U))] : 0x00000013U);
    }
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_reg_write 
        = ((1U & (~ ((IData)(vlSelfRef.dpi_tb__DOT__rst) 
                     | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush)))) 
           && (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__reg_write_id));
    dpi_tb__DOT__dut__DOT__forward_a = 0U;
    if ((((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_reg_write) 
          & (0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rd))) 
         & ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rd) 
            == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs1)))) {
        dpi_tb__DOT__dut__DOT__forward_a = 2U;
    }
    if (((((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_reg_write) 
           & (0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd))) 
          & (~ (((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_reg_write) 
                 & (0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rd))) 
                & ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rd) 
                   == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs1))))) 
         & ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd) 
            == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs1)))) {
        dpi_tb__DOT__dut__DOT__forward_a = 1U;
    }
    dpi_tb__DOT__dut__DOT__forward_b = 0U;
    if ((((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_reg_write) 
          & (0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rd))) 
         & ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rd) 
            == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs2)))) {
        dpi_tb__DOT__dut__DOT__forward_b = 2U;
    }
    if (((((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_reg_write) 
           & (0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd))) 
          & (~ (((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_reg_write) 
                 & (0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rd))) 
                & ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rd) 
                   == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs2))))) 
         & ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd) 
            == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs2)))) {
        dpi_tb__DOT__dut__DOT__forward_b = 1U;
    }
    vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs1 
        = ((0U == (IData)(dpi_tb__DOT__dut__DOT__forward_a))
            ? vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs1_data
            : ((2U == (IData)(dpi_tb__DOT__dut__DOT__forward_a))
                ? vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_alu_result
                : ((1U == (IData)(dpi_tb__DOT__dut__DOT__forward_a))
                    ? vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data
                    : vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs1_data)));
    vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs2 
        = ((0U == (IData)(dpi_tb__DOT__dut__DOT__forward_b))
            ? vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs2_data
            : ((2U == (IData)(dpi_tb__DOT__dut__DOT__forward_b))
                ? vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_alu_result
                : ((1U == (IData)(dpi_tb__DOT__dut__DOT__forward_b))
                    ? vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data
                    : vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rs2_data)));
    vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_a 
        = ((0U == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_a_sel))
            ? vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs1
            : ((1U == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_a_sel))
                ? vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_pc
                : (vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs1 
                   & (- (IData)((2U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_a_sel)))))));
    vlSelfRef.dpi_tb__DOT__dut__DOT__alu_operand_b 
        = ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_alu_src)
            ? vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_immediate
            : vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs2);
    vlSelfRef.dpi_tb__DOT__dut__DOT__pc_current = __Vdly__dpi_tb__DOT__dut__DOT__pc_current;
    vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_flush = 
        ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_jump) 
         | ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_branch) 
            & ((4U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                ? ((2U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                    ? ((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                        ? (vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs1 
                           >= vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs2)
                        : (vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs1 
                           < vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs2))
                    : ((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                        ? VL_GTES_III(32, vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs1, vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs2)
                        : VL_LTS_III(32, vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs1, vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs2)))
                : ((~ ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3) 
                       >> 1U)) & ((1U & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_funct3))
                                   ? (vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs1 
                                      != vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs2)
                                   : (vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs1 
                                      == vlSelfRef.dpi_tb__DOT__dut__DOT__forwarded_rs2))))));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_3 = ((((- (IData)(
                                                             (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                              >> 0x0000001fU))) 
                                                  << 0x0000000cU) 
                                                 | (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                    >> 0x00000014U)) 
                                                & (- (IData)(
                                                             (3U 
                                                              == 
                                                              (3U 
                                                               & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction)))));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_7 = (0xfffff000U 
                                                & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                                   & (- (IData)(
                                                                (3U 
                                                                 == 
                                                                 (3U 
                                                                  & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction))))));
    __Vtableidx1 = (0x0000007fU & vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction);
    dpi_tb__DOT__dut__DOT__uses_rs1_id = Vdpi_tb__ConstPool__TABLE_hd1ea5af5_0
        [__Vtableidx1];
    dpi_tb__DOT__dut__DOT__uses_rs2_id = Vdpi_tb__ConstPool__TABLE_h93bfbd5d_0
        [__Vtableidx1];
    vlSelfRef.dpi_tb__DOT__dut__DOT__alu_src_id = Vdpi_tb__ConstPool__TABLE_h094b32f0_0
        [__Vtableidx1];
    vlSelfRef.dpi_tb__DOT__dut__DOT__alu_op_id = Vdpi_tb__ConstPool__TABLE_h9042c495_0
        [__Vtableidx1];
    vlSelfRef.dpi_tb__DOT__dut__DOT__alu_a_sel_id = Vdpi_tb__ConstPool__TABLE_h343c9294_0
        [__Vtableidx1];
    vlSelfRef.dpi_tb__DOT__dut__DOT__mem_read_id = Vdpi_tb__ConstPool__TABLE_ha0edcdc0_0
        [__Vtableidx1];
    vlSelfRef.dpi_tb__DOT__dut__DOT__mem_write_id = Vdpi_tb__ConstPool__TABLE_h87d4bd01_0
        [__Vtableidx1];
    vlSelfRef.dpi_tb__DOT__dut__DOT__branch_id = Vdpi_tb__ConstPool__TABLE_hd9357a73_0
        [__Vtableidx1];
    vlSelfRef.dpi_tb__DOT__dut__DOT__jump_id = Vdpi_tb__ConstPool__TABLE_h01cc072a_0
        [__Vtableidx1];
    vlSelfRef.dpi_tb__DOT__dut__DOT__jalr_id = Vdpi_tb__ConstPool__TABLE_h15806f02_0
        [__Vtableidx1];
    vlSelfRef.dpi_tb__DOT__dut__DOT__reg_write_id = Vdpi_tb__ConstPool__TABLE_h6ddb05e1_0
        [__Vtableidx1];
    vlSelfRef.dpi_tb__DOT__dut__DOT__wb_sel_id = Vdpi_tb__ConstPool__TABLE_h1490e233_0
        [__Vtableidx1];
    dpi_tb__DOT__dut__DOT__hazard_inst__DOT__load_use_hazard 
        = (((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_mem_read) 
            & (0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rd))) 
           & (((IData)(dpi_tb__DOT__dut__DOT__uses_rs1_id) 
               & ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rd) 
                  == (0x0000001fU & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                     >> 0x0000000fU)))) 
              | ((IData)(dpi_tb__DOT__dut__DOT__uses_rs2_id) 
                 & ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_rd) 
                    == (0x0000001fU & (vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_instruction 
                                       >> 0x00000014U))))));
    vlSelfRef.dpi_tb__DOT__dut__DOT__pc_write = 1U;
    vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_write = 1U;
    dpi_tb__DOT__dut__DOT__id_ex_flush_hazard = 0U;
    if (dpi_tb__DOT__dut__DOT__hazard_inst__DOT__load_use_hazard) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__pc_write = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_write = 0U;
        dpi_tb__DOT__dut__DOT__id_ex_flush_hazard = 1U;
    }
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush = 
        ((IData)(dpi_tb__DOT__dut__DOT__id_ex_flush_hazard) 
         | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_flush));
}

void Vdpi_tb___024root___nba_sequent__TOP__2(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___nba_sequent__TOP__2\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem[vlSelfRef.__VdlyDim0__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0] 
            = vlSelfRef.__VdlyVal__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0;
    }
    if (vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v0) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[0U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[1U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[2U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[3U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[4U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[5U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[6U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[7U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[8U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[9U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[10U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[11U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[12U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[13U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[14U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[15U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[16U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[17U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[18U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[19U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[20U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[21U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[22U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[23U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[24U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[25U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[26U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[27U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[28U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[29U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[30U] = 0U;
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[31U] = 0U;
    }
    if (vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[vlSelfRef.__VdlyDim0__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32] 
            = vlSelfRef.__VdlyVal__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32;
    }
}

void Vdpi_tb___024root___eval_nba(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_nba\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_check_commit__1__Vfuncout;
    __Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_check_commit__1__Vfuncout = 0;
    IData/*31:0*/ __Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_reference_finished__2__Vfuncout;
    __Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_reference_finished__2__Vfuncout = 0;
    IData/*31:0*/ __Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_finish__3__Vfuncout;
    __Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_finish__3__Vfuncout = 0;
    IData/*31:0*/ __Vinline__nba_sequent__TOP__0___Vdly__dpi_tb__DOT__cycle_count;
    __Vinline__nba_sequent__TOP__0___Vdly__dpi_tb__DOT__cycle_count = 0;
    IData/*31:0*/ __Vinline__nba_sequent__TOP__0___VdlyMask__dpi_tb__DOT__cycle_count;
    __Vinline__nba_sequent__TOP__0___VdlyMask__dpi_tb__DOT__cycle_count = 0;
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0 = 0U;
        vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v0 = 0U;
        vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32 = 0U;
        if (((~ (IData)(vlSelfRef.dpi_tb__DOT__rst)) 
             & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_valid))) {
            if (((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_reg_write) 
                 & (0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd)))) {
                VL_WRITEF_NX("COMMIT PC=0x%08h INSTR=0x%08h RD=x%0d VALUE=0x%08h\n",4
                             , '#',32,vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc
                             , '#',32,vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_instr
                             , '#',5,(IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd)
                             , '#',32,vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data);
            } else {
                VL_WRITEF_NX("COMMIT PC=0x%08h INSTR=0x%08h RD=- VALUE=-\n",2
                             , '#',32,vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc
                             , '#',32,vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_instr);
            }
        }
        if (vlSelfRef.dpi_tb__DOT__rst) {
            __Vinline__nba_sequent__TOP__0___Vdly__dpi_tb__DOT__cycle_count = 0U;
            __Vinline__nba_sequent__TOP__0___VdlyMask__dpi_tb__DOT__cycle_count = 0xffffffffU;
        } else {
            __Vinline__nba_sequent__TOP__0___Vdly__dpi_tb__DOT__cycle_count 
                = ((IData)(1U) + vlSelfRef.dpi_tb__DOT__cycle_count);
            __Vinline__nba_sequent__TOP__0___VdlyMask__dpi_tb__DOT__cycle_count = 0xffffffffU;
            if (VL_UNLIKELY((VL_LTES_III(32, 0x000003e8U, vlSelfRef.dpi_tb__DOT__cycle_count)))) {
                VL_WRITEF_NX("[%0t] %%Fatal: dpi_tb.sv:198: Assertion failed in %m: [DPI TB] TIMEOUT after %0d cycles\n",4, 'M',vlSymsp->name(),"dpi_tb", 'T',-9
                             , '#',64,VL_TIME_UNITED_Q(1000)
                             , '~',32,vlSelfRef.dpi_tb__DOT__cycle_count);
                VL_STOP_MT("tb/dpi/dpi_tb.sv", 198, "", false);
            }
        }
        if (((~ (IData)(vlSelfRef.dpi_tb__DOT__rst)) 
             & (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_valid))) {
            vlSelfRef.dpi_tb__DOT__commit_count = ((IData)(1U) 
                                                   + vlSelfRef.dpi_tb__DOT__commit_count);
            Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_check_commit_TOP(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc, vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_instr, 
                                                                              ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_valid) 
                                                                               & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)), (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd), vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data, __Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_check_commit__1__Vfuncout);
            vlSelfRef.dpi_tb__DOT__dpi_status = __Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_check_commit__1__Vfuncout;
            if (VL_UNLIKELY(((0U == vlSelfRef.dpi_tb__DOT__dpi_status)))) {
                VL_WRITEF_NX("\n[DPI TB] Lockstep failure at commit %0d\n[%0t] %%Fatal: dpi_tb.sv:248: Assertion failed in %m: [DPI TB] RTL / C++ architectural mismatch\n",4, 'M',vlSymsp->name(),"dpi_tb", 'T',-9
                             , '~',32,vlSelfRef.dpi_tb__DOT__commit_count
                             , '#',64,VL_TIME_UNITED_Q(1000));
                VL_STOP_MT("tb/dpi/dpi_tb.sv", 248, "", false);
            }
            Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_reference_finished_TOP(__Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_reference_finished__2__Vfuncout);
            vlSelfRef.dpi_tb__DOT__reference_finished 
                = __Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_reference_finished__2__Vfuncout;
            if (VL_UNLIKELY(((0U != vlSelfRef.dpi_tb__DOT__reference_finished)))) {
                Vdpi_tb___024root____Vdpiimwrap_dpi_tb__DOT__dpi_finish_TOP(__Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_finish__3__Vfuncout);
                vlSelfRef.dpi_tb__DOT__dpi_status = __Vinline__nba_sequent__TOP__0___Vfunc_dpi_tb__DOT__dpi_finish__3__Vfuncout;
                if (VL_UNLIKELY(((0U == vlSelfRef.dpi_tb__DOT__dpi_status)))) {
                    VL_WRITEF_NX("[%0t] %%Fatal: dpi_tb.sv:276: Assertion failed in %m: [DPI TB] Golden model final check failed\n",3, 'M',vlSymsp->name(),"dpi_tb", 'T',-9
                                 , '#',64,VL_TIME_UNITED_Q(1000));
                    VL_STOP_MT("tb/dpi/dpi_tb.sv", 276, "", false);
                }
                VL_WRITEF_NX("\n==================================================\n              DPI TEST PASSED\n==================================================\nCycles  : %0d\nCommits : %0d\n==================================================\n\n",2
                             , '~',32,vlSelfRef.dpi_tb__DOT__cycle_count
                             , '~',32,vlSelfRef.dpi_tb__DOT__commit_count);
                VL_FINISH_MT("tb/dpi/dpi_tb.sv", 303, "");
            }
        }
        if (vlSelfRef.dpi_tb__DOT__rst) {
            vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v0 = 1U;
        } else if (((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_reg_write) 
                    & (0U != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd)))) {
            vlSelfRef.__VdlyVal__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32 
                = vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data;
            vlSelfRef.__VdlyDim0__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32 
                = vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd;
            vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32 = 1U;
        }
        if (((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_mem_write) 
             & (0x00000400U > (vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_alu_result 
                               >> 2U)))) {
            vlSelfRef.__VdlyVal__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0 
                = vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_rs2_data;
            vlSelfRef.__VdlyDim0__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0 
                = (0x000003ffU & (vlSelfRef.dpi_tb__DOT__dut__DOT__ex_mem_alu_result 
                                  >> 2U));
            vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0 = 1U;
        }
        vlSelfRef.dpi_tb__DOT__cycle_count = ((__Vinline__nba_sequent__TOP__0___Vdly__dpi_tb__DOT__cycle_count 
                                               & __Vinline__nba_sequent__TOP__0___VdlyMask__dpi_tb__DOT__cycle_count) 
                                              | (vlSelfRef.dpi_tb__DOT__cycle_count 
                                                 & (~ __Vinline__nba_sequent__TOP__0___VdlyMask__dpi_tb__DOT__cycle_count)));
        __Vinline__nba_sequent__TOP__0___VdlyMask__dpi_tb__DOT__cycle_count = 0U;
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vdpi_tb___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        if (vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0) {
            vlSelfRef.dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem[vlSelfRef.__VdlyDim0__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0] 
                = vlSelfRef.__VdlyVal__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0;
        }
        if (vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v0) {
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[0U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[1U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[2U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[3U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[4U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[5U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[6U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[7U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[8U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[9U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[10U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[11U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[12U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[13U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[14U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[15U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[16U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[17U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[18U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[19U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[20U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[21U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[22U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[23U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[24U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[25U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[26U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[27U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[28U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[29U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[30U] = 0U;
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[31U] = 0U;
        }
        if (vlSelfRef.__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32) {
            vlSelfRef.dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[vlSelfRef.__VdlyDim0__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32] 
                = vlSelfRef.__VdlyVal__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32;
        }
    }
}

void Vdpi_tb___024root___timing_ready(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___timing_ready\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h57ac7983__0.ready("@(posedge dpi_tb.clk)");
    }
}

void Vdpi_tb___024root___timing_resume(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___timing_resume\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h57ac7983__0.moveToResumeQueue(
                                                          "@(posedge dpi_tb.clk)");
    vlSelfRef.__VtrigSched_h57ac7983__0.resume("@(posedge dpi_tb.clk)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vdpi_tb___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdpi_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vdpi_tb___024root___eval_phase__act(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_phase__act\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vdpi_tb___024root___eval_triggers_vec__act(vlSelf);
    Vdpi_tb___024root___timing_ready(vlSelf);
    Vdpi_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdpi_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vdpi_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vdpi_tb___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vdpi_tb___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vdpi_tb___024root___eval_phase__inact(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_phase__inact\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("tb/dpi/dpi_tb.sv", 3, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vdpi_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vdpi_tb___024root___eval_phase__nba(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_phase__nba\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vdpi_tb___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vdpi_tb___024root___eval_nba(vlSelf);
        Vdpi_tb___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vdpi_tb___024root___eval(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vdpi_tb___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("tb/dpi/dpi_tb.sv", 3, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("tb/dpi/dpi_tb.sv", 3, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vdpi_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("tb/dpi/dpi_tb.sv", 3, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vdpi_tb___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vdpi_tb___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vdpi_tb___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vdpi_tb___024root____VbeforeTrig_h57ac7983__0(Vdpi_tb___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root____VbeforeTrig_h57ac7983__0\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.dpi_tb__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__dpi_tb__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__dpi_tb__DOT__clk__0 
        = vlSelfRef.dpi_tb__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h57ac7983__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vdpi_tb___024root___eval_debug_assertions(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_debug_assertions\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
