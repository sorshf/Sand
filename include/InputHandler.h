#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL3/SDL.h>
#include <iostream>


class InputHandler
{
private:
    const int m_heightLimit;
    const int m_widthLimit;
    SDL_Event m_e;
public:
    bool m_quit = false;
    bool m_mousePressed = false;
    bool m_addMaterial = false;
    bool m_addSands = true;
    bool m_addWoods = false;
    bool m_burn = false;
    bool m_diagnose = false;
    float m_x_click = 0.0f;
    float m_y_click = 0.0f;
    InputHandler(int heightLimit, int widthLimit);
    ~InputHandler();
    void handleInput();
    bool mouseWithinBounds();
};

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
                    m_diagnose = false;
                } else if (m_e.key.key == SDLK_S) {
                    m_addWoods = false;
                    m_addSands = true;
                    m_burn = false;
                    m_diagnose = false;
                } else if (m_e.key.key == SDLK_F) {
                    m_addWoods = false;
                    m_addSands = false;
                    m_burn = true;
                    m_diagnose = false;
                } else if (m_e.key.key == SDLK_D) {
                    m_addWoods = false;
                    m_addSands = false;
                    m_burn = false;
                    m_diagnose = true;
                }
                break;
            default:
                break;
        }
    }

}


#endif