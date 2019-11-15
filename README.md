# Beebee

A 6502 emulator written in C++ so that I can relearn modern C++.

## m6502_lib

Contains the CPU emulator.

## m6502_lib_tests

Tests for the CPU emulator covering the different documented OpCodes.

## m6502_lib_suite

Runs the 6502 assembler tests found here: https://github.com/Klaus2m5/6502_65C02_functional_tests
Copy the binary found here: https://github.com/Klaus2m5/6502_65C02_functional_tests/blob/master/bin_files/6502_functional_test.bin
Description of the binary is available here: https://github.com/Klaus2m5/6502_65C02_functional_tests/blob/master/bin_files/6502_functional_test.lst

## Running the tests
```
./build-debug.sh
# this will use cmake, then make then will run the test binary
```

