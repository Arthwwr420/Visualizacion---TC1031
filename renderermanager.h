#include<SDL2/SDL.h>

#ifndef RENDERERMANAGER_H
#define RENDERERMANAGER_H

//Actualizar el renderer para mostrar la imagen adecuada
void UpdateArrayRender(int* arr, int arrsize, int height, int width, int max, SDL_Renderer *renderer){
    SDL_Rect rRect{0, 0, 0, 0};
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < arrsize; i++){

            rRect.h = height*arr[i]/max;
            rRect.w = width/arrsize;
            rRect.x = i*width/arrsize;
            rRect.y = height - rRect.h;
             
            SDL_RenderFillRect(renderer, &rRect);

        }
}


#endif