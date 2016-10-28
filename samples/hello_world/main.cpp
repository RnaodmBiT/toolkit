#include <cstdio>
#include <SDL.h>

#include <graphics.hpp>
#include <core.hpp>

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

    tk::graphics::Shader shader("data/shaders/position.vert", "data/shaders/green.frag");

    tk::graphics::Array array(GL_TRIANGLES);

    tk::graphics::Buffer vertexBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    tk::core::Vector<float, 3> points[] = {
        { 0, 0, 0 },
        { 100, 0, 0 },
        { 0, 100, 0 }
    };

    tk::core::Mat4f transform = tk::core::orthographic(0, 0, 1024, 576) *
                                tk::core::transpose(100.0f, 0.0f, 0.0f) *
                                tk::core::rotate((float)M_PI / 4, { 0, 0, 1 });

    vertexBuffer.setData(points, 3);

    array.addBuffer(vertexBuffer, GL_FLOAT, 3);
    shader.apply();
    shader.setUniform("transform", transform);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        array.draw(0, 3);

        SDL_GL_SwapWindow(window);
    }

    return 0;
}

