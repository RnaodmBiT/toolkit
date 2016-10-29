#include <cstdio>
#include <SDL.h>

#include <graphics.hpp>
#include <core.hpp>

int main(int argc, char** argv) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        printf("Error: SDL_Init\n");
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_Window* window = SDL_CreateWindow("Hello World",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1024, 576,
                                          SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);

    tk::graphics::initializeExtensions();

    tk::graphics::Shader shader("data/shaders/positionUv.vert", "data/shaders/texture.frag");

    tk::graphics::Array array(GL_TRIANGLES);

    tk::graphics::Buffer vertexBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    tk::graphics::Buffer uvBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);

    tk::core::Vec3f points[] = {
        { 0, 0, 0 },
        { 100, 0, 0 },
        { 0, 100, 0 }
    };

    tk::core::Vec2f uvs[] = {
        { 0, 0 },
        { 1, 0 },
        { 0, 1 }
    };

    vertexBuffer.setData(points, 3);
    uvBuffer.setData(uvs, 3);

    array.addBuffer(vertexBuffer, GL_FLOAT, 3);
    array.addBuffer(uvBuffer, GL_FLOAT, 2);

    tk::core::Vector<unsigned char, 3> image[] = {
        { 255, 0, 0 },{ 0, 0, 255 },
        { 0, 255, 0 },{ 255, 0, 0 },
    };

    tk::graphics::Texture texture(GL_TEXTURE_2D);
    texture.setData(image, 2, 2, GL_RGB, GL_UNSIGNED_BYTE);

    tk::core::Mat4f transform = tk::core::orthographic(0, 0, 1024, 576) *
        tk::core::transpose(100.0f, 0.0f, 0.0f) *
        tk::core::rotate((float)M_PI / 4, { 0, 0, 1 });

    shader.apply();
    shader.setUniform("transform", transform);
    shader.setUniform("image", texture);

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

