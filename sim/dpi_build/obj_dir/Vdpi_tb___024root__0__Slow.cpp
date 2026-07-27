// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdpi_tb.h for the primary calling header

#include "Vdpi_tb__pch.h"

void Vdpi_tb___024root___timing_ready(Vdpi_tb___024root* vlSelf);

VL_ATTR_COLD void Vdpi_tb___024root___eval_static(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_static\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__dpi_tb__DOT__clk__0 
        = vlSelfRef.dpi_tb__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__dpi_tb__DOT__rst__0 
        = vlSelfRef.dpi_tb__DOT__rst;
    Vdpi_tb___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

extern const VlWide<64>/*2047:0*/ Vdpi_tb__ConstPool__CONST_h5089d25d_0;

VL_ATTR_COLD void Vdpi_tb___024root___eval_initial__TOP(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_initial__TOP\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ dpi_tb__DOT__dut__DOT__imem_inst__DOT____VlemExpr_0;
    IData/*31:0*/ dpi_tb__DOT__dut__DOT__imem_inst__DOT__i;
    dpi_tb__DOT__dut__DOT__imem_inst__DOT__i = 0;
    // Body
    dpi_tb__DOT__dut__DOT__imem_inst__DOT__i = 0U;
    while (VL_GTS_III(32, 0x00000400U, dpi_tb__DOT__dut__DOT__imem_inst__DOT__i)) {
        vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__memory[(0x000003ffU 
                                                                 & dpi_tb__DOT__dut__DOT__imem_inst__DOT__i)] = 0x00000013U;
        dpi_tb__DOT__dut__DOT__imem_inst__DOT__i = 
            ((IData)(1U) + dpi_tb__DOT__dut__DOT__imem_inst__DOT__i);
    }
    dpi_tb__DOT__dut__DOT__imem_inst__DOT____VlemExpr_0 
        = VL_VALUEPLUSARGS_INW(2048, "PROGRAM=%s"s, 
                               vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__program_file);
    if ((! dpi_tb__DOT__dut__DOT__imem_inst__DOT____VlemExpr_0)) {
        VL_ASSIGN_W(2048, vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__program_file, Vdpi_tb__ConstPool__CONST_h5089d25d_0);
    }
    VL_WRITEF_NX("\nLoading program: %s\n\n",1, '#',2048,vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__program_file.data());
    VL_READMEM_N(true, 32, 1024, 0, VL_CVT_PACK_STR_NW(64, vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__program_file)
                 ,  &(vlSelfRef.dpi_tb__DOT__dut__DOT__imem_inst__DOT__memory)
                 , 0, ~0ULL);
}

VL_ATTR_COLD void Vdpi_tb___024root___eval_final(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_final\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdpi_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vdpi_tb___024root___eval_phase__stl(Vdpi_tb___024root* vlSelf);

VL_ATTR_COLD void Vdpi_tb___024root___eval_settle(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_settle\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vdpi_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("tb/dpi/dpi_tb.sv", 3, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vdpi_tb___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vdpi_tb___024root___eval_triggers_vec__stl(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_triggers_vec__stl\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vdpi_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdpi_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vdpi_tb___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vdpi_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vdpi_tb___024root___stl_sequent__TOP__0(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___stl_sequent__TOP__0\n"); );
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
    // Body
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
    vlSelfRef.__VdfgRegularize_hebeb780c_0_0 = ((IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_reg_write) 
                                                & (0U 
                                                   != (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_rd)));
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
    vlSelfRef.dpi_tb__DOT__dut__DOT__writeback_data 
        = ((0U == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_wb_sel))
            ? vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_alu_result
            : ((1U == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_wb_sel))
                ? vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_memory_data
                : (vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_pc_plus4 
                   & (- (IData)((2U == (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__mem_wb_wb_sel)))))));
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
    vlSelfRef.dpi_tb__DOT__dut__DOT__id_ex_flush = 
        ((IData)(dpi_tb__DOT__dut__DOT__id_ex_flush_hazard) 
         | (IData)(vlSelfRef.dpi_tb__DOT__dut__DOT__if_id_flush));
}

VL_ATTR_COLD void Vdpi_tb___024root___eval_stl(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_stl\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vdpi_tb___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vdpi_tb___024root___eval_phase__stl(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___eval_phase__stl\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vdpi_tb___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdpi_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vdpi_tb___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vdpi_tb___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vdpi_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdpi_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vdpi_tb___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge dpi_tb.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(posedge dpi_tb.rst)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vdpi_tb___024root___ctor_var_reset(Vdpi_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdpi_tb___024root___ctor_var_reset\n"); );
    Vdpi_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->dpi_tb__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15083007808119607561ull);
    vlSelf->dpi_tb__DOT__rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11092054382699763721ull);
    vlSelf->dpi_tb__DOT__cycle_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15779859848083536308ull);
    vlSelf->dpi_tb__DOT__commit_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7898272143255060662ull);
    vlSelf->dpi_tb__DOT__dpi_status = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3958512756003971202ull);
    vlSelf->dpi_tb__DOT__reference_finished = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5080763469086197309ull);
    vlSelf->dpi_tb__DOT__dut__DOT__pc_current = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15165800400362992651ull);
    vlSelf->dpi_tb__DOT__dut__DOT__pc_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15724315254959680662ull);
    vlSelf->dpi_tb__DOT__dut__DOT__if_id_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14441289080319936506ull);
    vlSelf->dpi_tb__DOT__dut__DOT__if_id_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1747711601497504552ull);
    vlSelf->dpi_tb__DOT__dut__DOT__if_id_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3391037895728551796ull);
    vlSelf->dpi_tb__DOT__dut__DOT__if_id_instruction = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9808970514028480343ull);
    vlSelf->dpi_tb__DOT__dut__DOT__if_id_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4737571008457447526ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13986595935221773274ull);
    vlSelf->dpi_tb__DOT__dut__DOT__ex_mem_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4569063602007874362ull);
    vlSelf->dpi_tb__DOT__dut__DOT__mem_wb_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14827882293869321823ull);
    vlSelf->dpi_tb__DOT__dut__DOT__alu_src_id = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4640362582681757716ull);
    vlSelf->dpi_tb__DOT__dut__DOT__alu_op_id = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9433608823550855878ull);
    vlSelf->dpi_tb__DOT__dut__DOT__alu_a_sel_id = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10375518402577336382ull);
    vlSelf->dpi_tb__DOT__dut__DOT__mem_read_id = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7627141122381184045ull);
    vlSelf->dpi_tb__DOT__dut__DOT__mem_write_id = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8241354040412676834ull);
    vlSelf->dpi_tb__DOT__dut__DOT__branch_id = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3208002364511686869ull);
    vlSelf->dpi_tb__DOT__dut__DOT__jump_id = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 660832608348048033ull);
    vlSelf->dpi_tb__DOT__dut__DOT__jalr_id = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4702762574712473698ull);
    vlSelf->dpi_tb__DOT__dut__DOT__reg_write_id = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16162091050230236958ull);
    vlSelf->dpi_tb__DOT__dut__DOT__wb_sel_id = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16322395910859853604ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15954614851164364391ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_pc_plus4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16898166534248258017ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14496023095055675229ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_rs1_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18101708048457091745ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_rs2_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10004508478617316876ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_immediate = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13105866286416594690ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_rs1 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9126173038418019209ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_rs2 = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15232827916286826359ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 18231644411341061731ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_funct3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7656027950874227821ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_funct7 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 17073431465993430424ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_alu_src = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17212804242996072339ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_alu_op = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 955668712147061360ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_alu_a_sel = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15086768630249724060ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13257083650334325542ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9635420159479680662ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10085279633633651368ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_jump = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17532987858477750674ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_jalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12680088400677798815ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 654805866221899863ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_wb_sel = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12576722050160830417ull);
    vlSelf->dpi_tb__DOT__dut__DOT__id_ex_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8590206770179350717ull);
    vlSelf->dpi_tb__DOT__dut__DOT__forwarded_rs1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2644246246699302216ull);
    vlSelf->dpi_tb__DOT__dut__DOT__forwarded_rs2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15138090124954239063ull);
    vlSelf->dpi_tb__DOT__dut__DOT__alu_operand_a = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3495740433754819504ull);
    vlSelf->dpi_tb__DOT__dut__DOT__alu_operand_b = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6431396400469136836ull);
    vlSelf->dpi_tb__DOT__dut__DOT__alu_ctrl_ex = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7365762760419020265ull);
    vlSelf->dpi_tb__DOT__dut__DOT__ex_mem_alu_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2268099373982725007ull);
    vlSelf->dpi_tb__DOT__dut__DOT__ex_mem_rs2_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17617131768998450251ull);
    vlSelf->dpi_tb__DOT__dut__DOT__ex_mem_pc_plus4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4389485823881884192ull);
    vlSelf->dpi_tb__DOT__dut__DOT__ex_mem_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10068517295659417376ull);
    vlSelf->dpi_tb__DOT__dut__DOT__ex_mem_instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 826422011448580889ull);
    vlSelf->dpi_tb__DOT__dut__DOT__ex_mem_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13034744072301925991ull);
    vlSelf->dpi_tb__DOT__dut__DOT__ex_mem_mem_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 886632408408849939ull);
    vlSelf->dpi_tb__DOT__dut__DOT__ex_mem_mem_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13047902292156113826ull);
    vlSelf->dpi_tb__DOT__dut__DOT__ex_mem_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18266379029866530900ull);
    vlSelf->dpi_tb__DOT__dut__DOT__ex_mem_wb_sel = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7769433786501008106ull);
    vlSelf->dpi_tb__DOT__dut__DOT__mem_wb_memory_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1053890036154314395ull);
    vlSelf->dpi_tb__DOT__dut__DOT__mem_wb_alu_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15446316685728784686ull);
    vlSelf->dpi_tb__DOT__dut__DOT__mem_wb_pc_plus4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10367768645413894271ull);
    vlSelf->dpi_tb__DOT__dut__DOT__mem_wb_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9054745318066822981ull);
    vlSelf->dpi_tb__DOT__dut__DOT__mem_wb_instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7640046534895298008ull);
    vlSelf->dpi_tb__DOT__dut__DOT__mem_wb_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7905318168880842918ull);
    vlSelf->dpi_tb__DOT__dut__DOT__mem_wb_reg_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4054332346905706970ull);
    vlSelf->dpi_tb__DOT__dut__DOT__mem_wb_wb_sel = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17743694987029431437ull);
    vlSelf->dpi_tb__DOT__dut__DOT__writeback_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11269122904312388317ull);
    for (int __Vi0 = 0; __Vi0 < 1024; ++__Vi0) {
        vlSelf->dpi_tb__DOT__dut__DOT__imem_inst__DOT__memory[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3624920541829773478ull);
    }
    VL_SCOPED_RAND_RESET_W(2048, vlSelf->dpi_tb__DOT__dut__DOT__imem_inst__DOT__program_file, __VscopeHash, 17893322546451359800ull);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9964334332490402674ull);
    }
    for (int __Vi0 = 0; __Vi0 < 1024; ++__Vi0) {
        vlSelf->dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15434978428514875596ull);
    }
    vlSelf->__VdfgRegularize_hebeb780c_0_0 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_3 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_7 = 0;
    vlSelf->__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v0 = 0;
    vlSelf->__VdlyVal__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32 = 0;
    vlSelf->__VdlyDim0__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32 = 0;
    vlSelf->__VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32 = 0;
    vlSelf->__VdlyVal__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0 = 0;
    vlSelf->__VdlyDim0__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0 = 0;
    vlSelf->__VdlySet__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__dpi_tb__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__dpi_tb__DOT__rst__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
