#!/bin/bash

set -e

echo "🚀 Building BMS project..."

rm -rf build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_CXX_FLAGS="-Wno-deprecated-declarations"
ln -sf build/compile_commands.json compile_commands.json
cmake --build build

echo "✅ Build complete"