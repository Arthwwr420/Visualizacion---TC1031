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

const int WIDTH = 1200, HEIGHT = 675;


int main(int argc, char* argv[]){
    short unsigned int chosenone = 0;
    unsigned int maxelements = 1200;
    unsigned int arrsize = 100;

    //read parameters 
    if (argv[1] != NULL){
        std::string ar1 = argv[1];
        std::transform(ar1.begin(), ar1.end(), ar1.begin(),
            [](unsigned char c){ return std::tolower(c); });

        if (ar1 == "bubble" || ar1 == "0"){
            chosenone = 0;
        }
        else if (ar1 == "shell" || ar1 == "1"){
            chosenone = 1;
        }
        else if (ar1 == "insertion" || ar1 == "2"){
            chosenone = 2;
        }
        else if (ar1 == "selection"|| ar1 == "3"){
            chosenone = 3;
        }
        else if (ar1 == "merge"|| ar1 == "4"){
            chosenone = 4;
        }
        else if(ar1 == "bogo" || ar1 == "5"){
            chosenone = 5;
            maxelements = 10;
        }
        else if(ar1 == "bst" || ar1 == "6"){
            chosenone = 6;
        }
        else{
            std::cout << 
            "Entrada no valida, el formato para la ejecucion es \" main + algoritmo + numero de elementos \" \n \
Los algoritmos son:  (0) Bubble , (1) Shell, (2) Insertion, (3) Selection, (4) Merge, (5) Bogo, (6) BST \n";
            exit(1);
        }
    }

    if (argv[2] !=  NULL && chosenone != 6){
        std::string alg;
        switch (chosenone)
        {
        case 0:
            alg = "Bubble";
            break;
        case 1:
            alg = "Shell";
            break;
        case 2:
            alg = "Insertion";
            break;
        case 3:
            alg = "Selection";
            break;
        case 4:
            alg = "Merge";
            break;
        case 5:
            alg = "Bogo";
            break;
        default:
            break;
        }
        unsigned int ar2 = std::stoi(argv[2]);
        try{
            if (ar2 > maxelements){
                throw 100;
            }

        }catch(int num){
            std::cout << "Error "<< num <<", numero excede el numero maximo de elementos para el algoritmo elegido. (Creeme es por tu propio bien)\n\
El numero maximo de elementos para " << alg << " es " << maxelements << "\n";
            exit(1);
        }
        
        arrsize = ar2;
    }else if(maxelements > 0){
        arrsize = (arrsize > maxelements) ? maxelements : arrsize;
    }


    //Create Array
    int array[arrsize];
    int BSTarray[] = {32, 16, 48, 8, 24, 40, 56, 4, 12, 20, 28, 36, 44, 52, 60, 2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 
                1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63};
    newOrderArray(array, arrsize);
    shuffle(array, arrsize);

    int max = maxint(array, arrsize);
    std::cout << max << "\n";

    bool running = true;

    //SDL stuff so I can create the window
    SDL_Init( SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow( "I love sorting algorithms!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
    

    if (window == NULL){
        std::cout << "No se pudo crear ventana: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Log("Hello World");

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
    default:
        break;
    }

    


    SDL_RenderPresent(renderer);
    //end screen
    while(true){
        if (!running) break;
        
        std::this_thread::sleep_for<int64_t, std::milli>(std::chrono::milliseconds(1000/35));
        //INPUT
        if (SDL_PollEvent(&windowEvent))
            if (windowEvent.type == SDL_QUIT) break;


        //RENDERING
        //UpdateArrayRender(array, arrsize, HEIGHT, WIDTH, max, renderer);
        //SDL_RenderPresent(renderer);
    }
        SDL_RenderPresent(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
    
}