#include <SDL.h>
#include <cstring>
#include "beebee_lib/Teletext.cpp"

#ifndef BEEBEE_PAGEABLEMEMORY

#include "m6502_lib/PageableMemory.cpp"

#endif

#ifndef BEEBEE_CPU
#include "m6502_lib/CPU.cpp"

#endif
#ifndef BEEBEE_VIA
#include "m6502_lib/Via.cpp"

#endif

class App {
    static const int SCREEN_WIDTH = 1280;
    static const int SCREEN_HEIGHT = 800;
    static const int MODE7_CHAR_HEIGHT = SCREEN_HEIGHT / 25;
    static const int MODE7_CHAR_WIDTH = SCREEN_WIDTH / 40;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;

    bool quit;

    Memory<0x8000> *memory;
    int32_t cycles = 0;
public:
    App(Memory<0x8000> &memory) : memory(&memory) {}

    void start(CPU<0x8000> *cpu, Via<0x8000> *via) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        }
        window = SDL_CreateWindow("Beebee BBC Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 6, 10);

        SDL_RenderClear(renderer);
        for (uint16_t i = 0x7c00; i <= 0x7fff; i++) {
            auto letter = Teletext::getCharacter(memory->getValue(i));
            SDL_UpdateTexture(texture, NULL, letter, 6 * 4);
            SDL_Rect dst;
            dst.x = 12 * ((i - 0x7bff) % 0x28);
            dst.y = 20 * ((i - 0x7bff) / 0x28);
            dst.w = 12;
            dst.h = 20;
            SDL_RenderCopy(renderer, texture, NULL, &dst);
        }
        SDL_RenderPresent(renderer);

        SDL_Event e;
        while (!quit) {
            cpu->runUntilInteruptable();
            if(memory->needsScreenRefresh()) {
                renderScreen();
                memory->setScreenRefresh(false);
            }
            std::cout << std::dec << "cycles:" << cycles << std::endl;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                if (e.type == SDL_KEYDOWN) {
                    quit = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    quit = true;
                }
            }
        }
    }

    void renderScreen() {
        SDL_RenderClear(renderer);
        for (uint16_t i = 0x7c00; i <= 0x7fff; i++) {
            auto letter = Teletext::getCharacter(memory->getValue(i));
            SDL_UpdateTexture(texture, NULL, letter, 6 * 4);
            SDL_Rect dst;
            dst.x = MODE7_CHAR_WIDTH * ((i - 0x7bff) % 0x28);
            dst.y = MODE7_CHAR_HEIGHT * ((i - 0x7bff) / 0x28);
            dst.w = MODE7_CHAR_WIDTH;
            dst.h = MODE7_CHAR_HEIGHT;
            SDL_RenderCopy(renderer, texture, NULL, &dst);
        }
        SDL_RenderPresent(renderer);
    }
};