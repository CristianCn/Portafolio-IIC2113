# Portafolio Semana 1

## Cristian Carreño


Si se quiere probar el código se debe hacer make desde la carpeta Semana1 y ejecutarlo de la siguiente forma `./simulator <scheduler> <file> <quantum>`

# Explicación del código:

El código presentado es una tarea que realicé con un compañero para el curso IIC2333 - Sistemas Operativos y Redes, el objetivo de la tarea era realizar una simulación de un scheduler de procesos utilizando tres algoritmos:

1. * FCFS

2. * Round-Robin

3. * Random


# ¿Por qué se escogió el código?

Escogí este código pues en mi opinión es un código que tiene una calidad pobre. Al entregarlo ya estabamos al tanto de esto, pero cumplía funcionalmente el objetivo requerido para la tarea. En este código es fácil evidenciar problemas de calidad que se podrían catalogar como universalmente aceptados como: repetición de código, mal uso de nombre de variables, código comentado sin utilizar y otros que se revisarán a continuación.


# Calidad de código

Es difícil establecer qué se entiende por código de calidad, pues surgen inmediatamente muchas preguntas, como por ejemplo:
1. * ¿Si el código cumple la funcionalidad y el tiempo es acotado, vale la pena crear un código reutilizable o de gran calidad?
2. * ¿El código debe ser corto y eficiente o de mayor extensión y de fácil lectura?
3. * ¿Las normas "universalmente aceptadas" deben ser un axioma al programar o se puede programar con buena calidad siguiendo principios que nos acomodan de forma personal?
4. * ¿Cómo definimos los pesos de las distintas partes de un código al establecer si es de buena calidad? Por ejemplo, si es más importante tener código rápido o más lento pero de fácil comprensión.
5. * Etc.

Como la calidad de código no es un tema de opinión unánime, se discutirá el código en solo algunos puntos que a mi parecer resultan intuitivamente malas prácticas.

# Discusión y análisis del código presentado

El código presentado es una tarea que presenta un código deficiente en términos de calidad en varios aspectos, los que se detallan a continuación:

1. * El código es desordenado y no existe una modularidad clara: Podemos ver en el archivo `Tarea1.c`que existen diversas funciones, las que representan la mayor parte del archivo pero están mezcladas con el código main principal, que puede verse desde la línea `660`, esto dificulta la lectura y entendimiento del código. Además hace que el código a la larga no sea mantenible ya que si se siguiera programando en este estilo se terminaría con un código de muchas líneas en un mismo archivo, lo que hace que el debuggeo sea muy difícil de realizar y sea complejo entender el código para terceros.

Podemos ver que la siguiente función:

 ```c
void erase_node(Nodo *nodo, WaitList *lista) {

  if (nodo->prev == NULL && nodo->next == NULL) {
    lista->inicio = NULL;
    lista->fin = NULL;
    lista->largo --;

  }
  ```
  está en el mismo archivo que la función `main`, pero `erase_node` es solo una función auxiliar por lo que no debería estar en el archivo principal.

2. * En los archivos no se utiliza consistentemente un solo idioma para desarrollar, por ejemplo podemos ver el método

```c
void erase_node(Nodo *nodo, WaitList *lista) {

  if (nodo->prev == NULL && nodo->next == NULL) {
    lista->inicio = NULL;
    lista->fin = NULL;
    lista->largo --;

  }
```
  con un nombre en ingles pero con variables en español. Esto dificulta la lectura del código al no mantener un estándar.

3. * Existe repetición de código: Como se puede ver, la función `roundrobin` y `fcfs` poseen estructuras muy similares, las que podrían haber sido modeladas como métodos para poder reutilizarse, de forma de ordenar el código y seguir el prinipio DRY, lo que claramente no se utilizó en esta tarea.

4. * En el archivo `Tarea1.c` existe gran cantidad de código comentado que no tiene ningún uso, solamente ensucia el código general. Esto quita claridad al leer el archivo. Además de esto no se respeta una formato a lo largo del archivo, es decir espacios después de definición de métodos o saltos de línea entre funciones lo que también quita claridad al código. Esto se puede ver a continuación

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

5. * No existen comentarios útiles que ayuden a terceros a entender el código, uno se enfrenta a un código de mala calidad y formato sin comentarios en lenguaje natural para guiar el entendimiento.
