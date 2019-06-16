# Opengl Preset

> A preset for a OpenGL project

This preset aims to serve as an easy to use project preset which I can use
to experiment with OpenGL stuff. It provides
- a way to render text
- a wrapper about shaders
- an application class
- a makefile, license, readme, gitignore and main.cpp file preset

## How to build (Linux)
You will need `make`, `gcc/g++`, `freetype2`, `glew`, `glfw`, `glm` and `opengl` installed.

Build: `make build`
Run: `make run`
Delete build files: `make clean`

Built executable can be found in `out/glapp` or run directly via `make run`.

## How to build (Web / Emscripten)
You will need `make`, `emscripten/emcc` and `glm` installed.
You may have to copy your system headers for `glm` into `<emscripten>/system/include`.

`make embuild` will generate a html page with other files in `out/web/`.
You have to start a web server like nodejs' `http-server` in that directory in order to run it.
