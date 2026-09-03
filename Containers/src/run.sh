#!/bin/bash

# супер простой скрипт для максимального быстрого старта работы
# используй:
# ./run.sh -c  -- чтобы очистить файлы сборки
# ./run.sh -е  -- собрать и запустить тесты
# ./run.sh -m  -- собрать и запустить код из main.cpp

b="build"
j=$(nproc)

case $1 in
    -c)   rm -rf "$b"; echo "rm -rf build/" ;;
    -t)   mkdir -p "$b" && cd "$b" && cmake -DBUILD_TEST=ON .. && cmake --build . -j$j && ./s21_containers_tests ;;
    -tf)  mkdir -p "$b" && cd "$b" && cmake -DBUILD_TEST=ON -DCMAKE_CXX_FLAGS="-fsanitize=address -fsanitize=leak -fsanitize=undefined" .. && cmake --build . -j$j && ./s21_containers_tests ;;
    -tmv) mkdir -p "$b" && cd "$b" && cmake -DBUILD_TEST=ON .. && cmake --build . -j$j && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./s21_containers_tests ;;
    -m)   mkdir -p "$b" && cd "$b" && cmake .. && cmake --build . -j$j && ./simple_example ;;
    -mf)  mkdir -p "$b" && cd "$b" && cmake -DCMAKE_CXX_FLAGS="-fsanitize=address -fsanitize=leak -fsanitize=undefined" .. && cmake --build . -j$j && ./simple_example ;;
    -mmv) mkdir -p "$b" && cd "$b" && cmake .. && cmake --build . -j$j && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./simple_example ;;
    -h|*) echo "Usage: $0 [-c|-t|-tf|-tmv|-m|-mf|-mmv] (clean|test|test with fsanitize|test with valgrind + memory|main|main with fsanitize|main with valgrind + memory)" ;;
esac