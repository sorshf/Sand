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
        void updateSand(int x, int y, int dy);
        int lastVerticalEmptySpace(int x, int startingY, VerticalDirection dir) const;
        int lastHorizontalEmptySpace(int startingX, int y, HorizontalDirection dir) const;
        bool withinRows(int y) const;
        bool withinCols(int x) const;
        void swapPixels(int x1, int y1, int x2, int y2);
        bool moveParticleVertically(int x, int y, int dy, VerticalDirection dir);
        bool moveParticleHorizontally(int x, int y, int dx, HorizontalDirection dir);
        bool moveParticleDiagonally(int x, int y, HorizontalDirection horDir, VerticalDirection verDir, bool ignoreCollision = false);
        void burn(int x, int y, int side);
        void diagnose(int x, int y, int side);
        void updateWood(int x, int y);
        void burnSurrounding(int x, int y, int side=1);
};

World::World(int rows, int cols): 
    m_rows(rows), m_cols(cols), m_points(rows, cols) {
    SDL_Log("Creating the World object");

}

World::~World() {
    SDL_Log("Deleting the World object");
}

SDL_Color genRandomFromBase(SDL_Color baseColor) {
    int offset = 10;
    int randOffset = SDL_rand(offset*2) - offset; 
    return SDL_Color {static_cast<Uint8>(baseColor.r + randOffset),
                      static_cast<Uint8>(baseColor.g + randOffset),
                      static_cast<Uint8>(baseColor.b + randOffset),
                      baseColor.a  };
}

void World::addMaterial(int x, int y, SDL_Color color, MaterialType type, int velocity) {
    if (m_points(x, y).isEmpty()) {

        m_points(x, y).updateColor(color);
        m_points(x, y).updateType(type);
        m_points(x, y).m_velocity = velocity;
    }
}

void World::addMaterials(int x, int y, int diameter, int numPixels, int maxVelocity, SDL_Color baseColor, MaterialType type){
    int circleDiameter = diameter;
    int numPixelsGenerate = numPixels;
    for (int i=0; i < numPixelsGenerate; i++)
    {
        int rand_x = SDL_rand(circleDiameter) - circleDiameter/2;
        int y_bound = SDL_floorf(SDL_sqrt((circleDiameter/2)*(circleDiameter/2)-(rand_x)*(rand_x)));
        int rand_y = SDL_rand(y_bound*2) - y_bound;

        rand_x += x;
        rand_y += y;

        if (rand_x < m_cols && rand_y < m_rows && rand_x>=0 && rand_y>=0 &&
         m_points(rand_x, rand_y).isEmpty() ) {
                addMaterial(rand_x, rand_y, genRandomFromBase(baseColor), type, SDL_rand(maxVelocity));
            }
    }

}

void World::burn(int x, int y, int side){
    int topLeftX = (x - side/2);
    int topLeftY = (y - side/2);

    for (int i = topLeftX; i < x+side/2; i++) {
        for (int j = topLeftY; j < y+side/2; j++) {
            if (withinRows(j) && withinCols(i) && m_points(i, j).getType()==Wood) {
                m_points(i, j).burn();
            }
            
        }
        
    }
    
    
}

void World::burnSurrounding(int x, int y, int side) {
    //Square around point (x,y) with length side*2+1 will burn
    for (int i = x-side; i <= x+side; i++) {
        for (int j = y-side; j <= y+side; j++) {
            
            if (withinCols(i) && withinRows(j) && 
                    m_points(i, j).isWood() && m_points(i, j).m_burnDegree == 0 &&
                    i != x && j != y) {

                m_points(i, j).burn();
            }
            
        }    
    } 
}

void World::diagnose(int x, int y, int side){
    int topLeftX = (x - side/2);
    int topLeftY = (y - side/2);

    for (int i = topLeftX; i < x+side/2; i++) {
        for (int j = topLeftY; j < y+side/2; j++) {
            if (withinRows(j) && withinCols(i) && m_points(i, j).getType()==Wood) {
                SDL_Log("%d", m_points(i, j).m_burnDegree);
            }
            
        }
        
    }
    
    
}

void World::render(SDL_Renderer* renderer) {
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            if (!m_points(j, i).isEmpty())
            {
                SDL_Color c = m_points(j, i).getColor();
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
                SDL_RenderPoint(renderer, j, i);
                // m_points(j, i).updated = false;
            }
            
        }
        
    }
    

}

    
bool World::withinRows(int y) const{
    return y>=0 && y<=m_rows-1;
}

bool World::withinCols(int x) const{
    return x>=0 && x<=m_cols-1;
}

int World::lastVerticalEmptySpace(int x, int startingY, VerticalDirection dir) const {
    //If the column is totally filled, it returns the startingY
    //Otherwise returns the first empty space going down vertically
    while (true)
    {
        startingY += dir;
        if (withinRows(startingY))
        {
            if (!m_points(x, startingY).isEmpty())
            {
                return startingY += dir*(-1);
            } 
            
        } else {
            return startingY += dir*(-1);
        }
    }    
}


int World::lastHorizontalEmptySpace(int startingX, int y, HorizontalDirection dir) const {
    //If the column is totally filled, it returns the startingY
    //Otherwise returns the first empty space going down vertically
    while (true)
    {
        startingX += dir;
        if (withinCols(startingX))
        {
            if (!m_points(startingX, y).isEmpty())
            {
                return startingX += dir*(-1);
            } 
            
        } else {
            return startingX += dir*(-1);
        }
    }    
}

void World::swapPixels(int x1, int y1, int x2, int y2) {
    //copy pixel 1 data
    SDL_Color m_color1 = m_points(x1,y1).getColor();
    MaterialType m_type1 = m_points(x1,y1).getType();
    bool updated1 = m_points(x1,y1).updated; 
    int m_velocity1 = m_points(x1,y1).m_velocity;
    int m_burnDegree1 = m_points(x1,y1).m_burnDegree;

    //update pixel 1 with pixel 2 data
    m_points(x1,y1).updateColor(m_points(x2,y2).getColor());
    m_points(x1,y1).updateType(m_points(x2,y2).getType());
    m_points(x1,y1).updated = m_points(x2,y2).updated;
    m_points(x1,y1).m_velocity = m_points(x2,y2).m_velocity;
    m_points(x1,y1).m_burnDegree = m_points(x2,y2).m_burnDegree;

    //update pixel2 with pixel 1 data
    m_points(x2,y2).updateColor(m_color1);
    m_points(x2,y2).updateType(m_type1);
    m_points(x2,y2).updated = updated1;
    m_points(x2,y2).m_velocity = m_velocity1;
    m_points(x2,y2).m_burnDegree = m_burnDegree1;
}


bool World::moveParticleVertically(int x, int y, int dy, VerticalDirection dir) {

    //Find the last empty space on the column for the empty space
    int lves = lastVerticalEmptySpace(x, y, dir);
    int newY;

    //If there is a collision ([y+dy*dir] > lves), the newY for the particle is the last vertical empty space
    if (y+dy*dir > lves) {
        newY = lves;
    } else { //Otherwise the newY is calculated normally
        newY = y+dy*dir;
    }

    //if there is an empty space at newY, Swap the particles, otherwise do nothing (keep the particle pos as is)
    if (lves != y) {

        swapPixels(x, y, x, newY);
        //update the velocity
        m_points(x, newY).m_velocity += m_points(x, newY).ACCELERATION;

        return true;

    }
    return false;
}

bool World::moveParticleHorizontally(int x, int y, int dx, HorizontalDirection dir) {

    //Find the last empty space on the row for the empty space
    int lhes = lastHorizontalEmptySpace(x, y, dir);
    int newX;

    //If there is a collision ([x+dx*dir] > lhes), the newx for the particle is the last horizontal empty space
    if (x+dx*dir > lhes) {
        newX = lhes;
    } else { //Otherwise the newY is calculated normally
        newX = x+dx*dir;
    }

    //if there is an empty space at newX, Swap the particles, otherwise do nothing (keep the particle pos as is)
    if (lhes != x) {

        swapPixels(x, y, newX, y);
        return true;
    }
    
    return false;
}

bool World::moveParticleDiagonally(int x, int y, HorizontalDirection horDir, VerticalDirection verDir, bool ignoreCollision) {

    if (horDir == RANDOM_H) {
        horDir = SDL_rand(2)==1 ? LEFT : RIGHT;
    }
    
    if (verDir == RANDOM_V) {
        verDir = SDL_rand(2)==1 ? DOWN : UP;
    }

    //Make sure the particle is within the window
    int newX = withinCols(x + horDir) ? x + horDir : x;
    int newY = withinRows(y + verDir) ? y + verDir : y;

    //If the new position is empty and different from the original, we swap the points
    if (ignoreCollision) {
        swapPixels(x, y, newX, newY);
        return true;
    } else if (m_points(newX , newY).isEmpty()) {
        swapPixels(x, y, newX, newY);
        return true;
    }

    return false;
}

void World::updateSand(int x, int y, int dy){

    //If the point hasn't been updated yet in this frame and not on the last row
    if (!m_points(x,y).updated && y != m_rows-1) {

        //half the time, we also move the particle diagonally in addition to vertically
        if (SDL_rand(2) == 1){
            moveParticleDiagonally(x, y, RANDOM_H, DOWN);
        }
        
        //If we couldn't move the particle down, we move it diagonally
        if (!moveParticleVertically(x, y, dy, DOWN)){
            moveParticleDiagonally(x, y, RANDOM_H, DOWN);
        }       
    }
     
}

void World::updateWood(int x, int y) {

    int burnDegree = m_points(x,y).m_burnDegree;
    if (burnDegree > 0 && burnDegree < 50) {


        //Change the color of the particle mimicking burning
        SDL_Color red = {255, 0, 0, 255};
        SDL_Color yellow = {255, 255, 0, 255};
        SDL_Color newColor = SDL_rand(2) == 1 ? red : yellow;
        m_points(x,y).updateColor(newColor);
        m_points(x,y).m_burnDegree = burnDegree + 1;

        //Burn the surrounding Wood
        burnSurrounding(x, y, 1);

        //Move particle randomly diagonally
        moveParticleDiagonally(x, y, RANDOM_H, RANDOM_V, false);
    } else if (burnDegree >= 50) {
        m_points(x,y).updateColor({0, 255, 0, 255});
        m_points(x,y).reset();
    }
    

}

void World::update() {
    
    for (int i = 0; i < m_cols; i++) {
        for (int j = m_rows-1; j >= 0; j--) { //Bottom up approach
            if (m_points(i,j).getType() == Sand){
                int dy = m_points(i,j).m_velocity;
                updateSand(i, j, dy);
            } else if (m_points(i,j).getType() == Wood) {
                updateWood(i, j);
            }
        }
    }

}

#endif
