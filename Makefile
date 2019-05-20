NAME=glapp
LIBS=-lGL -lGLEW -lSDL -lfreetype

CXX_OPTS=-I include -o out/$(NAME)
EMS_OPTS=-std=c++11 USE_FREETYPE=1 -s FULL_ES3=1 -s USE_WEBGL2=1 -I include -o out/web/$(NAME).html --preload_file ./res@/res --preload_file ./shaders@/shaders

FILES=$(wildcard src/*.cpp) $(wildcard src/sorts/*.cpp)

.PHONY: mkdirs build run clean embuild embuild_asmjs

mkdirs:
	@mkdir -p out/web

build: mkdirs
	@g++ -I include -o out/$(NAME) $(FILES) $(LIBS)

embuild: mkdirs
	@em++ $(EMS_OPTS) $(FILES)

embuild_asmjs: mkdirs
	@em++ $(EMS_OPTS) -s WASM=0 $(FILES)

run: build
	@out/$(NAME)

clean:
	@rm -r out/

.DEFAULT_GOAL := build
