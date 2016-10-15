#include <cstdio>
#include <SDL.h>
#include <SDL_opengl.h>
#include <graphics.hpp>

int main(int argc, char** argv) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        printf("Error: SDL_Init\n");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Hello World",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1024, 576,
                                          SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);

    tk::graphics::initializeExtensions();

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    return 0;
}

