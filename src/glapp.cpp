#include <iostream>

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
#endif

#include "glapp.hpp"

void _loopf(void *self) {
    ((GlApp*)self)->mainloop();
}

void GlApp::loop() {
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(_loopf, this, 100, 1);
#else
    running = true;
    while (running) {
        mainloop();
    }
#endif
    cleanup();
}
