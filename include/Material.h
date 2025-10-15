#ifndef MATERIAL_H
#define MATERIAL_H

#include <SDL3/SDL.h>
#include <iostream>


class Material {
    protected:
        int m_x;
        int m_y;
        bool update = true;
        SDL_Color m_color;
    public:
        Material(int x, int y, SDL_Color color);
        ~Material();
        Material(const Material& other);
        
        SDL_Color getColor() const;
        int getX() const;
        int getY() const;
        void updateX(int newX);
        void updateY(int newY);
};

//Constructor
Material::Material(int x, int y, SDL_Color color):
    m_x(x), m_y(y), m_color(color) {
}

//Copy constructor
Material::Material(const Material& other):
    m_x(other.m_x), m_y(other.m_y), m_color(other.m_color)
    {

    }

Material::~Material() {
    // std::cout << "Deleting material object" << "\n";
}

SDL_Color Material::getColor() const {
    return m_color;
}

int Material::getX() const {
    return m_x;
}

int Material::getY() const {
    return m_y;
}

void Material::updateX(int newX) {
    m_x = newX;
}

void Material::updateY(int newY) {
    m_y = newY;
}

#endif
