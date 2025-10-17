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
        void updateSand(int x, int y);
};

World::World(int rows, int cols): 
    m_rows(rows), m_cols(cols), m_points(rows, cols) {
    SDL_Log("Creating the World object");

}

World::~World() {
    SDL_Log("Deleting the World object");
}

void World::addSand(int x, int y, SDL_Color color) {
    if (m_points(x, y).getType() == Empty) //If it is empty
    {
        m_points(x, y).updateColor(color);
        m_points(x, y).updateType(Sand);
        m_points(x, y).updateX(x);
        m_points(x, y).updateY(y);
    }
     
}

//TODO: infinite while loop when clicked at the same spot
void World::addSands(int x, int y, SDL_Color color){
    int squareLength = 50;
    int pixelGenerate = 200;
    int counter = 0;
    int whileCounter = 0; //To prevent infinite while loop when we can't generate enough pixels
    while (counter < pixelGenerate || whileCounter < pixelGenerate*2)
    {
        int rand_x = SDL_rand(squareLength) + x - squareLength/2;
        int rand_y = SDL_rand(squareLength) + y - squareLength/2;

        if (rand_x < m_cols && rand_y < m_rows && rand_x>=0 && rand_y>=0 &&
         m_points(rand_x, rand_y).getType() == Empty ) {
                m_points(rand_x, rand_y).updateColor(color);
                m_points(rand_x, rand_y).updateType(Sand);
                m_points(rand_x, rand_y).updateX(rand_x);
                m_points(rand_x, rand_y).updateY(rand_y);
                counter++;
            }

        whileCounter ++;

    }

}

void World::render(SDL_Renderer* renderer) {
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            if (m_points(j, i).getType() != Empty)
            {
                SDL_Color c = m_points(j, i).getColor();
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
                SDL_RenderPoint(renderer, j, i);
                // m_points(j, i).updated = false;
            }
            
        }
        
    }
    

}


void World::updateSand(int x, int y){

    if (!m_points(x,y).updated && y != m_rows-1) {//If the point hasn't been updated yet in this frame

                int newY = y + 1; //New y

                //This is to prevent going outside of the window
                if (newY > m_rows-1) { //Get on top of the other sands
                    newY = m_rows-1; 
                } 

                //if there is an empty space at newY, Empty this particle and sand the other
                if (m_points(x, newY).getType() == Empty) {

                    // //update the pixels y
                    // m_points(i,j).updateY(newY);
                    addSand(x, newY, m_points(x,y).getColor());
                    // m_points(x,y).updated = true;
                    // m_points(x,newY).updated = true;

                    //swap the two pixels on the grid
                    m_points(x, y).updateType(Empty);


                    
                } 

                //REDUNDANT
                //We can't go down, now lets go to bottom right or bottom left
                //Check if newY is inside the world
                else if (newY <= m_rows-1) { 
                    //if left is still inside the world, and is empty
                    if (x-1>=0 && m_points(x-1 , newY).getType()==Empty){

                        addSand(x-1, newY, m_points(x,y).getColor());
                        // m_points(x-1, newY).updated = true;
                        // m_points(x, y).updated = true;
                        //swap the two pixels on the grid
                        m_points(x, y).updateType(Empty);

                    //if right is still inside the world, and is empty
                    } else if (x+1<=m_cols-1 && m_points(x+1 , newY).getType()==Empty) {

                        addSand(x+1, newY, m_points(x,y).getColor());
                        // m_points(x+1, newY).updated = true;
                        // m_points(x, y).updated = true;
                        //swap the two pixels on the grid
                        m_points(x, y).updateType(Empty);

                    }
                }
                
            }
     
}

void World::update() {
    
    for (int i = 0; i < m_cols; i++) {
        for (int j = m_rows-1; j >= 0; j--) { //Bottom up approach
            if (m_points(i,j).getType() == Sand)
                updateSand(i, j);
        }
    }

}

#endif
