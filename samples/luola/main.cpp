#include <cstdio>
#include <SDL.h>


#include "global.hpp"
#include "title.hpp"

#include <graphics.hpp>
#include <core.hpp>
#include <net.hpp>

using namespace tk::core;
using namespace tk::graphics;
using namespace tk::net;

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

    initLog("luola.log");

    tk::net::initialize();

    Global global;
    global.resolution = Vec2i{ 1024, 576 };

    tk_assert(SDL_Init(SDL_INIT_EVERYTHING) == 0, "SDL_Init failed");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    SDL_Window* window = SDL_CreateWindow("Luola",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          global.resolution.x, global.resolution.y,
                                          SDL_WINDOW_OPENGL);
    tk_assert(window, "SDL_CreateWindow failed");

    SDL_GLContext context = SDL_GL_CreateContext(window);
    tk_assert(context, "SDL_GL_CreateContext failed");

    tk_assert(tk::graphics::initialize(), "Error initializing the graphics");

    loadResources(global.resources);

    LuolaState* state = new Title(global);

    UpdateTimer updateTimer(60);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                global.keyboard.handleEvent(event.key.keysym.sym, event.type == SDL_KEYDOWN);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                global.mouse.handleEvent(event.button.button, event.type == SDL_MOUSEBUTTONDOWN);
                break;
            case SDL_MOUSEMOTION:
                global.mouse.handleMove(event.motion.x, event.motion.y);
                break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        while (updateTimer.update()) {
            LuolaState* newState = state->update(updateTimer.period());
            if (newState) {
                state->shutdown();
                delete state;
                state = newState;
            }
        }

        state->draw();

        SDL_GL_SwapWindow(window);
    }

    if (state) {
        state->shutdown();
        delete state;
    }

    return 0;
}

