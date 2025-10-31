#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <iostream>
#include "Config.h"
#include "World.h"
#include "InputHandler.h"

using namespace std;

class Game {
private:
    const char* m_title;
    int m_width;
    int m_height;
    World m_world;
    InputHandler m_inputHandler;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool m_quit = false;
public:
    Game(const char* title, int width, int height);
    ~Game();
    void processInput();
    void update();
    void render();
    void run();
    void saveImage();
};


#endif