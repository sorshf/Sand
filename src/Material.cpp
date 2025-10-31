#include "Material.h"

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

bool Material::isWood() const {
    return m_type == Wood;
}

void Material::burn() {
    m_burnDegree = 1;
}

void Material::smoke() {
    m_type = Smoke;
    m_color = {128, 128, 128, 255};
}

void Material::reset() {
    m_color = {0, 0, 0, 255};
    m_type = Empty;
    updated = false;
    m_velocity = 1;
    m_burnDegree = 0;
}
