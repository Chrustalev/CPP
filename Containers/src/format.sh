#!/bin/bash

case $1 in
    -i) find . \( -name "*.hpp" -o -name "*.cpp" -o -name "*.cc" -o -name "*.h" \) ! -path "./build/*" | xargs clang-format -i --style=file ;; 
    -n) find . \( -name "*.hpp" -o -name "*.cpp" -o -name "*.cc" -o -name "*.h" \) ! -path "./build/*" | xargs clang-format -n --style=file ;;
    -h|*) echo "Usage: $0 [-i|-n] (correct files with clang-format|check clang-format in ur files)" ;; 
esac
