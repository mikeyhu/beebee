#include <SDL.h>
#include <cstring>

class App {
    static const int SCREEN_WIDTH = 1280;
    static const int SCREEN_HEIGHT = 800;

    SDL_Window* window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Texture * texture = NULL;

    bool quit;

    static char from6to8(char sixBit) {
        return (sixBit * 255) / 63;
    }
public:
    App() {}

    void start() {
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        }
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 320, 200);

        Uint32 palette[256];
        for(int i=0; i< 256; i++) {
            unsigned char r = from6to8(i);
            unsigned char g = from6to8(i);
            unsigned char b = from6to8(i);
            palette[i] = 255 << 24 | r << 16 | g << 8 | b;
        }

        Uint32 * pixels = new Uint32[320 * 200];
        for(int i = 0; i< 64000; i++) {
            auto col = palette[i % 255];
            pixels[i] = col;

        }
        SDL_UpdateTexture(texture, NULL, pixels,320 * 4);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
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