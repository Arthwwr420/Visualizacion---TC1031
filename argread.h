/*
 * Argread.h
 * Se encarga de administrar los parametros de entrada del programa
 * autor: Arturo Balboa
 * fecha: 9/nov/2024
 */

#ifndef ARGREAD_h_
#define ARGREAD_h_

#include<iostream>
#include<fstream>
#include<algorithm>

//estructura con valores 
struct arginf{
    int chosenone = 0; //numero perteneciente al algoritmo a elegir
    int arrsize = 100; //cantidad de elementos a ordenar
    bool readFromFile = 0; //Se lee de un archivo?
    std::fstream file; //archivo de texto a leer
};

//Seleccion de algoritmo a usar, segun string
int selectSA(std::string ar1){
    
    if (ar1 == "bubble" || ar1 == "0"){
            return 0;
        }
        else if (ar1 == "shell" || ar1 == "1"){
            return 1;
        }
        else if (ar1 == "insertion" || ar1 == "2"){
            return 2;
        }
        else if (ar1 == "selection"|| ar1 == "3"){
            return 3;
        }
        else if (ar1 == "merge"|| ar1 == "4"){
            return  4;
        }
        else if(ar1 == "bogo" || ar1 == "5"){
            return 5;
        }
        else if(ar1 == "bst" || ar1 == "6"){
            return 6;
        }
        else{
            std::cout << 
            "Entrada no valida, el formato para la ejecucion es \" main + algoritmo + numero de elementos \" \n \
Los algoritmos son:  (0) Bubble , (1) Shell, (2) Insertion, (3) Selection, (4) Merge, (5) Bogo, (6) BST \n \
Si estas leyendo de un archivo, recuerda que el nombre del algoritmo va en minusculas y sin espacios";
            exit(1);
        }
}

//regresa parametro como char* (o string) dependiendo del 
char* getArgOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

//Analiza los argumentos de la consola y a partir de ellos sobreescribe out con los valores adecuados
void readPar( struct arginf* out, int argc, char** argv){
    int maxelements = 1200;

    //algoritmo a usar
    if (getArgOption(argv, argv+argc, "-a")){
        std::string ar1 = getArgOption(argv, argv+argc, "-a");
        std::transform(ar1.begin(), ar1.end(), ar1.begin(),
            [](unsigned char c){ return std::tolower(c); });

        out->chosenone = selectSA(ar1);
        
    }

    //numero de elementos
    if (getArgOption(argv, argv + argc, "-n") && out->chosenone != 6){
        std::string alg;
        switch (out->chosenone)
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
        unsigned int ar2 = std::stoi(getArgOption(argv, argv + argc, "-n"));
        try{
            if (ar2 > maxelements){
                throw 100;
            }

        }catch(int num){
            std::cout << "Error "<< num <<", numero excede el numero maximo de elementos para el algoritmo elegido. (Creeme es por tu propio bien)\n\
El numero maximo de elementos para " << alg << " es " << maxelements << "\n";
            exit(1);
        }
        
        out->arrsize = ar2;
    }else if(maxelements > 0){
        out->arrsize = (out->arrsize > maxelements) ? maxelements : out->arrsize;
    }

    out->readFromFile = 0;

    //archivo a leer
    if(getArgOption(argv, argv+argc, "-f")){
        std::string fileName = getArgOption(argv, argv+argc, "-f");
        try{
            out->file.open(fileName, std::fstream::in);
        }catch (int num){
            std::cout << "Error "<< num << ": Archivo \"" << fileName << "\" no encontrado. \n";
            exit(1);
        }


        if(!out->file){
            std::cout << "Algo salio mal al leer el archivo \"" << fileName << "\"\n";
            exit(1);
        }

        out->arrsize = -1; //la primer linea es el string del algoritmo a usar
        while (std::getline(out->file, fileName)){
            if(out->arrsize >= maxelements) break;
            if(out->arrsize == -1){
                out->chosenone = selectSA(fileName);
                if(out->chosenone == 5) maxelements = 10;
            }    
            out->arrsize++;
        }
        std::cout << out->arrsize << "\n";
        

        out->readFromFile = true;

    }


}

#endif