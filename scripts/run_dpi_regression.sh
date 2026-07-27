#!/bin/bash

set -u

# ============================================================
# RV32I DPI-C LOCKSTEP REGRESSION
# ============================================================

echo "=================================================="
echo "          RV32I DPI-C REGRESSION"
echo "=================================================="
echo


# ============================================================
# CONFIGURATION
# ============================================================

DPI_SIM="sim/dpi_build/obj_dir/Vdpi_tb"

LOG_DIR="sim/logs/dpi"

mkdir -p "$LOG_DIR"


# ============================================================
# TEST DEFINITIONS
#
# Format:
#
#     test_name:program_file
#
# TEST_ID is not required by the DPI testbench.
# ============================================================

TESTS=(
    "alu:tests/directed/alu.hex"
    "forwarding:tests/directed/forwarding.hex"
    "load_store:tests/directed/load_store.hex"
    "load_use:tests/directed/load_use.hex"
    "beq_taken:tests/directed/beq_taken.hex"
    "beq_not_taken:tests/directed/beq_not_taken.hex"
    "branches:tests/directed/branches.hex"
    "jal:tests/directed/jal.hex"
    "jalr:tests/directed/jalr.hex"
    "full_regression:tests/directed/full_regression.hex"
)


# ============================================================
# CHECK DPI SIMULATOR
# ============================================================

if [ ! -x "$DPI_SIM" ]; then

    echo "[ERROR] DPI simulation binary not found:"
    echo
    echo "        $DPI_SIM"
    echo
    echo "Build it first with:"
    echo
    echo "        ./scripts/build_dpi.sh"
    echo

    exit 1
fi


# ============================================================
# REGRESSION COUNTERS
# ============================================================

passed=0
failed=0


# ============================================================
# RUN TESTS
# ============================================================

for test in "${TESTS[@]}"; do

    IFS=':' read -r \
        name \
        program \
        <<< "$test"

    echo "--------------------------------------------------"
    echo "[DPI TEST] $name"
    echo "--------------------------------------------------"


    # --------------------------------------------------------
    # Verify program exists
    # --------------------------------------------------------

    if [ ! -f "$program" ]; then

        echo "[FAIL] Program file not found:"
        echo "       $program"
        echo

        failed=$((failed + 1))

        continue
    fi


    # --------------------------------------------------------
    # Log file
    # --------------------------------------------------------

    log_file="$LOG_DIR/${name}.log"


    # --------------------------------------------------------
    # Run DPI lockstep simulation
    # --------------------------------------------------------

    "$DPI_SIM" \
        +PROGRAM="$program" \
        > "$log_file" 2>&1

    status=$?


    # --------------------------------------------------------
    # Determine result
    # --------------------------------------------------------

    if [ "$status" -eq 0 ] &&
       grep -q "DPI LOCKSTEP VERIFICATION PASSED" "$log_file"
    then

        echo "[PASS] $name"

        passed=$((passed + 1))

    else

        echo "[FAIL] $name"
        echo "       Log: $log_file"

        failed=$((failed + 1))

    fi

    echo

done


# ============================================================
# SUMMARY
# ============================================================

total=$((passed + failed))

echo
echo "=================================================="
echo "          DPI REGRESSION SUMMARY"
echo "=================================================="
echo

echo "Total tests : $total"
echo "Passed      : $passed"
echo "Failed      : $failed"

echo


# ============================================================
# FINAL RESULT
# ============================================================

if [ "$failed" -eq 0 ]; then

    echo "=================================================="
    echo "          DPI REGRESSION PASSED"
    echo "=================================================="
    echo
    echo "All RTL commits matched the C++ golden model."
    echo
    echo "Logs:"
    echo
    echo "    $LOG_DIR/"
    echo

    exit 0

else

    echo "=================================================="
    echo "          DPI REGRESSION FAILED"
    echo "=================================================="
    echo
    echo "Failed-test logs are available in:"
    echo
    echo "    $LOG_DIR/"
    echo

    exit 1
fi