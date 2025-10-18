#include <SDL3/SDL.h>
#include <iostream>
#include "Config.h"
#include "World.h"
#include "Grid.h"
#include "memory"

using namespace std;

int main() {

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

    //Create window
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer("Falling Sand Simulation", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, 
        &window, &renderer);
    if (window == NULL) {
        cerr << "Couldn't create SDL window: " << SDL_GetError() << endl;
        SDL_Quit();
    }
    if (renderer == NULL) {
        cerr << "Couldn't initiate the renderer: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    //Controling the main loop of the app
    bool quit, mousePressed = false;
    SDL_Event e;

    World w {WINDOW_HEIGHT, WINDOW_WIDTH};
    
    SDL_Color sandColor = {255, 255, 255, 255};

    float x_click, y_click;

    

    //Main loop of the app
    while (!quit) {

       while (SDL_PollEvent(&e)) {            
            switch (e.type) {
                case SDL_EVENT_QUIT:
                    quit = true;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    mousePressed = false;
                    break;
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    mousePressed = true;
                case SDL_EVENT_MOUSE_MOTION:
                    if (mousePressed){
                        SDL_GetMouseState(&x_click, &y_click);
                        if (x_click >= 0 && y_click >= 0 && x_click<WINDOW_WIDTH && y_click<WINDOW_HEIGHT)
                            w.addSands(SDL_floorf(x_click), SDL_floorf(y_click), sandColor);
                    }
                        break;
                //     SDL_GetMouseState(&x_click, &y_click);
                //     // SDL_Log("%f %f", x_click, y_click);
                //     w.addSand(SDL_floorf(x_click), SDL_floorf(y_click), sandColor);
                //     break;
                default:
                    break;
            }
        }


        //Background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Graph
        w.render(renderer);

        
        //Present everything
        SDL_RenderPresent(renderer);

        w.update();
        

        SDL_Delay(40);

    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    
}