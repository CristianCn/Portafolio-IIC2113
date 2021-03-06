# Portafolio Semana 1

## Cristian Carreño


Si se quiere probar el código se debe hacer make desde la carpeta Semana1 y ejecutarlo de la siguiente forma `./simulator <scheduler> <file> <quantum>`, los archivos `Tarea1.c` y `Tarea1.h`solo se incluyen como referencia del código completo, pero la crítica se hace a trozos de esté código que se presentan el siguiente README.md.

## Explicación del código:

El código presentado es una tarea que realicé con un compañero para el curso IIC2333 - Sistemas Operativos y Redes, el objetivo de la tarea era realizar una simulación de un scheduler de procesos utilizando tres algoritmos:

1. * FCFS

2. * Round-Robin

3. * Random


## ¿Por qué se escogió el código?

Escogí este código pues en mi opinión es un código que tiene una calidad pobre. Al entregarlo ya estabamos al tanto de esto, pero cumplía funcionalmente el objetivo requerido para la tarea. En este código es fácil evidenciar problemas de calidad que se podrían catalogar como universalmente aceptados como: repetición de código, mal uso de nombre de variables, código comentado sin utilizar y otros que se revisarán a continuación. Este artefacto tiene estrecha relación con el curso pues es un ejemplo de "código de mala calidad", en el sentido de la forma en como está escrito, por lo que sería necesario hacer refactoring sobre él si se fuese a ocupar posteriormente. En la semana vimos ideas generales de lo que es un mal código, presento este artefacto a modo de realizar un análisis crítico con contenidos de ingeniería de software, pero presentaré problemas que a mi juicio son intuitivamente indicios de "mal código" mas que indicios guiados por la literatura.


## Calidad de código

Es difícil establecer qué se entiende por código de calidad, pues surgen inmediatamente muchas preguntas, como por ejemplo:
* ¿Si el código cumple la funcionalidad y el tiempo es acotado, vale la pena crear un código reutilizable o de gran calidad?
* ¿El código debe ser corto y eficiente o de mayor extensión y de fácil lectura?
* ¿Las normas "universalmente aceptadas" deben ser un axioma al programar o se puede programar con buena calidad siguiendo principios que nos acomodan de forma personal?
* ¿Cómo definimos los pesos de las distintas partes de un código al establecer si es de buena calidad? Por ejemplo, si es más importante tener código rápido o más lento pero de fácil comprensión.
* Etc.

Como la calidad de código no es un tema de opinión unánime, se discutirá el código en solo algunos puntos que a mi parecer resultan intuitivamente malas prácticas.

## Discusión y análisis del código presentado

El código presentado es una tarea que presenta un código deficiente en términos de calidad en varios aspectos, los que se detallan a continuación:

* ### El código es desordenado y no existe una modularidad clara:

Podemos ver en el archivo `Tarea1.c` que existen diversas funciones, las que representan la mayor parte del archivo pero están mezcladas con el código main principal, que puede verse desde la línea `660`, esto dificulta la lectura y entendimiento del código. Además hace que el código a la larga no sea mantenible, si se continúa programando de esta forma se tendría un solo archivo gigante sin un hilo conductor coherente. Esto hace que el debuggeo sea muy difícil de realizar y sea complejo entender el código por terceros.

La función erase_node mostrada a continuación:

 ```c
void erase_node(Nodo *nodo, WaitList *lista) {

  if (nodo->prev == NULL && nodo->next == NULL) {
    lista->inicio = NULL;
    lista->fin = NULL;
    lista->largo --;

  }
```
está en el mismo archivo que la función `main`, pero `erase_node` es solo una función auxiliar, por lo que no debería estar en el archivo principal, esto hace que se mezclen responsabilidades en un mismo archivo.

* ### En los archivos no se utiliza consistentemente un solo idioma para desarrollar:

por ejemplo la función InsertAtTail:

```c
void InsertAtTail(WaitList *lista, Process *proceso) {
	Nodo *newNode = GetNewNode(proceso);

  /*Caso de lista vacia*/
  if (lista ->fin == NULL && lista ->inicio == NULL) {
    newNode->prev = lista->inicio;
    newNode->next = lista->fin;
    lista->inicio = newNode;
    lista->fin = newNode;
    lista->largo++;

  }
  else{
    newNode->prev = lista->fin;

    newNode->next = NULL;
    lista->fin->next = newNode;
    lista->fin = newNode;
    lista->largo++;}


}
```
posee un nombre en inglés, pero las variables utilizadas al interior de esta están algunas en español y otras en inglés. Esto dificulta la lectura del código para un tercero, pues no existe un estándar en el lenguaje natural utilizado.

* ### Repetición de código:
Como se puede ver, la función `Random` y `fcfs` poseen estructuras muy similares y hay repetición del mismo código, esto podría haber sido modelado como un método para poder reutilizarse, de forma de ordenar el código y seguir el prinipio DRY (Don't repeat yourself), lo que claramente no se utilizó en esta tarea.

A continuación se muestra un fragmento de código que se reutiliza en ambas funciones:

```c
if (cola_wait->largo != 0) {

  Nodo *actual = cola_wait->inicio;
  //puts("efrain");
  for (int i = 0; i < cola_wait->largo; i++) {//revisa los wait y actualiza los tiempos
    //puts("efrain 2");

    if (actual->proceso->tiempo_restante == 0) { // cero a 1


      actual->proceso->estado = "READY";
      printf("El proceso %s pasa a estado READY\n",actual->proceso->nombre );

      actual->proceso->subsequencia++;

      actual->proceso->tiempo_restante = actual->proceso->array[actual->proceso->subsequencia];

      erase_node(actual, cola_wait);
      i--;

    }
```
este trozo se ocupa desde la línea 363 en la función `fcfs` y desde la línea 512 en la función `RandomScheduler`. Con esto se añade código innecesario "ensuciando" el código y haciendolo más extenso de forma innecesaria.

* ### Código comentado sin utilizar:

En el archivo `Tarea1.c` existe gran cantidad de código comentado que no tiene ningún uso, solamente ensucia el código general. Esto quita claridad al leer el archivo. Además de esto no se respeta una formato a lo largo del archivo, es decir espacios después de definición de métodos o saltos de línea entre funciones lo que también quita claridad al código. Esto se puede ver a continuación:

```c
if (proceso_actual->tiempo_restante == 0 && //linea 272
  proceso_actual->subsequencia < proceso_actual->n * 2 -1 - 1) {
    //printf("Se le acaba el tiempo en CPU a: %s, tiempo restante es cero\n", proceso_actual->nombre);
    proceso_actual->subsequencia ++;
    proceso_actual->tiempo_restante = proceso_actual->array[proceso_actual->subsequencia];
    proceso_actual->estado = "WAITING";
    //printf("Tiempo de waiting del proceso: %s es %d\n", proceso_actual->nombre,proceso_actual->tiempo_restante );
    //puts("--------------- Entra el proceso a waiting  ------------------------");
    //printf("|    - - - - - - -     Proceso %s a estado WAITING    - - - - - - -    |\n\n", proceso_actual->nombre);
    printf("Se le acaba el tiempo en CPU al proceso:%s, entra a estado WAITING\n", proceso_actual->nombre);
    proceso_actual->tiempo_stop=0;
```

* ### No existen comentarios útiles que ayuden a terceros a entender el código:

Un tercero se enfrenta a un código de mala calidad y formato sin comentarios en lenguaje natural para guiar el entendimiento.

## Conclusión:

Me parece que el código mostrado posee un pésima calidad pero cumple los objetivos principales que se pedían en la tarea. Por temas de tiempo y carga académica muchas veces escribimos código siguiendo la metodología `code & fix` sabiendo que es una mala práctica, pero se ocupa de igual forma pues se privilegia cumplir con los requisitos principales de las tareas y cumplir los deadlines. Hecho parecido que ocurre en la creación de software real al privilegiar el `Time To Market` en vez de la calidad del código, lo que claramente no es óptimo.
