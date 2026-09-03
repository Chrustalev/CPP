#!/bin/bash

# for executable files
mkdir -p iwyu_build && cd iwyu_build
cmake .. -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE="include-what-you-use"
cmake --build . 2>&1
cd .. && rm -rf iwyu_build

# for headers
for f in include/*.hpp; do include-what-you-use -std=c++20 -I./include "$f" 2>&1; done
