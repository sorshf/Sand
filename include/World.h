#ifndef WORLD_H
#define WORLD_H

#include <SDL3/SDL.h>
#include "Material.h"
#include "Grid.h"

enum VerticalDirection {UP = -1, DOWN = 1, RANDOM_V = 0};
enum HorizontalDirection {LEFT = -1, RIGHT = 1, RANDOM_H = 0};

class World {
    private:

    int m_rows, m_cols;
    Grid<Material> m_points;

    public:
        World(int cols, int rows);
        ~World();
        void addMaterial(int x, int y, SDL_Color color, MaterialType type, int velocity);
        void addMaterials(int x, int y, int diameter, int numPixels, int maxVelocity, SDL_Color baseColor, MaterialType type);
        void render(SDL_Renderer* renderer);
        void update();
        void updateSand(int x, int y);
        int lastVerticalEmptySpace(int x, int startingY, VerticalDirection dir) const;
        int lastHorizontalEmptySpace(int startingX, int y, HorizontalDirection dir) const;
        bool withinRows(int y) const;
        bool withinCols(int x) const;
        void swapPixels(int x1, int y1, int x2, int y2);
        bool moveParticleVertically(int x, int y, int dy, VerticalDirection dir);
        bool moveParticleHorizontally(int x, int y, int dx, HorizontalDirection dir);
        bool moveParticleDiagonally(int x, int y, int dx, int dy, HorizontalDirection horDir, VerticalDirection verDir, bool ignoreCollision = false);
        void burn(int x, int y, int side);
        void diagnose(int x, int y, int side);
        void updateWood(int x, int y);
        void burnSurrounding(int x, int y, int side=1);
        void updateSmoke(int i, int j);
        void updatePoint(int i, int j);
};

#endif
