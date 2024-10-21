#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<math.h>

#ifndef RENDERERMANAGER_H
#define RENDERERMANAGER_H


class numberDrawer{
    private:
        TTF_Font *font;
        
    public:
        numberDrawer(const char*);
        void drawNumber(SDL_Renderer *renderer, int val, SDL_Rect place);   

};

numberDrawer::numberDrawer(const char *fontname){
    TTF_Init();
    font = TTF_OpenFont(fontname, 100);
}

void numberDrawer::drawNumber(SDL_Renderer *renderer, int val, SDL_Rect place){
    char const* valchar = std::to_string(val).c_str();

    SDL_Surface *srf = TTF_RenderText_Solid(font, valchar, {255,255,255});
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, srf);

    SDL_RenderCopy(renderer, text, NULL, &place);
    SDL_FreeSurface(srf);
    SDL_DestroyTexture(text);
}


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

void DrawBST(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderDrawLine(renderer, 0, 75, 1200, 75);
    SDL_RenderDrawLine(renderer, 0, 175, 1200, 175);
    SDL_RenderDrawLine(renderer, 0, 275, 1200, 275);
    SDL_RenderDrawLine(renderer, 0, 375, 1200, 375);
    SDL_RenderDrawLine(renderer, 0, 475, 1200, 475);
    SDL_RenderDrawLine(renderer, 0, 575, 1200, 575);

    SDL_RenderDrawLine(renderer, 601, 175, 601, 675); //3

    SDL_RenderDrawLine(renderer, 301, 275, 301, 675); //7
    SDL_RenderDrawLine(renderer, 901, 275, 901, 675);

    SDL_RenderDrawLine(renderer, 151, 375, 151, 675); //15
    SDL_RenderDrawLine(renderer, 451, 375, 451, 675);
    SDL_RenderDrawLine(renderer, 751, 375, 751, 675);
    SDL_RenderDrawLine(renderer, 1051, 375, 1051, 675);

    SDL_RenderDrawLine(renderer, 75, 475, 75, 675); //31
    SDL_RenderDrawLine(renderer, 225, 475, 225, 675);
    SDL_RenderDrawLine(renderer, 375, 475, 375, 675);
    SDL_RenderDrawLine(renderer, 525, 475, 525, 675);
    SDL_RenderDrawLine(renderer, 675, 475, 675, 675);
    SDL_RenderDrawLine(renderer, 825, 475, 825, 675);
    SDL_RenderDrawLine(renderer, 975, 475, 975, 675);
    SDL_RenderDrawLine(renderer, 1125, 475, 1125, 675);

    SDL_RenderDrawLine(renderer, 38, 575, 38, 675); //63
    SDL_RenderDrawLine(renderer, 113, 575, 113, 675);
    SDL_RenderDrawLine(renderer, 188, 575, 188, 675);
    SDL_RenderDrawLine(renderer, 263, 575, 263, 675);

    SDL_RenderDrawLine(renderer, 338, 575, 338, 675); //63
    SDL_RenderDrawLine(renderer, 413, 575, 413, 675);
    SDL_RenderDrawLine(renderer, 488, 575, 488, 675);
    SDL_RenderDrawLine(renderer, 563, 575, 563, 675);

    SDL_RenderDrawLine(renderer, 638, 575, 638, 675); //63
    SDL_RenderDrawLine(renderer, 713, 575, 713, 675);
    SDL_RenderDrawLine(renderer, 788, 575, 788, 675);
    SDL_RenderDrawLine(renderer, 863, 575, 863, 675);

    SDL_RenderDrawLine(renderer, 938, 575, 938, 675); //63
    SDL_RenderDrawLine(renderer, 1013, 575, 1013, 675);
    SDL_RenderDrawLine(renderer, 1088, 575, 1088, 675);
    SDL_RenderDrawLine(renderer, 1163, 575, 1163, 675);

    
    

    
}
void BSTDrawAt(SDL_Renderer *renderer, int lvl, int pos, int val, numberDrawer num){
    int starty = 75 + 100*(lvl-1);
    int startx = (1200/(pow(2, lvl-1)))*pos -1200/pow(2, lvl)-18;
    SDL_Rect rect{startx, starty , 38, 50};

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    num.drawNumber(renderer, val, rect);
}

void BSTDrawUnder(SDL_Renderer *renderer, int lvl, int pos, int val, numberDrawer num){
    int starty = 75 + 100*(lvl-1);
    int startx = (1200/(pow(2, lvl-1)))*pos -1200/pow(2, lvl)-18;
    SDL_Rect rect{startx, starty + 50 , 38, 50};

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    num.drawNumber(renderer, val, rect);
}

void BSTEraseUnder(SDL_Renderer *renderer, int lvl, int pos, numberDrawer num){
    int starty = 75 + 100*(lvl-1);
    int startx = (1200/(pow(2, lvl-1)))*pos -1200/pow(2, lvl)-18;
    SDL_Rect rect{startx, starty +50, 38, 50};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderFillRect(renderer, &rect);
}

void BSTDrawAtPos(SDL_Renderer *renderer, int pos, numberDrawer num){
    int lvl = 0, pospos = 0;

    if(pos < 0 || pos >63) return;

    if(pos % 2 != 0){
        lvl = 6;
        pospos = (pos +1) / 2;
    }else if(pos %4 != 0){
        lvl = 5;
        pospos = (pos +2) / 4;
    }else if(pos %8 != 0){
        lvl = 4;
        pospos = (pos +4) / 8;
    }else if(pos %16 != 0){
        lvl = 3;
        pospos = (pos +8) / 16;
    }else if(pos %32 != 0){
        lvl = 2;
        pospos = (pos +16) / 32;
    }else{
        lvl = 1;
        pospos = 1;
    }
    
    BSTDrawAt(renderer, lvl, pospos, pos, num);

}

#endif