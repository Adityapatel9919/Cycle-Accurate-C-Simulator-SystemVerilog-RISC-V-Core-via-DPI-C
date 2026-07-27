// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vdpi_tb.h for the primary calling header

#ifndef VERILATED_VDPI_TB___024ROOT_H_
#define VERILATED_VDPI_TB___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vdpi_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vdpi_tb___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ dpi_tb__DOT__clk;
        CData/*0:0*/ dpi_tb__DOT__rst;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__pc_write;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__if_id_write;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__if_id_flush;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__if_id_valid;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__id_ex_valid;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__ex_mem_valid;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__mem_wb_valid;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__alu_src_id;
        CData/*1:0*/ dpi_tb__DOT__dut__DOT__alu_op_id;
        CData/*1:0*/ dpi_tb__DOT__dut__DOT__alu_a_sel_id;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__mem_read_id;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__mem_write_id;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__branch_id;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__jump_id;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__jalr_id;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__reg_write_id;
        CData/*1:0*/ dpi_tb__DOT__dut__DOT__wb_sel_id;
        CData/*4:0*/ dpi_tb__DOT__dut__DOT__id_ex_rs1;
        CData/*4:0*/ dpi_tb__DOT__dut__DOT__id_ex_rs2;
        CData/*4:0*/ dpi_tb__DOT__dut__DOT__id_ex_rd;
        CData/*2:0*/ dpi_tb__DOT__dut__DOT__id_ex_funct3;
        CData/*6:0*/ dpi_tb__DOT__dut__DOT__id_ex_funct7;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__id_ex_alu_src;
        CData/*1:0*/ dpi_tb__DOT__dut__DOT__id_ex_alu_op;
        CData/*1:0*/ dpi_tb__DOT__dut__DOT__id_ex_alu_a_sel;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__id_ex_mem_read;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__id_ex_mem_write;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__id_ex_branch;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__id_ex_jump;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__id_ex_jalr;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__id_ex_reg_write;
        CData/*1:0*/ dpi_tb__DOT__dut__DOT__id_ex_wb_sel;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__id_ex_flush;
        CData/*3:0*/ dpi_tb__DOT__dut__DOT__alu_ctrl_ex;
        CData/*4:0*/ dpi_tb__DOT__dut__DOT__ex_mem_rd;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__ex_mem_mem_read;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__ex_mem_mem_write;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__ex_mem_reg_write;
        CData/*1:0*/ dpi_tb__DOT__dut__DOT__ex_mem_wb_sel;
        CData/*4:0*/ dpi_tb__DOT__dut__DOT__mem_wb_rd;
        CData/*0:0*/ dpi_tb__DOT__dut__DOT__mem_wb_reg_write;
        CData/*1:0*/ dpi_tb__DOT__dut__DOT__mem_wb_wb_sel;
        CData/*0:0*/ __VdfgRegularize_hebeb780c_0_0;
        CData/*0:0*/ __VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v0;
        CData/*4:0*/ __VdlyDim0__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32;
        CData/*0:0*/ __VdlySet__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32;
        CData/*0:0*/ __VdlySet__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__dpi_tb__DOT__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__dpi_tb__DOT__rst__0;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VinactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        SData/*9:0*/ __VdlyDim0__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0;
        IData/*31:0*/ dpi_tb__DOT__cycle_count;
        IData/*31:0*/ dpi_tb__DOT__commit_count;
        IData/*31:0*/ dpi_tb__DOT__dpi_status;
        IData/*31:0*/ dpi_tb__DOT__reference_finished;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__pc_current;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__if_id_pc;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__if_id_instruction;
    };
    struct {
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__id_ex_pc;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__id_ex_pc_plus4;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__id_ex_instr;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__id_ex_rs1_data;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__id_ex_rs2_data;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__id_ex_immediate;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__forwarded_rs1;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__forwarded_rs2;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__alu_operand_a;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__alu_operand_b;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__ex_mem_alu_result;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__ex_mem_rs2_data;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__ex_mem_pc_plus4;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__ex_mem_pc;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__ex_mem_instr;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__mem_wb_memory_data;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__mem_wb_alu_result;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__mem_wb_pc_plus4;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__mem_wb_pc;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__mem_wb_instr;
        IData/*31:0*/ dpi_tb__DOT__dut__DOT__writeback_data;
        VlWide<64>/*2047:0*/ dpi_tb__DOT__dut__DOT__imem_inst__DOT__program_file;
        IData/*31:0*/ __VdfgRegularize_hebeb780c_0_3;
        IData/*31:0*/ __VdfgRegularize_hebeb780c_0_7;
        IData/*31:0*/ __VdlyVal__dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs__v32;
        IData/*31:0*/ __VdlyVal__dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem__v0;
        IData/*31:0*/ __VactIterCount;
        IData/*31:0*/ __VinactIterCount;
        IData/*31:0*/ __Vi;
        VlUnpacked<IData/*31:0*/, 1024> dpi_tb__DOT__dut__DOT__imem_inst__DOT__memory;
        VlUnpacked<IData/*31:0*/, 32> dpi_tb__DOT__dut__DOT__regfile_inst__DOT__regs;
        VlUnpacked<IData/*31:0*/, 1024> dpi_tb__DOT__dut__DOT__dmem_inst__DOT__mem;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };
    std::string dpi_tb__DOT__program_file;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h57ac7983__0;

    // INTERNAL VARIABLES
    Vdpi_tb__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vdpi_tb___024root(Vdpi_tb__Syms* symsp, const char* namep);
    ~Vdpi_tb___024root();
    VL_UNCOPYABLE(Vdpi_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
