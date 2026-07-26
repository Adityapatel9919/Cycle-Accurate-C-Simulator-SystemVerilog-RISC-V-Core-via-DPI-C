#!/bin/bash

# ================================================================
# RV32I 5-STAGE PIPELINE
# DIRECTED REGRESSION SCRIPT
# ================================================================

set -u

SIM="sim/cpu_sim"
TEST_DIR="tests/directed"
LOG_DIR="sim/logs"

PASS=0
FAIL=0


# ================================================================
# TEST LIST
#
# Format:
#
# TEST_ID:TEST_NAME
# ================================================================

TESTS=(
    "1:alu"
    "2:forwarding"
    "3:load_store"
    "4:load_use"
    "5:beq_taken"
    "6:beq_not_taken"
    "7:branches"
    "8:jal"
    "9:jalr"
    "10:full_regression"
)


# ================================================================
# CREATE OUTPUT DIRECTORIES
# ================================================================

mkdir -p sim
mkdir -p waves
mkdir -p "$LOG_DIR"


# ================================================================
# HEADER
# ================================================================

echo ""
echo "=================================================="
echo "       RV32I PIPELINE REGRESSION"
echo "=================================================="
echo ""


# ================================================================
# BUILD RTL
# ================================================================

echo "[BUILD] Compiling RTL..."
echo ""


iverilog -g2012 -Wall \
-o "$SIM" \
rtl/alu/alu.sv \
rtl/regfile/regfile.sv \
rtl/decoder/imm_gen.sv \
rtl/decoder/control_unit.sv \
rtl/decoder/alu_control.sv \
rtl/core/pc.sv \
rtl/core/branch_unit.sv \
rtl/memory/instruction_memory.sv \
rtl/memory/data_memory.sv \
rtl/pipeline/if_id.sv \
rtl/pipeline/id_ex.sv \
rtl/pipeline/ex_mem.sv \
rtl/pipeline/mem_wb.sv \
rtl/hazard/forwarding_unit.sv \
rtl/hazard/hazard_unit.sv \
rtl/core/top.sv \
tb/basic/top_tb.sv


# ================================================================
# CHECK BUILD
# ================================================================

if [ $? -ne 0 ]; then

    echo ""
    echo "=================================================="
    echo "                  BUILD FAILED"
    echo "=================================================="
    echo ""

    exit 1

fi


echo ""
echo "[BUILD] PASSED"
echo ""


# ================================================================
# RUN DIRECTED TESTS
# ================================================================

for ENTRY in "${TESTS[@]}"
do

    # ------------------------------------------------------------
    # Extract ID and name
    #
    # Example:
    #
    # ENTRY = 4:load_use
    #
    # TEST_ID = 4
    # TEST     = load_use
    # ------------------------------------------------------------

    TEST_ID="${ENTRY%%:*}"
    TEST="${ENTRY##*:}"

    HEX="$TEST_DIR/$TEST.hex"
    LOG="$LOG_DIR/$TEST.log"


    echo "--------------------------------------------------"
    echo "[TEST $TEST_ID] $TEST"
    echo "--------------------------------------------------"


    # ------------------------------------------------------------
    # Check HEX exists
    # ------------------------------------------------------------

    if [ ! -f "$HEX" ]; then

        echo "[FAIL] Missing HEX file:"
        echo "       $HEX"
        echo ""

        FAIL=$((FAIL + 1))

        continue

    fi


    # ------------------------------------------------------------
    # Run simulation
    # ------------------------------------------------------------

    vvp "$SIM" \
        +TEST_ID="$TEST_ID" \
        +PROGRAM="$HEX" \
        > "$LOG" 2>&1


    VVP_STATUS=$?


    # ------------------------------------------------------------
    # Check simulator status
    # ------------------------------------------------------------

    if [ "$VVP_STATUS" -ne 0 ]; then

        echo "[FAIL] Simulator returned error code $VVP_STATUS"
        echo ""
        echo "Simulation log:"
        echo ""

        cat "$LOG"

        echo ""

        FAIL=$((FAIL + 1))

        continue

    fi


    # ------------------------------------------------------------
    # Check testbench result
    # ------------------------------------------------------------

    if grep -q "ALL TESTS PASSED" "$LOG"; then

        echo "[PASS] $TEST"

        PASS=$((PASS + 1))

    else

        echo "[FAIL] $TEST"
        echo ""
        echo "Simulation output:"
        echo ""

        cat "$LOG"

        echo ""

        FAIL=$((FAIL + 1))

    fi


    echo ""

done


# ================================================================
# REGRESSION SUMMARY
# ================================================================

TOTAL=$((PASS + FAIL))


echo ""
echo "=================================================="
echo "              REGRESSION SUMMARY"
echo "=================================================="
echo ""

echo "Total tests : $TOTAL"
echo "Passed      : $PASS"
echo "Failed      : $FAIL"

echo ""


# ================================================================
# FINAL STATUS
# ================================================================

if [ "$FAIL" -eq 0 ]; then

    echo "=================================================="
    echo "              REGRESSION PASSED"
    echo "=================================================="
    echo ""

    exit 0

else

    echo "=================================================="
    echo "              REGRESSION FAILED"
    echo "=================================================="
    echo ""

    echo "Failed-test logs are available in:"
    echo ""
    echo "    $LOG_DIR/"
    echo ""

    exit 1

fi