#!/bin/bash

set -u

# ============================================================
# RV32I COMPLETE PROJECT REGRESSION
# ============================================================
#
# Runs:
#
#   1. RTL directed regression
#   2. C++ golden-model regression
#   3. Offline RTL <-> C++ differential regression
#   4. DPI-C build
#   5. DPI-C lockstep regression
#
# ============================================================

echo
echo "=================================================="
echo "        RV32I COMPLETE VERIFICATION SUITE"
echo "=================================================="
echo


# ============================================================
# CONFIGURATION
# ============================================================

RTL_REGRESSION="./scripts/run_regression.sh"
CPP_REGRESSION="scripts/run_cpp_regression.sh"
DIFF_REGRESSION="./scripts/run_differential.sh"

DPI_BUILD="./scripts/build_dpi.sh"
DPI_REGRESSION="./scripts/run_dpi_regression.sh"


# ============================================================
# RESULT COUNTERS
# ============================================================

passed=0
failed=0

declare -a failed_stages


# ============================================================
# RUN ONE STAGE
# ============================================================

run_stage()
{
    local name="$1"
    local command="$2"

    echo
    echo "=================================================="
    echo " STAGE: $name"
    echo "=================================================="
    echo

    if [ ! -f "$command" ]; then

        echo "[FAIL] Script not found:"
        echo "       $command"

        failed=$((failed + 1))
        failed_stages+=("$name")

        return
    fi


    if [ ! -x "$command" ]; then
        chmod +x "$command"
    fi


    "$command"

    local status=$?


    echo

    if [ "$status" -eq 0 ]; then

        echo "--------------------------------------------------"
        echo "[STAGE PASS] $name"
        echo "--------------------------------------------------"

        passed=$((passed + 1))

    else

        echo "--------------------------------------------------"
        echo "[STAGE FAIL] $name"
        echo "--------------------------------------------------"

        failed=$((failed + 1))
        failed_stages+=("$name")

    fi
}


# ============================================================
# 1. RTL DIRECTED REGRESSION
# ============================================================

run_stage \
    "RTL DIRECTED REGRESSION" \
    "$RTL_REGRESSION"


# ============================================================
# 2. C++ GOLDEN MODEL REGRESSION
# ============================================================

run_stage \
    "C++ GOLDEN MODEL REGRESSION" \
    "$CPP_REGRESSION"


# ============================================================
# 3. OFFLINE DIFFERENTIAL REGRESSION
# ============================================================

run_stage \
    "OFFLINE DIFFERENTIAL REGRESSION" \
    "$DIFF_REGRESSION"


# ============================================================
# 4. DPI-C BUILD
# ============================================================

run_stage \
    "DPI-C BUILD" \
    "$DPI_BUILD"


# ============================================================
# 5. DPI-C LOCKSTEP REGRESSION
# ============================================================

run_stage \
    "DPI-C LOCKSTEP REGRESSION" \
    "$DPI_REGRESSION"


# ============================================================
# FINAL PROJECT SUMMARY
# ============================================================

total=$((passed + failed))

echo
echo
echo "=================================================="
echo "           PROJECT REGRESSION SUMMARY"
echo "=================================================="
echo

echo "Verification stages : $total"
echo "Passed              : $passed"
echo "Failed              : $failed"

echo


# ============================================================
# FINAL RESULT
# ============================================================

if [ "$failed" -eq 0 ]; then

    echo "=================================================="
    echo "       ALL VERIFICATION STAGES PASSED"
    echo "=================================================="
    echo
    echo "RTL directed regression       : PASS"
    echo "C++ golden-model regression   : PASS"
    echo "Offline differential          : PASS"
    echo "DPI-C build                   : PASS"
    echo "DPI-C lockstep regression     : PASS"
    echo
    echo "=================================================="
    echo "          RV32I PROJECT: PASS"
    echo "=================================================="
    echo

    exit 0

else

    echo "=================================================="
    echo "       PROJECT VERIFICATION FAILED"
    echo "=================================================="
    echo

    echo "Failed stages:"

    for stage in "${failed_stages[@]}"; do
        echo "  - $stage"
    done

    echo
    echo "=================================================="

    exit 1
fi