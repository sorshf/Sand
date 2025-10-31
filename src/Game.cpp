#include "Game.h"

Game::Game(const char* title, int width, int height):
    m_title{title}, m_width(width), m_height(height), m_world{height, width}, m_inputHandler{height, width}  {

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

    m_inputHandler.handleInput();

    if (m_inputHandler.m_quit){
        m_quit = true;
    }

}

void Game::update() {
    if (m_inputHandler.m_addMaterial && m_inputHandler.m_addSands) {
        m_world.addMaterials(SDL_floorf(m_inputHandler.m_x_click), SDL_floorf(m_inputHandler.m_y_click),
                 50, 200, 20, m_inputHandler.m_sandBaseColor, Sand);
    } else if (m_inputHandler.m_addMaterial && m_inputHandler.m_addWoods) {
        m_world.addMaterials(SDL_floorf(m_inputHandler.m_x_click), SDL_floorf(m_inputHandler.m_y_click),
                        16, 250, 0, {150, 111, 51, 255}, Wood);
    } else if (m_inputHandler.m_addMaterial && m_inputHandler.m_burn) {
        m_world.burn(SDL_floorf(m_inputHandler.m_x_click), SDL_floorf(m_inputHandler.m_y_click), 20);
    }
}

void Game::render() {
    //Background
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    //Graph
    m_world.render(m_renderer);

    if(m_inputHandler.m_addMaterial && m_inputHandler.m_saveImage) {
        saveImage();
    }
    
    //Present everything
    SDL_RenderPresent(m_renderer);

    m_world.update();
    

    SDL_Delay(40);
}

void Game::run() {
    while (!m_quit) {
        processInput();
        update();
        render();
    }
}

void Game::saveImage() {
    SDL_Surface *surface = SDL_RenderReadPixels(m_renderer, NULL);
    SDL_SaveBMP(surface, "./Snapshot.bmp");
    SDL_DestroySurface(surface);
}