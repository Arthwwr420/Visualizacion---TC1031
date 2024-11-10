/*
*  autor: Arturo Balboa Alvarado
*  fecha: Sept 2024
*  Visualizador de algoritmos
*/

#include<iostream>
#include<SDL2/SDL.h>
#include<thread>
#include"sorts.h"
#include<algorithm>
#include"bst.h"
#include"argread.h"
#include<sstream>

const int WIDTH = 1200, HEIGHT = 675;


int main(int argc, char* argv[]){
    short unsigned int chosenone = 0;
    unsigned int arrsize = 100;

    struct arginf info;

    //read parameters 
    readPar(&info, argc, argv);

    arrsize = info.arrsize;
    chosenone = info.chosenone;


    //Create Array
    int array[arrsize];
    int BSTarray[] = {32, 16, 48, 8, 24, 40, 56, 4, 12, 20, 28, 36, 44, 52, 60, 2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 
                1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63};

    
    if(info.readFromFile){ //cargar elementos del archivo al array
        std::string aux;
        int count = -1;
        info.file.clear();
        info.file.seekg(0);
        while(std::getline(info.file, aux)){
            if(count < arrsize){
                array[count] = std::stoi(aux);
            }
            count ++;
        }
    }else{ //nuevo array de arrsize elementos
        newOrderArray(array, arrsize);
        shuffle(array, arrsize);
    }

    int max = maxint(array, arrsize);
    std::cout << max << "\n";

    bool running = true;

    //SDL stuff so I can create the window
    SDL_Init( SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow( "I love sorting algorithms!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
    

    if (window == NULL){ //Por si algo falla
        std::cout << "No se pudo crear ventana: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Event windowEvent;

    //Initial black screen
    SDL_RenderPresent(renderer);
    std::this_thread::sleep_for<int64_t, std::milli>(std::chrono::milliseconds(1000));

    //Visualize
    switch (chosenone)
    {
    case 0:
        running = bubble(array, arrsize, HEIGHT, WIDTH, renderer);
        break;
    
    case 1:
        running = shell(array, arrsize, HEIGHT, WIDTH, renderer);
        break;
    case 2:
        running = insertion(array, arrsize, HEIGHT, WIDTH, renderer);
        break;
    case 3:
        running = selection(array, arrsize, HEIGHT, WIDTH, renderer);
        break;
    case 4:
        running = mergeSort(array, arrsize, 0, arrsize, HEIGHT, WIDTH, renderer);
        break;
    case 5: 
        running = BogoSort(array, arrsize, HEIGHT, WIDTH, renderer);
        break;
    case 6:
        running = orderBST(renderer);
        break;
    default:
        break;
    }

    //end of sort visualization
    SDL_RenderPresent(renderer);

    //end screen
    while(true){
        if (!running) break;
        
        std::this_thread::sleep_for<int64_t, std::milli>(std::chrono::milliseconds(1000/35));
        //INPUT
        if (SDL_PollEvent(&windowEvent))
            if (windowEvent.type == SDL_QUIT) break;

    }

    //Escribir al archivo Out.txt los valores ordenados
    if(info.readFromFile){
        std::fstream out;
        out.open("Out.txt", std::fstream::out);
        out << "Datos ordenados: \n";

        for(int i = 0 ; i < arrsize ; i++){
            out << array[i] << "\n";
        }

        out.close();
        info.file.close();
    }

    //Matar ventana
    SDL_RenderPresent(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
    
}