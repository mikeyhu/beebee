#include <iostream>
#include <fstream>
#include <array>
#include "m6502_lib/PageableMemory.cpp"
#include "m6502_lib/Via.cpp"
#include "App.cpp"

static const uint16_t RAM_SIZE = 0x8000;
static const uint16_t OS_SIZE = 0x4000;
static const uint16_t PAGE_SIZE = 0x4000;

std::array<uint8_t, OS_SIZE> loadFile(std::string filename) {
    std::ifstream t;

    t.open(filename);
    if (!t.good()) {
        std::cout << "file not found: " << filename << std::endl;
        exit(2);
    }
    auto buffer = new char[OS_SIZE];
    t.read(buffer, OS_SIZE);
    t.close();

    std::array<uint8_t, OS_SIZE> mem = {};

    for (int i = 0; i < OS_SIZE; ++i) {
        mem[i] = buffer[i];
    }
    delete buffer;
    return mem;
}

int main(int argc, char *argv[]) {
    if(argc!=2) {
        std::cout << "Rom path argument required" << std::endl;
        exit(1);
    }
    std::string romPath(argv[1]);
    auto os = loadFile(romPath + "/Os12.rom");
    auto basic = loadFile(romPath + "/Basic2.rom");
    auto dfs = loadFile(romPath + "/DFS-0.9.rom");

    std::array<uint8_t, 0x8000> mem={};
    int32_t cycles = 0;



    auto memory = new PageableMemory(mem);
    memory->setPageOS(os);
    memory->setPage(basic,0xF);
    memory->setPage(dfs,0x0);
    auto programCounter = 0xD9CD;

    auto app = new App(*memory);
    auto via = new Via(*memory);

    auto cycleCallback = [&cycles,&app]() -> void
    {
        cycles++;
        if(cycles % 1000 == 0) {
            app->renderScreen();
        }
    };

    auto cpu = new CPU(programCounter, *memory, cycleCallback);
    cpu->setBreakLocation(0xfffe);
    via->initialise();
    app->start(cpu, via);

    delete memory;
    return 0;
}