#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <iostream>
#include "Config.h"
#include "World.h"

using namespace std;

class Game {
private:
    const char* m_title;
    int m_width;
    int m_height;
    World m_world;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Color m_baseColor {194, 178, 128, 1}; //to be removed with better logic
    bool m_quit = false;
    bool m_mousePressed = false;
    SDL_Event m_e;
    float m_x_click = 0.0f;
    float m_y_click = 0.0f;
public:
    Game(const char* title, int width, int height);
    ~Game();
    void processInput();
    // void update();
    void render();
    void run();
};

SDL_Color getRandomColor(){
    int r = SDL_rand(256);
    int g = SDL_rand(256);
    int b = SDL_rand(256);
    return SDL_Color{static_cast<Uint8>(r), 
                     static_cast<Uint8>(g), 
                     static_cast<Uint8>(b), 
                     255};
}

Game::Game(const char* title, int width, int height):
    m_title{title}, m_width(width), m_height(height), m_world{height, width} {

    SDL_CreateWindowAndRenderer(m_title, m_width, m_height, 0, 
        &m_window, &m_renderer);
    if (m_window == NULL) {
        cerr << "Couldn't create SDL window: " << SDL_GetError() << endl;
        SDL_Quit();
    }
    if (m_renderer == NULL) {
        cerr << "Couldn't initiate the renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
}

Game::~Game() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void Game::processInput() {

    while (SDL_PollEvent(&m_e)) {            
        switch (m_e.type) {
            case SDL_EVENT_QUIT:
                m_quit = true;
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                m_mousePressed = false;
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                m_mousePressed = true;
                m_baseColor = getRandomColor();
            case SDL_EVENT_MOUSE_MOTION:
                if (m_mousePressed){
                    SDL_GetMouseState(&m_x_click, &m_y_click);
                    if (m_x_click >= 0 && m_y_click >= 0 && m_x_click<m_width && m_y_click<m_height)
                        m_world.addSands(SDL_floorf(m_x_click), SDL_floorf(m_y_click), m_baseColor);
                }
                    break;

            default:
                break;
        }
    }

}

void Game::render() {
    //Background
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    //Graph
    m_world.render(m_renderer);

    
    //Present everything
    SDL_RenderPresent(m_renderer);

    m_world.update();
    

    SDL_Delay(40);
}

void Game::run() {
    while (!m_quit) {
        processInput();
        // update();
        render();
    }
}


#endif