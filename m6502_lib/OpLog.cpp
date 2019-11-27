#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#ifndef CLASS_OPCODE
#define CLASS_OPCODE
#include "OpCode.cpp"
#endif

class OpLog {
    OpCode opCode;
    uint16_t programCounter;
    std::string log="";

    static std::string OpCodeToString(OpCode value) {
        switch (value) {
#define OPCODE(name, code, function, mode) case code: return #name;

#include "OpCodeMacro.cpp"
        }
        return "";
    }

public:
    OpLog(OpCode opCode, uint16_t programCounter) : opCode(opCode), programCounter(programCounter) {}

    void addToLog(std::string &entry) {
        log.append(entry);
    }

    std::string ToString() {
        std::stringstream buffer;
        buffer << std::setw(22) << OpCodeToString(opCode) << " PC:" << std::hex << (int)programCounter;
        return buffer.str();
    }
};