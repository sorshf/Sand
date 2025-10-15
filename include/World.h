#ifndef WORLD_H
#define WORLD_H

#include <SDL3/SDL.h>
#include "Sand.h"
#include "Material.h"
#include <memory>
#include <vector>
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
        void render(SDL_Renderer* renderer) const;
        void update();
};

World::World(int rows, int cols): 
    m_rows(rows), m_cols(cols), m_points(rows, cols) {
    SDL_Log("Creating the World object");

}

World::~World() {
    SDL_Log("Deleting the World object");
}

void World::addSand(int x, int y, SDL_Color color) {
    if (!m_points(x, y)) //If it is null
    {
        m_points(x, y) = std::make_shared<Sand>(x, y, color);
    }
     
}

void World::addSands(int x, int y, SDL_Color color){
    int squareLength = 50;
    int pixelGenerate = 200;
    int counter = 0;
    while (counter < pixelGenerate)
    {
        int rand_x = SDL_rand(squareLength) + x - squareLength/2;
        int rand_y = SDL_rand(squareLength) + y - squareLength/2;

        if (rand_x < m_cols && rand_y < m_rows && rand_x>=0 && rand_y>=0 &&
         !m_points(rand_x, rand_y) ) {
                m_points(rand_x, rand_y) = std::make_shared<Sand>(rand_x, rand_y, color);
                counter++;
            }

    }

}

void World::render(SDL_Renderer* renderer) const {
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            if (m_points(j, i))
            {
                SDL_Color c = m_points(j, i)->getColor();
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
                SDL_RenderPoint(renderer, m_points(j, i)->getX(), m_points(j, i)->getY());
            }
            
        }
        
    }
    

}


void World::update() {
    
    for (int i = 0; i < m_cols; i++) {
        for (int j = m_rows-1; j >= 0; j--) { //Bottom up approach
            if (m_points(i,j)) {//Non-null values(material) which should be updated

                int newY = j + 1; //New y

                //This is to prevent going outside of the window
                if (newY > m_rows-1) { //Get on top of the other sands
                    newY = m_rows-1; 
                } 

                //if there is an empty space at newY, place the particle there
                if (!m_points(i, newY)) {

                    //update the pixels y
                    m_points(i,j)->updateY(newY);

                    //update the location of the pixel on the grid
                    m_points(i, newY) = m_points(i, j);

                    //Remove the old pointer on the grid
                    m_points(i, j) = nullptr;
                } 
                // else if (newY <= m_rows-1) { // Check the bottom left or right and place the particle there
                //     if (!m_points(i-1 , newY)){ //bottom left
                //         //update the pixels y
                //         pointsCopy(i,j)->updateY(newY);

                //         //update the location of the pixel on the grid
                //         pointsCopy(i-1, newY) = pointsCopy(i, j);

                //         //Remove the old pointer on the grid
                //         pointsCopy(i, j) = nullptr;
                //     } else if (!m_points(i+1 , newY)) { //bottom right

                //         //update the pixels y
                //         pointsCopy(i,j)->updateY(newY);

                //         //update the location of the pixel on the grid
                //         pointsCopy(i+1, newY) = pointsCopy(i, j);

                //         //Remove the old pointer on the grid
                //         pointsCopy(i, j) = nullptr;

                //     }
                // }
                
            }
        }
    }

}

#endif
