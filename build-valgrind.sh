set -e
mkdir -p cmake-build-debug
cd cmake-build-debug
conan install .. --install-folder .
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
valgrind --leak-check=yes -s bin/m6502_lib_tests