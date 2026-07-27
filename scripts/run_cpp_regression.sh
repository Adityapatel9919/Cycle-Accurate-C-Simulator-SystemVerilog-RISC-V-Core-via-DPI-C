#!/bin/bash

set -e

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"

BUILD_DIR="$ROOT_DIR/cpp_model/build"

mkdir -p "$BUILD_DIR"

echo "=================================================="
echo "       RV32I C++ REFERENCE REGRESSION"
echo "=================================================="

echo
echo "[BUILD] Compiling C++ reference model..."

clang++ \
    -std=c++17 \
    -Wall \
    -Wextra \
    -I"$ROOT_DIR/cpp_model/include" \
    "$ROOT_DIR/cpp_model/src/cpu.cpp" \
    "$ROOT_DIR/cpp_model/src/decoder.cpp" \
    "$ROOT_DIR/cpp_model/src/memory.cpp" \
    "$ROOT_DIR/cpp_model/tests/test_runner.cpp" \
    -o "$BUILD_DIR/cpp_regression"

echo "[BUILD] PASSED"
echo

cd "$ROOT_DIR"

"$BUILD_DIR/cpp_regression"