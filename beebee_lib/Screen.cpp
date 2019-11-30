#include <SDL2/SDL_video.h>
#ifndef CLASS_MEMORY
#define CLASS_MEMORY
#include "../m6502_lib/Memory.cpp"
#endif

template<std::size_t MEM_SIZE>

class Screen {
    static const int SCREEN_WIDTH = 1024;
    static const int SCREEN_HEIGHT = 768;
    Memory<MEM_SIZE> *memory;

    SDL_Window *window = NULL;
public:
    explicit Screen(Memory<MEM_SIZE> &mem)
            : memory(&mem) {

    }

    void start() {
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    }
};

