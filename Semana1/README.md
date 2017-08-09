# Repositorio Tarea 1

##Integrantes:

###Ignacio Urzua

###Cristian Carreño

Para usar el scheduler se debe hacer make desde la carpeta del repositorio y ejecutarlo como se indica `./simulator <scheduler> <file> <quantum>``

# Explicación de los algoritmos:

##FCFS:

* El algoritmo FCFS se creó con una cola de procesos representada con el struct
`Queue` que se fue llenando al inicio del programa con los datos que se recaban
del archivo .txt que se lee, luego de esto los procesos se ordenan en la cola
según el tiempo de llegada a la CPU (i.e. cuando se crean los procesos), el
scheduler está representado con un loop infinito que tiene como condicion de
término una variable global que vale 1 o 0. Los procesos se mantiene en la cola
en todo momento y solo cambian de estado, los que son: WAITING, READY, RUNNING y
DEAD (estado añadido por simplicidad). Cuando los procesos entran a estado
WAITING son añadidos a una cola creada con el struct WaitList que representa una
lista doblemente ligada para almacenar los procesos en estado waiting, cuando un
proceso pasa a este estado se añade y cuando queda READY se elimina de la cola.
El algoritmo básicamente va añadiendo un tiempo en cada loop y revisa la cola
waiting para bajarle el tiempo de espera a estos procesos y eventualmente cambiarlos
a estado READY, luego de esto se hace un loop de todos los procesos de la cola `Queue`
para ver que proceso escoger y poner en funcionamiento (estado RUNNING), luego de esto se rebajan los tiempos correspondientes de los procesos, los procesos se recorren en orden en la cola `Queue` y si se encuentra con un proceso READY (si es que la CPU esta libre) lo coloca en funcionamiento, cumpliendo lo indicado por los algoritmos FCFS.
La condicion de termino del loop es cuando todos los procesos se hayan terminado de ejecutar o cuando se desencadena la señal `CTRL + C` que se atrapa y cambia la condición de término del loop infinito por lo que éste para y se imprimen las estadísticas correspondientes.

##RANDOM:

* El algoritmo Random funciona de forma equivalente al FCFS, con el único cambio que no se revisa secuencialmente la cola `Queue`de procesos sino que se hace un random que va desde 1 al largo de la cola para escoger cual proceso entrará a la CPU, este random se da en un loop hasta que encuentre un proceso en estado READY y que haya llegado. El funcionamiento de las colas es igual al FCFS y posee las mismas condiciones de término.


##ROUND ROBIN:


* El algoritmo utiliza las mismas estructuras que FCFS y RANDOM. Este algoritmo se compone de un While que funcionará hasta que hayan dejado de ejecutarse todos los procesos o hasta que se pulse `CTRL + C` en la consola. En cada iteración del While, se recorren en orden según su tiempo de llegada todos los procesos, y se trata de que siguiendo el orden ejecute cada uno de los proceso su quantum correspondiente de tiempos.

* Si en esta revisión un proceso está en estado READY y el tiempo de llegada es menor o igual al tiempo actual, el proceso pasa a estado RUNNING y utilizará un máximo de quantum, que es determinado según su prioridad, veces la cpu (puede ser menos dependiendo del valor de A_i).

* En cada ejecución en la CPU pueden pasar diversas cosas con cada proceso (en cada momento va aumentando el tiempo en 1):

    * Puede morir el proceso (cuando se ejecutó cumpliendo la secuencia de A y B), con nuevo estado DEAD
    * Puede pasar a estado WAITING (cuando termino la subsecuencia A_i)
    * Puede seguir en estado READY al tener un quantum menor al A_i y entregar la CPU (guardando el tiempo en el que se detuvo)
    * Puede ejecutar un tiempo más el proceso

* La función revisa en cada iteración si es que se detecta la señal enviada al pulsar `CTRL + C`, y si es que es así manda a imprimir todas las estadísticas que se tengan recabadas hasta ese momento.

* Para modelar se utilizaron las mismas estructuras descritas anteriormente, revisando periódicamente la cola Wait para cambiar los procesos a READY cuando corresponda, manejando bien la cola de procesos y utilizando diversas funciones auxiliares para ordenar la función.

#SUPUESTOS:

1. * El proceso Idle no se presenta como un proceso ejecutandose pues no hace nada por lo tanto hay posibilidad de que se muestre en consola solo el tiempo, es ahí donde no hay procesos en ejecución (en CPU) y ahí actúa el Idle.

2. * Como se dijo en ayudantía tenemos el numero de procesos al leer el archivo por eso creamos colas de tamaño fijo (el número de procesos).

3. * El Response Time se tomó como el tiempo en que llega un proceso a la CPU - el tiempo en que se ejecuta en CPU por primera vez.

4. * El Turnaround Time se consideró como tiempo en que muere el proceso - tiempo en que entra a CPU por primera vez.

5. * Las veces que se bloqueo son la cantidad de veces que pasa de Running a Waiting.

6. * Por simplicidad se inician los procesos en READY pero no se ejecutan si no han llegado.

7. * El output que dice cuantos tiempos le quedan a un proceso corresponden a la suma de todos los A y B (subsecuencias) que aún no ejecuta.
