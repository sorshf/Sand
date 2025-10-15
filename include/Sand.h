#ifndef SAND_H
#define SAND_H

#include <SDL3/SDL.h>
#include "Material.h"


class Sand: public Material {
    public:
        Sand(int x, int y, SDL_Color color): Material(x, y, color){};
        void fall();
};



#endif
