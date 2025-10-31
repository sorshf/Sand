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
    bool m_saveImage = false;
    SDL_Color m_sandBaseColor;
    float m_x_click = 0.0f;
    float m_y_click = 0.0f;
    InputHandler(int heightLimit, int widthLimit);
    ~InputHandler();
    void handleInput();
    bool mouseWithinBounds();
};


#endif