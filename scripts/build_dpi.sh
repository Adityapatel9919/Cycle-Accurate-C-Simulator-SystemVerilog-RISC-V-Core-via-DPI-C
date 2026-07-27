#!/bin/bash

set -euo pipefail

echo "=================================================="
echo "          RV32I DPI-C BUILD"
echo "=================================================="
echo

# ============================================================
# DIRECTORIES
# ============================================================

BUILD_DIR="sim/dpi_build"
OBJ_DIR="$BUILD_DIR/obj_dir"

mkdir -p "$BUILD_DIR"


# ============================================================
# CHECK VERILATOR
# ============================================================

if ! command -v verilator >/dev/null 2>&1; then
    echo "[ERROR] Verilator not found."
    exit 1
fi

echo "[INFO] $(verilator --version)"
echo


# ============================================================
# CLEAN PREVIOUS BUILD
# ============================================================

echo "[BUILD] Cleaning previous DPI build..."

rm -rf "$OBJ_DIR"


# ============================================================
# RTL SOURCES
# ============================================================

RTL_SOURCES=(
    rtl/core/top.sv

    rtl/core/pc.sv
    rtl/core/branch_unit.sv

    rtl/pipeline/if_id.sv
    rtl/pipeline/id_ex.sv
    rtl/pipeline/ex_mem.sv
    rtl/pipeline/mem_wb.sv

    rtl/decoder/control_unit.sv
    rtl/decoder/alu_control.sv
    rtl/decoder/imm_gen.sv

    rtl/alu/alu.sv

    rtl/regfile/regfile.sv

    rtl/hazard/hazard_unit.sv
    rtl/hazard/forwarding_unit.sv

    rtl/memory/instruction_memory.sv
    rtl/memory/data_memory.sv
)


# ============================================================
# SYSTEMVERILOG DPI TESTBENCH
# ============================================================

TB_SOURCE="tb/dpi/dpi_tb.sv"


# ============================================================
# C++ GOLDEN MODEL SOURCES
# ============================================================

CPP_SOURCES=(
    cpp_model/src/cpu.cpp
    cpp_model/src/decoder.cpp
    cpp_model/src/memory.cpp
    cpp_model/dpi/dpi_bridge.cpp
)


# ============================================================
# VERIFY SOURCE FILES
# ============================================================

echo "[BUILD] Checking source files..."

for file in \
    "${RTL_SOURCES[@]}" \
    "$TB_SOURCE" \
    "${CPP_SOURCES[@]}"
do
    if [ ! -f "$file" ]; then
        echo "[ERROR] Missing source file:"
        echo "        $file"
        exit 1
    fi
done

echo "[BUILD] Source check passed."
echo


# ============================================================
# VERILATOR BUILD
# ============================================================

echo "[BUILD] Building DPI simulation..."
echo

verilator \
    --binary \
    --timing \
    --sv \
    --top-module dpi_tb \
    --Mdir "$OBJ_DIR" \
    -Wall \
    -Wno-fatal \
    -Irtl/core \
    -Irtl/pipeline \
    -Irtl/decoder \
    -Irtl/alu \
    -Irtl/regfile \
    -Irtl/hazard \
    -Irtl/memory \
    -CFLAGS "-std=c++17 -I$(pwd)/cpp_model/include" \
    "${RTL_SOURCES[@]}" \
    "$TB_SOURCE" \
    "${CPP_SOURCES[@]}"


# ============================================================
# CHECK RESULT
# ============================================================

SIM_BINARY="$OBJ_DIR/Vdpi_tb"

if [ ! -x "$SIM_BINARY" ]; then
    echo
    echo "[ERROR] DPI simulation binary was not generated:"
    echo "        $SIM_BINARY"
    exit 1
fi


echo
echo "=================================================="
echo "             DPI BUILD PASSED"
echo "=================================================="
echo
echo "Simulation binary:"
echo
echo "    $SIM_BINARY"
echo
echo "Run example:"
echo
echo "    $SIM_BINARY +PROGRAM=tests/directed/alu.hex"
echo