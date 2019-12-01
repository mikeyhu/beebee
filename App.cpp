#include <SDL.h>
#include <cstring>
#include "beebee_lib/Teletext.cpp"

class App {
    static const int SCREEN_WIDTH = 1280;
    static const int SCREEN_HEIGHT = 800;

    SDL_Window* window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Texture * texture = NULL;

    bool quit;

public:
    App() {}

    void start() {
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        }
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 6, 10);

        SDL_RenderClear(renderer);

        for(uint8_t i=0x20;i<0x80; i++) {
            auto letter = Teletext::getCharacter(i);
            SDL_UpdateTexture(texture, NULL, letter, 6 * 4);
            SDL_Rect dst;
            dst.x = 24*(i%0xf);
            dst.y = 40*(i/0xf);
            dst.w = 24;
            dst.h = 40;
            SDL_RenderCopy(renderer, texture, NULL, &dst);
        }

        SDL_RenderPresent(renderer);

        SDL_Event e;
        while (!quit){
            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                    quit = true;
                }
                if (e.type == SDL_KEYDOWN){
                    quit = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN){
                    quit = true;
                }
            }
        }
    }
};