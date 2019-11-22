set -e
mkdir -p cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
valgrind --leak-check=yes -s m6502_lib_tests/m6502_lib_tests