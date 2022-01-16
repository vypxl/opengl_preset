#include <iostream>

#include "glapp.hpp"

// Example - You can remove this
class Example : public GlApp {

    FtFont* font;

    void update() {

    }

    void draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        font->renderText("Hello World", 10, height - 26, 1.f);

        SDL_GL_SwapBuffers();
    }

    void cleanup() {
        delete font;
    }

public:
    int init() {
#ifdef __EMSCRIPTEN__
        EmscriptenWebGLContextAttributes __attrs;
        emscripten_webgl_init_context_attributes(&__attrs);
        __attrs.majorVersion = 2; __attrs.minorVersion = 0;
        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE __ctx = emscripten_webgl_create_context(0, &__attrs);
        emscripten_webgl_make_context_current(__ctx);
#endif
        // Initialize SDL
        const SDL_VideoInfo* info = nullptr;
        int width = 1920;
        int height = 1080;

        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Video initialization failed: " << SDL_GetError() << std::endl;
            return 1;
        }

        info = SDL_GetVideoInfo( );
        if(!info) {
            std::cerr << "Video query failed: " << SDL_GetError() << std::endl;
            return 1;
        }

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

        if(SDL_SetVideoMode(width, height, 0, SDL_OPENGL | SDL_NOFRAME) == 0) {
            std::cerr << "Video mode set failed: " << SDL_GetError() << std::endl;
            return 1;
        }
#ifndef __EMSCRIPTEN__
        // Initialize glew
        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            return -1;
        }
#endif
        // Initialize OpenGL
        glViewport(0, 0, width, height);
        glClearColor(0.1f, 0.1f, 0.1f, 0.f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Initialize infotext
        font = new FtFont("res/RobotoMono-Regular.ttf", 16, width, height);

        // Initialize Buffers

        return 0;
    }

    void mainloop() {
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_q)
                    running = false;
                break;
            case SDL_QUIT:
                running = false;
                break;
            case SDL_VIDEORESIZE:
                // set instance members
                width = event.resize.w;
                height = event.resize.h;
                
                // set sdl videomode
                if(SDL_SetVideoMode(width, height, 0, SDL_OPENGL | SDL_NOFRAME) == 0) {
                    std::cerr << "Video mode set failed: " << SDL_GetError() << std::endl;
                    exit(1);
                }

                // set gl viewport
                glViewport(0, 0, width, height);

                // set font projection
                font->setWindow(width, height);
                break;
            }
        }

        update();
        draw();
    }
};

int main() {
    Example app;
    if (app.init() != 0) {
        std::cerr << "Failed to initialize" << std::endl;
        return -1;
    };
    app.loop();
    return 0;
}
