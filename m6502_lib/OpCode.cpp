enum OpCode {
#define ITEM(name, code) name=code,

#include "OpCodeMacro.cpp"
};
