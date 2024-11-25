#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL.h>
#include<iostream>

#ifndef DRAW_NUM_H_
#define DRAW_NUM_H_


class numberDrawer{
    private:
        TTF_Font *font;
        
    public:
        numberDrawer(const char*);
        void drawNumber(SDL_Renderer *renderer, int val, SDL_Rect place);   

};

//Complejidad: O(1)
numberDrawer::numberDrawer(const char *fontname){
    TTF_Init();
    font = TTF_OpenFont(fontname, 100);
}

//complejidad: O(1)
void numberDrawer::drawNumber(SDL_Renderer *renderer, int val, SDL_Rect place){
    char const* valchar = std::to_string(val).c_str();

    SDL_Surface *srf = TTF_RenderText_Solid(font, valchar, {255,255,255});
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, srf);

    SDL_RenderCopy(renderer, text, NULL, &place);
    SDL_FreeSurface(srf);
    SDL_DestroyTexture(text);
}

#endif