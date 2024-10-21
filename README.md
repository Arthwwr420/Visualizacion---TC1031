# Visualizador de ordenamiento de algoritmos

El proyecto se basa en un programa que visualiza algoritmos de ordenamiento o el funcionamiento de un arbol de busqueda binaria segun los parametros de ejecucion. Esto se hace con la libreria de SDL.

## Instrucciones de uso
### Compilacion

Debido al uso de SDL, el comando usado para compilar debe de incluir la libreria:

g++ -I SDL2src/include -L SDL2src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2

### Ejecucion
Al ejecutar el programa desde la consola, se pueden poner otros 2 parametros de entrada, el primero siendo el algoritmo que se desea usar y el segundo el numero de elementos a ordenar, por ejemplo:

main merge 200 

(ordena 200 elementos usando el merge sort)

Cada algoritmo de ordenamiento tiene un numero maximo de elementos que se pueden ordenar. Si el programa se ejecuta sin parametros o desde el explorador de archivos, se mostrara el ordenamiento de 100 elementos con un bubble sort.

En caso de querer usar eprograma para visualizar un arbol de busqueda binaria el segundo parametro se ignorará, por lo que no hay necesidad de escribirlo en este contexto.

## Algoritmos
El programa tiene 6 algoritmos que se pueden mostrar usandolos como primer parametro:
- Bubble Sort (paramatero: "bubble" o "0") Numero maximo de elementos: 1200
- Shell Sort (paramatero: "shell" o "1") Numero maximo de elementos: 1200
- Insertion Sort (paramatero: "insertion" o "2") Numero maximo de elementos: 1200
- Selection Sort (paramatero: "selection" o "3") Numero maximo de elementos: 1200
- Merge Sort (paramatero: "merge" o "4") Numero maximo de elementos: 1200
- Bogo Sort (paramatero: "bogo" o "5") Numero maximo de elementos: 10

- Arbol de busqueda binaria (parametro:  "BST" o "6"), Siempre llena un arbol con una lista de 63 numeros colocados de tal manera que el arbol quede balanceado (es un BST no un AVL)

## Subcompetencias

### SICT0301: Evalúa los componentes
Cada algoritmo tiene una complejidad distinto:
- Bubble Sort: O(n^2) en promedio, O(n) en el mejor caso
- Shell Sort: O(n^1.25) en promdeio, 0(n^2) en el peor caso
- Insertion Sort: O(n^2) en promedio, O(n) en el mejor caso
- Selection Sort: O(n^2) - Misma complejidad independiente del caso
- Merge Sort: O(n log n) - Misma complejidad independientemente del caso
- Bogo Sort: O((n-1)n!) en promedio, mejor caso O(n) y peor caso O(infinito)

### SICT0302: Toma decisiones
Se eligieron los algoritmos para su visualizacion y la comparacion del funcionamiento y efectividad de cada uno de manera visual.
Se eligio tambien añadir el BST debido a que es de las estructuras de datos a las que mas le puede ser de utilidad tener una visualizacion clara.
