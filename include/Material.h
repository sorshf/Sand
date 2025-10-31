#ifndef MATERIAL_H
#define MATERIAL_H

#include <SDL3/SDL.h>
#include <iostream>

enum MaterialType {Empty=0, Sand, Wood, Smoke};

class Material {
    private:
        SDL_Color m_color;
        MaterialType m_type = Empty;
    public:
        bool updated = false; //The material was updated in the current frame
        int m_velocity = 1;
        int m_burnDegree = 0;
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
        bool isWood() const;
        void burn();
        void smoke();
        void reset();
};

#endif
