#include <cstdio>
#include <SDL.h>

#include <graphics.hpp>
#include <core.hpp>

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

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    tk::graphics::initializeExtensions();

    tk_info("Loading resources...");
    tk::core::ResourceCollection resources;
    resources.load<tk::graphics::Shader>("shader",
        "data/shaders/shape.vert",
        "data/shaders/shape.frag");

    resources.load<tk::graphics::Font>("font",
        "data/fonts/caviar.ttf");
    tk_info("Finished loading resources.");

    tk::graphics::Bitmap<uint8_t> textImage = resources.get<tk::graphics::Font>("font")->renderText("PONG    | .      |", 40);

    tk::graphics::Texture texture(GL_TEXTURE_2D);
    texture.setData(textImage.getData(), textImage.getWidth(), textImage.getHeight(), GL_R8, GL_RED, GL_UNSIGNED_BYTE);
    texture.useRedAsAlpha();

    tk::graphics::Shape rect = tk::graphics::Shape::rectangle({ 100, 100 }, { (float)textImage.getWidth(), (float)textImage.getHeight() });

    tk::core::Mat4f transform = tk::core::orthographic(0, 0, 1024, 576);

    tk::graphics::Shader* shader = resources.get<tk::graphics::Shader>("shader");
    shader->apply();
    shader->setUniform("image", texture);
    
    tk::graphics::TranslateNode graph("root");
    graph.addChild(new tk::graphics::TranslateNode("left"));
    graph.addChild(new tk::graphics::TranslateNode("right"));

    graph.draw();


    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        shader->setUniform("transform", transform);
        shader->setUniform("tint", tk::core::Vec4f{ 1, 1, 0, 1 });
        rect.draw();

        shader->setUniform("transform", transform * tk::core::transpose(2.0f, -2.f, 0.0f));
        shader->setUniform("tint", tk::core::Vec4f{ 1, 1, 1, 1 });
        rect.draw();

        SDL_GL_SwapWindow(window);
    }

    return 0;
}

