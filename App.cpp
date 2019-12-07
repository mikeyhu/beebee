#include <SDL.h>
#include <cstring>
#include "beebee_lib/Teletext.cpp"

#ifndef BEEBEE_PAGEABLEMEMORY

#include "m6502_lib/PageableMemory.cpp"

#endif

class App {
    static const int SCREEN_WIDTH = 1280;
    static const int SCREEN_HEIGHT = 800;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;

    bool quit;

    Memory<0x8000> *memory;
public:
    App(Memory<0x8000> &memory) : memory(&memory) {}

    void start() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        }
        window = SDL_CreateWindow("Beebee BBC Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 6, 10);

        SDL_RenderClear(renderer);

        for (uint16_t i = 0x7c00; i <= 0x7fff; i++) {
            memory->setValue(i, 0x20);
        }

        memory->setValue(0x7c28, 0x42);
        memory->setValue(0x7c29, 0x42);
        memory->setValue(0x7c2a, 0x43);
        memory->setValue(0x7c2b, 0x20);
        memory->setValue(0x7c2c, 0x43);
        memory->setValue(0x7c2d, 0x6f);
        memory->setValue(0x7c2e, 0x6d);
        memory->setValue(0x7c2f, 0x70);
        memory->setValue(0x7c30, 0x75);
        memory->setValue(0x7c31, 0x74);
        memory->setValue(0x7c32, 0x65);
        memory->setValue(0x7c33, 0x72);
        memory->setValue(0x7c34, 0x20);
        memory->setValue(0x7c35, 0x33);
        memory->setValue(0x7c36, 0x32);
        memory->setValue(0x7c37, 0x4b);
        memory->setValue(0x7c78, 0x42);
        memory->setValue(0x7c79, 0x41);
        memory->setValue(0x7c7a, 0x53);
        memory->setValue(0x7c7b, 0x49);
        memory->setValue(0x7c7c, 0x43);
        memory->setValue(0x7cc8, 0x3e);

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
};