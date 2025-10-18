#ifndef MATERIAL_H
#define MATERIAL_H

#include <SDL3/SDL.h>
#include <iostream>

enum MaterialType {Empty=0, Sand, Snow, Fire};

class Material {
    private:
        int m_x;
        int m_y;
        SDL_Color m_color;
        MaterialType m_type = Empty;
    public:
        bool updated = false; //The material was updated in the current frame
        int m_velocity = 1;
    public:
        static const int ACCELERATION = 3;
        Material();
        Material(int x, int y, SDL_Color color, MaterialType type);
        ~Material();
        Material(const Material& other);
        
        SDL_Color getColor() const;
        int getX() const;
        int getY() const;
        void updateX(int newX);
        void updateY(int newY);
        void updateColor(SDL_Color color);
        void updateType(MaterialType type);
        MaterialType getType() const;
};

Material::Material(){}

//Constructor
Material::Material(int x, int y, SDL_Color color, MaterialType type):
    m_x(x), m_y(y), m_color(color), m_type(type) {
}

//Copy constructor
Material::Material(const Material& other):
    m_x(other.m_x), m_y(other.m_y), m_color(other.m_color), m_type(other.m_type)
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

void Material::updateColor(SDL_Color color){
    m_color = color;
}

void Material::updateType(MaterialType type){
    m_type = type;
}

MaterialType Material::getType() const {
    return m_type;
}



#endif
