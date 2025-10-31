#include "InputHandler.h"

InputHandler::InputHandler(int heightLimit, int widthLimit):
    m_heightLimit(heightLimit), m_widthLimit(widthLimit)
{
}

InputHandler::~InputHandler()
{
}

bool InputHandler::mouseWithinBounds(){
    return (m_x_click >= 0 && m_y_click >= 0 && 
        m_x_click<m_widthLimit && m_y_click<m_heightLimit);

}

SDL_Color getRandomColor(){
    int r = SDL_rand(256);
    int g = SDL_rand(256);
    int b = SDL_rand(256);
    return SDL_Color{static_cast<Uint8>(r), 
                     static_cast<Uint8>(g), 
                     static_cast<Uint8>(b), 
                     255};
}

void InputHandler::handleInput(){

    while (SDL_PollEvent(&m_e)) {            
        switch (m_e.type) {
            case SDL_EVENT_QUIT:
                m_quit = true;
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                m_addMaterial = false;
                m_mousePressed = false;
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                m_mousePressed = true;
                m_sandBaseColor = getRandomColor();
                SDL_GetMouseState(&m_x_click, &m_y_click);
                if (mouseWithinBounds()) {
                    m_addMaterial = true;
                }
                break;
            case SDL_EVENT_MOUSE_MOTION:
                if (m_mousePressed){
                    SDL_GetMouseState(&m_x_click, &m_y_click);
                    if (mouseWithinBounds()) {
                        m_addMaterial = true;
                    }
                }
                    break;
            case SDL_EVENT_KEY_DOWN:
                if (m_e.key.key == SDLK_W) {
                    m_addWoods = true;
                    m_addSands = false;
                    m_burn = false;
                    m_saveImage = false;
                } else if (m_e.key.key == SDLK_S) {
                    m_addWoods = false;
                    m_addSands = true;
                    m_burn = false;
                    m_saveImage = false;
                } else if (m_e.key.key == SDLK_F) {
                    m_addWoods = false;
                    m_addSands = false;
                    m_burn = true;
                    m_saveImage = false;
                } else if (m_e.key.key == SDLK_D) {
                    m_addWoods = false;
                    m_addSands = false;
                    m_burn = false;
                    m_saveImage = true;
                }
                break;
            default:
                break;
        }
    }

}
