#ifndef WORLD_H
#define WORLD_H

#include <SDL3/SDL.h>
#include "Material.h"
#include "Grid.h"


class World {
    private:

    int m_rows, m_cols;
    Grid<Material> m_points;

    public:
        World(int cols, int rows);
        ~World();
        void addSand(int x, int y, SDL_Color color);
        void addSands(int x, int y, SDL_Color color);
        void render(SDL_Renderer* renderer);
        void update();
        void updateSand(int x, int y, int dy);
        int lastVerticalEmptySpace(int x, int startingY) const;
        bool withinRows(int y) const;
        bool withinCols(int x) const;
        void swapPixels(int x1, int y1, int x2, int y2);
};

World::World(int rows, int cols): 
    m_rows(rows), m_cols(cols), m_points(rows, cols) {
    SDL_Log("Creating the World object");

}

World::~World() {
    SDL_Log("Deleting the World object");
}

void World::addSand(int x, int y, SDL_Color color) {
    if (m_points(x, y).isEmpty()) //If it is empty
    {
        m_points(x, y).updateColor(color);
        m_points(x, y).updateType(Sand);
        m_points(x, y).m_velocity = SDL_rand(20) + 1;
    }
     
}

SDL_Color genRandomFromBase(SDL_Color baseColor) {
    int offset = 10;
    int randOffset = SDL_rand(offset*2) - offset; 
    return SDL_Color {static_cast<Uint8>(baseColor.r + randOffset),
                      static_cast<Uint8>(baseColor.g + randOffset),
                      static_cast<Uint8>(baseColor.b + randOffset),
                      baseColor.a  };
}

void World::addSands(int x, int y, SDL_Color baseColor){
    int circleDiameter = 50;
    int numPixelsGenerate = 200;
    for (int i=0; i < numPixelsGenerate; i++)
    {
        int rand_x = SDL_rand(circleDiameter) - circleDiameter/2;
        int y_bound = SDL_floorf(SDL_sqrt((circleDiameter/2)*(circleDiameter/2)-(rand_x)*(rand_x)));
        int rand_y = SDL_rand(y_bound*2) - y_bound;

        rand_x += x;
        rand_y += y;

        if (rand_x < m_cols && rand_y < m_rows && rand_x>=0 && rand_y>=0 &&
         m_points(rand_x, rand_y).isEmpty() ) {
                addSand(rand_x, rand_y, genRandomFromBase(baseColor));
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

int World::lastVerticalEmptySpace(int x, int startingY) const {
    //If the column is totally filled, it returns the startingY
    //Otherwise returns the first empty space going down vertically
    while (true)
    {
        startingY++;
        if (withinRows(startingY))
        {
            if (!m_points(x, startingY).isEmpty())
            {
                return startingY-1;
            } 
            
        } else {
            return startingY-1;
        }
    }    
}

void World::swapPixels(int x1, int y1, int x2, int y2) {
    //copy pixel 1 data
    SDL_Color m_color1 = m_points(x1,y1).getColor();
    MaterialType m_type1 = m_points(x1,y1).getType();
    bool updated1 = m_points(x1,y1).updated; 
    int m_velocity1 = m_points(x1,y1).m_velocity;

    //update pixel 1 with pixel 2 data
    m_points(x1,y1).updateColor(m_points(x2,y2).getColor());
    m_points(x1,y1).updateType(m_points(x2,y2).getType());
    m_points(x1,y1).updated = m_points(x2,y2).updated;
    m_points(x1,y1).m_velocity = m_points(x2,y2).m_velocity;

    //update pixel2 with pixel 1 data
    m_points(x2,y2).updateColor(m_color1);
    m_points(x2,y2).updateType(m_type1);
    m_points(x2,y2).updated = updated1;
    m_points(x2,y2).m_velocity = m_velocity1;
}

void World::updateSand(int x, int y, int dy){

    //If the point hasn't been updated yet in this frame and not on the last row
    if (!m_points(x,y).updated && y != m_rows-1) {

        //Find the last empty space on the column for the empty space
        int lves = lastVerticalEmptySpace(x, y);
        int newY;

        //If there is a collision ([y+dy] > lves), the newY for the sand is the last vertical empty space
        if (y+dy > lves) {
            newY = lves;
        } else { //Otherwise the newY is calculated normally
            newY = y+dy;
        }
                
        //if there is an empty space at newY, Swap the particles
        if (lves != y) {

            swapPixels(x, y, x, newY);
            //update the velocity
            m_points(x, newY).m_velocity += m_points(x, newY).ACCELERATION;

        //We can't go down, now lets go to bottom right or bottom left
        //++newY goes down
        } else if (withinRows(++newY)) { 
            //if left is still inside the world, and is empty
            if (withinCols(x-1) && m_points(x-1 , newY).isEmpty()){

                swapPixels(x, y, x-1, newY);
                m_points(x-1, newY).m_velocity = 1;

            //if right is still inside the world, and is empty
            } else if (withinCols(x+1) && m_points(x+1 , newY).isEmpty()) {
                
                swapPixels(x, y, x+1, newY);
                m_points(x+1, newY).m_velocity = 1;

            }
        }
                
    }
     
}

void World::update() {
    
    for (int i = 0; i < m_cols; i++) {
        for (int j = m_rows-1; j >= 0; j--) { //Bottom up approach
            if (m_points(i,j).getType() == Sand){
                int dy = m_points(i,j).m_velocity;
                updateSand(i, j, dy);
            }
        }
    }

}

#endif
