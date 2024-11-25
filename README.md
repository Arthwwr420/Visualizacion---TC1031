# Visualizador de ordenamiento de algoritmos

El proyecto se basa en un programa que visualiza algoritmos de ordenamiento o el funcionamiento de un arbol de busqueda binaria segun los parametros de ejecucion. Esto se hace con la libreria de SDL.

## Instrucciones de uso
### Compilacion

Debido al uso de SDL, el comando usado para compilar debe de incluir la libreria:

g++ -I SDL2src/include -L SDL2src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

### Ejecucion
Al ejecutar el programa desde la consola, se pueden poner otros 3 parametros de entrada distintos:

main -a (algoritmo) -n (numero de elementos) -f (nombre de archivo)

- -a: Recibe el tipo de algoritmo a utilizar
- -n: Recibe el numero de elementos a ordenar, debe ser menor al numero maximo de elementos del algoritmo a utilizar (si se usa con BST toma el valor como un elemento a buscar en el arbol, escribiendo en Out.txt en que nivel del arbol encontró el valor)
- -f: Recibe el nombre del archivo a leer (Si se usa junto a los otros parametros de entrada, los valores de los mismos serán sobreescritos)

Cada algoritmo de ordenamiento tiene un numero maximo de elementos que se pueden ordenar. 
Si el programa se ejecuta sin parametros o desde el explorador de archivos, se mostrara el ordenamiento de 100 elementos con un bubble sort.
En caso de querer usar el programa para visualizar un arbol de busqueda binaria el parametro leido de -n, por lo que no hay necesidad de escribirlo en este contexto.

### Archivo txt de datos
El programa puede leer un archivo de entrada con cierto formato si se da el nombre del archivo como parametro. Sin embargo para el correcto funcionamiento del programa el archivo debe de:
- Tener el nombre del algoritmo a usar para ordenar los elementos en la primer fila, escrito en minusculas y si espacios
- Alternativamente se pueden tener los numeros del 0 al 5 en esta primera linea, cada uno perteneciente a su algoritmo respectivo (vease: Algoritmos)
- Cada linea despues de la primera debe de tener un solo numero entero, de otra manera el programa podria no funcionar de manera correcta
- Si se sobrepasa el numero maximo de elementos a ordenar en un archivo, el programa ignorara el resto de numeros.

## Algoritmos
El programa tiene 6 algoritmos que se pueden mostrar usandolos como primer parametro:
- Bubble Sort (paramatero: "bubble" o "0") Numero maximo de elementos: 1200
- Shell Sort (paramatero: "shell" o "1") Numero maximo de elementos: 1200
- Insertion Sort (paramatero: "insertion" o "2") Numero maximo de elementos: 1200
- Selection Sort (paramatero: "selection" o "3") Numero maximo de elementos: 1200
- Merge Sort (paramatero: "merge" o "4") Numero maximo de elementos: 1200
- Bogo Sort (paramatero: "bogo" o "5") Numero maximo de elementos: 10

- Arbol de busqueda binaria (parametro:  "BST" o "6"), Siempre llena un arbol con una lista de 63 numeros colocados de tal manera que el arbol quede balanceado (es un BST no un AVL)

### Ejemplos de uso

main -a selection

- Muestra el ordenamiento de 100 elementos(predeterminado) con el algoritmo selection sort

main -a merge -n 1200

- Muestra el ordenamiento de 1200 elementos con el algoritmo merge sort

main -f Elementos.txt

- Lee el archivo Elementos.txt, muestra el ordenamiento de los numeros que contiene y escribe los numeros ordenados a Out.txt

main -a BST -n 32

- Muestra el ordenamiento de elementos en un BST, al terminar la animacion busca en el arbol el numero 32 y escribe en Out.txt el nivel en el que encontro el numero.

## Subcompetencias

### SICT0301: Evalúa los componentes
Cada algoritmo tiene una complejidad distinto:
- Bubble Sort: O(n^2) en promedio, O(n) en el mejor caso
- Shell Sort: O(n^1.25) en promdeio, 0(n^2) en el peor caso
- Insertion Sort: O(n^2) en promedio, O(n) en el mejor caso
- Selection Sort: O(n^2) - Misma complejidad independiente del caso
- Merge Sort: O(n log n) - Misma complejidad independientemente del caso
- Bogo Sort: O((n-1)n!) en promedio, mejor caso O(n) y peor caso O(infinito)
- BST: O(h) (en donde h es la altura) en promedio al buscar, O(n) en el peor caso, y O(1) en el mejor caso. O(h) (donde h es altura) en promedio al insertar, en el peor de los casos O(n) y el mejor O(1) (arbol vacio)
- Complejidad del Programa: La complejidad del programa varia dependiendo de los parametros de entrada, o el algoritmo que se va a utilizar, la complejidad de las funciones del programa independientes de los algoritmos y el BST no pasa de O(n), por lo que la complejidad del programa, en el programa las funciones tienen comentarios con su respectiva complejidad (en los que solo hay un valor se refiere a que es el mismo para peor caso, mejor y promedio)

### SICT0302: Toma decisiones
Se eligieron los algoritmos para su visualizacion y la comparacion del funcionamiento y efectividad de cada uno de manera visual.
Se eligio tambien añadir el BST para tener una visualizacion del funcionamiento del mismo, además de tener una representacion visual que sirve no solo para el BST en sí, sino que, al compartir hasta cierto punto estructura con otros árboles (como el AVL, por ejemplo), tambien es de ayuda al entender estas otras estructuras de datos.

### SICT0303 Implementa acciones científicas
La estructura de arbol binario puede ser consultada al verla representada graficamente en la pantalla, ademas de mostrar el ordenamiento paso a paso de los elementos de acuerdo al arbol. si se da el parametro de tamaño del arreglo con el comando de BST, se busca ese elemento en el arbol y se escribe en Out.txt el nivel en el que se encontro el valor
Para leer datos de archivo, solo hace falta colocar un archivo en el directorio del ejecutable y pasar el nombre de archivo como parametro, estos datos seran los que se ordenarán, mostrando en pantalla el proceso
Para escribir los datos en un archivo, se toman los datos del archivo de entrada, ya ordenados por el programa, y se escribe en un archivo de nombre "Out.txt"
