#ifndef SORTS_H
#define SORTS_H

#include<vector>
#include<list>
#include"renderermanager.h"


//Encontrar el valor maximo de un array
int maxint(int arr[], int size){
    int max = arr[0];
    for(int i = 0; i < size; i++){
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

//cambiar de lugar 2 elementos de un arreglo
void swap(int* arr, int i, int j){
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

//checa si el arreglo esta ordenado (usado por bogo)
bool sorted(int arr[], int size){
    for (int i = 1; i < size ; i++){
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

//Reordenar aleatoriamente todo el arreglo
void shuffle(int * arr, int size){
    srand (time(NULL));
    int in = 0;
    int in2 = 0;
    for (int i = 0; i < size*3; i++){
        in = rand() % size;
        in2 = rand() % size;
        swap(arr, in, in2);
    }
}

// funcion bubble sort
bool bubble(int arr[], int size, int H, int W, SDL_Renderer *renderer){
    int max = maxint(arr, size);
    bool running  = true; 
    SDL_Event windowEvent;

    for (int i = size -1; i > 0 ; i--){

        if (!running) return false; //regresar falso si se cierra la ventana mientras se ejecuta el algoritmo

        for (int j = 0; j < i ; j++){

        std::this_thread::sleep_for<int64_t, std::micro>(std::chrono::microseconds(1));

        if (SDL_PollEvent(&windowEvent))
            if (windowEvent.type == SDL_QUIT){ //input de cerrar ventana
                running = false;
                break;
                } 


            if (arr[j] > arr[j+1]) swap(arr, j, j +1);

            UpdateArrayRender(arr, size, H, W, max, renderer);
            SDL_RenderPresent(renderer); //actualizar renderer y presentarlo
            }   
    }

    return true; //si el programa no se cierra mientras el algoritmo se ejectuta, regresar true (para no cerrar la ventana)

}

// funcion shell
bool shell(int *arr, int size, int H, int W, SDL_Renderer *renderer){
    bool ordered = false;

    int max = maxint(arr, size);
    bool running  = true;
    SDL_Event windowEvent;
	
    // Ciclo principal que empieza con particiones de 1/8 parte del arreglo
	for (int n = size/8; n > 0; n--){
		int i = 0;
		do{
			ordered = true;

            // bubble con las particiones adecuadas
			for (int i = 0; i + n < size; i++){

				if (arr[i] > arr[i + n]){
                    std::this_thread::sleep_for<int64_t, std::micro>(std::chrono::microseconds(100));

                    if (SDL_PollEvent(&windowEvent))
                        if (windowEvent.type == SDL_QUIT){//input de cerrar ventana
                            running = false;
                            break;
                        } 

					ordered = false;
					swap(arr, i, i + n);

                    UpdateArrayRender(arr, size, H, W, max, renderer);
                    SDL_RenderPresent(renderer);

				}
			}

            if (!running) return false; //regresar falso si se cierra la ventana mientras se ejecuta el algoritmo

		}while (!ordered);
	}

    return true;
}

//funcion selection
bool selection(int arr[], int size, int H, int W, SDL_Renderer *renderer){
    int minindex = 0;

    int max = maxint(arr, size);
    bool running  = true;
    SDL_Event windowEvent;

	for (int i = 0; i < size; i++) {
        if (!running) return false; //regresar falso si se cierra la ventana mientras se ejecuta el algoritmo

		minindex = i;

		for (int j = i; j < size; j++) {
            std::this_thread::sleep_for<int64_t, std::nano>(std::chrono::nanoseconds(10));

            if (SDL_PollEvent(&windowEvent)) 
                if (windowEvent.type == SDL_QUIT){ //input de cerrar ventana
                    running = false;
                    break;
                } 

			
			if (arr[j] < arr[minindex])
				minindex = j;
            
            UpdateArrayRender(arr, size, H, W, max, renderer);
            SDL_RenderPresent(renderer);

		}

		swap(arr, minindex, i);
	}

	return true;
}

//funcion Insertion 
bool insertion(int arr[], int size, int H, int W, SDL_Renderer *renderer){
    int curr = 0;

    int max = maxint(arr, size);
    bool running  = true;
    SDL_Event windowEvent;

    for (int i = 1; i < size; i++){
        curr = arr[i];
        arr[i] = 0;
        if(!running) return false; //regresar falso si se cierra la ventana mientras se ejecuta el algoritmo

        for (int j = i - 1; j >=0; j--){
            std::this_thread::sleep_for<int64_t, std::milli>(std::chrono::milliseconds(1));

            if (SDL_PollEvent(&windowEvent))
                if (windowEvent.type == SDL_QUIT){ //input de cerrar ventana
                    running = false;
                    break;
                } 

            UpdateArrayRender(arr, size, H, W, max, renderer);
            SDL_RenderPresent(renderer);

            if (arr[j] < curr) {   
                arr[j+1] = curr;
                break;
            }

            swap(arr, j + 1, j);

            if(j==0){
                arr[j] = curr;
            }
        
        }

    UpdateArrayRender(arr, size, H, W, max, renderer);
    SDL_RenderPresent(renderer);
    
    }

    return true;
}

//Combinar 2 partes ordenadas de un arreglo (para merge)
bool merge(int *arr, int start, int mid, int finish, const int &size, const int &H, const int &W, SDL_Renderer *renderer){
    int max = maxint(arr, size);
    bool running  = true;
    SDL_Event windowEvent;

    //Crear 2 arreglos auxiliares para guardar los datos
    int Lsize = mid - start +1;
    int Rsize = finish - mid;
    int auxL[mid - start+1];
    int auxR[finish - mid];

    //Llenar los 2 arreglos auxiliares con los datos
    for (int i = 0; i < Lsize; i++)
        auxL[i] = arr[i + start];
    
    for (int i = 0; i< Rsize; i++)
        auxR[i] = arr[i + mid + 1];

    int i = 0;
    int j = 0;
    int k = start;

    //Sobreeescribir arreglo original con los elementos ordenados de los auxuiliares
    while(i < Lsize && j < Rsize){
        std::this_thread::sleep_for<int64_t, std::micro>(std::chrono::microseconds(10000));
        if (SDL_PollEvent(&windowEvent))
            if (windowEvent.type == SDL_QUIT){ //input de cerrar ventana
                return false; //regresar falso si se cierra la ventana mientras se ejecuta el algoritmo
            } 
        
        if (auxL[i] <= auxR[j]){
            arr[k] = auxL[i];
            i++;
        }else{
            arr[k] = auxR[j];
            j++;
        }
        k++;

        UpdateArrayRender(arr, size, H, W, max, renderer);
        SDL_RenderPresent(renderer);
    }

    //Llenar con el resto de elementos del primer arreglo (si es que quedan)
    while (i < Lsize) {
        std::this_thread::sleep_for<int64_t, std::micro>(std::chrono::microseconds(10000));
        if (SDL_PollEvent(&windowEvent))
            if (windowEvent.type == SDL_QUIT){ //input de cerrar ventana
                return false; //regresar falso si se cierra la ventana mientras se ejecuta el algoritmo
            } 

        arr[k] = auxL[i];
        i++;
        k++;

        UpdateArrayRender(arr, size, H, W, max, renderer);
        SDL_RenderPresent(renderer);
    }

    //Llenar con el resto de elementos del primer arreglo (si es que quedan)
    while (j < Rsize) {
        std::this_thread::sleep_for<int64_t, std::micro>(std::chrono::microseconds(10000));
        if (SDL_PollEvent(&windowEvent))
            if (windowEvent.type == SDL_QUIT){ //input de cerrar ventana
                return false; //regresar falso si se cierra la ventana mientras se ejecuta el algoritmo
            } 
    
        arr[k] = auxR[j];
        j++;
        k++;

        UpdateArrayRender(arr, size, H, W, max, renderer);
        SDL_RenderPresent(renderer);
    }

    return true;

}

//Funcion recursiva Merge Sort
bool mergeSort(int arr[], int size, int strt, int fns, int H, int W, SDL_Renderer *renderer){
    bool running;



    if (fns <= strt) return true;

    int mid = strt + (fns - strt)/2;

    running = mergeSort(arr, size, strt, mid, H, W, renderer);
    if(!running) return false; //regresar falso si se cierra la ventana mientras se ejecuta el algoritmo
    running = mergeSort(arr, size, mid +1, fns, H, W, renderer);
    if(!running) return false; //regresar falso si se cierra la ventana mientras se ejecuta el algoritmo
    running = merge(arr, strt, mid, fns, size, H, W, renderer);
    if(!running) return false; //regresar falso si se cierra la ventana mientras se ejecuta el algoritmo

    return true;
}


//WARNING: DO NOT USE WITH A LOT OF ELEMENTS
bool BogoSort(int arr[], int size, int H, int W, SDL_Renderer *renderer){
    int max = maxint(arr, size);
    bool running  = true;
    SDL_Event windowEvent;

    while (!sorted(arr, size)){
        std::this_thread::sleep_for<int64_t, std::micro>(std::chrono::microseconds(200));

        if (SDL_PollEvent(&windowEvent))
            if (windowEvent.type == SDL_QUIT){
                return false; //regresar falso si se cierra la ventana mientras se ejecuta el algoritmo
            } 
        
        shuffle(arr, size);

        UpdateArrayRender(arr, size, H, W, max, renderer);
        SDL_RenderPresent(renderer);

    }

    return true;

}

//random elements from 1 to 100
void newArray(int arr[], int size){
    srand (time(NULL));
    for (int i = 0; i < size; i++){
        arr[i] = rand() % 100 +1;
    }
}

//elementos de 1 a n para un arreglo de tamaño n
void newOrderArray(int arr[], int size){
    for (int i = 0; i < size; i++){
        arr[i] = i+1;
    }
}


#endif