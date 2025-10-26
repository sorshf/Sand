#ifndef MATERIAL_H
#define MATERIAL_H

#include <SDL3/SDL.h>
#include <iostream>

enum MaterialType {Empty=0, Sand, Wood, Fire};

class Material {
    private:
        SDL_Color m_color;
        MaterialType m_type = Empty;
    public:
        bool updated = false; //The material was updated in the current frame
        int m_velocity = 1;
    public:
        static const int ACCELERATION = 3;
        Material();
        Material(SDL_Color color, MaterialType type);
        ~Material();
        Material(const Material& other) = delete;
        
        SDL_Color getColor() const;
        void updateColor(SDL_Color color);
        void updateType(MaterialType type);
        MaterialType getType() const;
        bool isEmpty() const;
};

Material::Material(){}

//Constructor
Material::Material(SDL_Color color, MaterialType type):
    m_color(color), m_type(type) {
}

Material::~Material() {
    // std::cout << "Deleting material object" << "\n";
}

SDL_Color Material::getColor() const {
    return m_color;
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

bool Material::isEmpty() const {
    return m_type == Empty;
}

#endif
