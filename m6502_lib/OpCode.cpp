enum OpCode {
#define OPCODE(name, code, function, mode) name=code,

#include "OpCodeMacro.cpp"
};
