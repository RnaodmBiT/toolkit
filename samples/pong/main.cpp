#include <cstdio>
#include <SDL.h>

#include <graphics.hpp>
#include <core.hpp>

#include "game.hpp"

void loadResources(ResourceCollection& resources) {
    tk_info("Loading resources...");

    resources.load<Shader>("shader",
                           "data/shaders/shape.vert",
                           "data/shaders/shape.frag");

    resources.load<Font>("font",
                         "data/fonts/caviar.ttf");

    tk_info("Finished loading resources.");
}

int main(int argc, char** argv) {

    tk::core::initLog("pong.log");

    tk_assert(SDL_Init(SDL_INIT_EVERYTHING) == 0, "SDL_Init failed");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_Window* window = SDL_CreateWindow("Pong",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1024, 576,
                                          SDL_WINDOW_OPENGL);
    tk_assert(window, "SDL_CreateWindow failed");

    SDL_GLContext context = SDL_GL_CreateContext(window);
    tk_assert(context, "SDL_GL_CreateContext failed");

    tk_assert(tk::graphics::initialize(), "Error initializing the graphics");

    tk::core::ResourceCollection resources;
    loadResources(resources);

    tk::core::State* state = new Game();
    state->create(resources);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        tk::core::State* newState = state->update();
        if (newState) {
            state->shutdown();
            state = newState;
            state->create(resources);
        }

        state->draw();

        SDL_GL_SwapWindow(window);
    }

    return 0;
}

