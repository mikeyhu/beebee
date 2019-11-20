enum OpCode {
#define OPCODE(name, code, mode) name=code,

#include "OpCodeMacro.cpp"
};
