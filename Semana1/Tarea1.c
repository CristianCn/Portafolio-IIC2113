#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "Tarea1.h"
#include <string.h>
#include <signal.h>

/*FUNCIONES*/




void sigint_handler(int dummy) {
	puts("*********************");
	puts("El programa ha sido cortado por la señan CTRL + C");
	puts("Estadisticas hasta el momento:");
	loop = 0;

}


void imprimir_estadisticas(int tiempo, Queue *cola_procesos, int dead_processes) {
	printf("Se terminaron de ejecutar %d procesos\n",dead_processes );
	printf("La simulacion duro %d unidades de tiempo\n\n",tiempo );
	for (int i = 0; i < cola_procesos->largo; i++) {
		printf("_____________Estadisticas proceso: %s____________\n", cola_procesos->cola[i].nombre);
		if (cola_procesos->cola[i].estado == "DEAD") {
			puts("El proceso termino de ejecutarse");

			printf("Veces que fue elegido para usar CPU:%d\n",cola_procesos->cola[i].veces_q_cpu_escoge );
			printf("Veces que se bloqueo: %d\n",cola_procesos->cola[i].veces_bloqueo );
			printf("Turnaround time:%d\n",cola_procesos->cola[i].tiempo_muerte - cola_procesos->cola[i].primer_tiempo_uso_cpu );
			printf("Response time:%d\n",cola_procesos->cola[i].tiempo_inicio - cola_procesos->cola[i].primer_tiempo_uso_cpu );
			printf("Waiting Time:%d\n\n",cola_procesos->cola[i].tiempo_muerte - cola_procesos->cola[i].tiempo_inicio - cola_procesos->cola[i].tiempo_ejecucion );
		}
		else{
			puts("El proceso no ha terminado de ejecutarse se dan estadisticas parciales");
			printf("Veces que fue elegido para usar CPU:%d\n",cola_procesos->cola[i].veces_q_cpu_escoge );
			printf("Veces que se bloqueo: %d\n",cola_procesos->cola[i].veces_bloqueo );
			puts("El Turnaround time no es posible de calcular pues no ha terminado");
			if (cola_procesos->cola[i].primer_tiempo_uso_cpu > tiempo) {
				printf("Response time:%d\n",cola_procesos->cola[i].tiempo_inicio - cola_procesos->cola[i].primer_tiempo_uso_cpu );

			}
			else{
				puts("No es posible calcular el Response Time todavia");
			}
			puts("No es posible calcular el Waiting Time todavia\n");


		}
		puts("__________________________________________");
		}
	/* code */
}

Nodo* GetNewNode(Process *proceso) {

  Nodo *newNode = malloc(sizeof(Nodo));
  newNode->next = NULL;
  newNode->prev = NULL;
  newNode->proceso = proceso;
  return newNode;
}

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

void erase_node(Nodo *nodo, WaitList *lista) {

  if (nodo->prev == NULL && nodo->next == NULL) {
    lista->inicio = NULL;
    lista->fin = NULL;
    lista->largo --;

  }

  else if (nodo->prev == NULL && nodo->next != NULL) {//es la cabeza
    lista->largo--;
    lista->inicio = nodo->next;
    nodo->next->prev = NULL;
  }

  else if (nodo->prev != NULL && nodo->next == NULL) {// es la cola
    lista->largo --;
    lista->fin = nodo->prev;
    nodo->prev->next = NULL;
  }
  else{
    lista->largo--;
    nodo->next->prev = nodo->prev; // deslinkeo el nodo a eliminar
    nodo->prev->next = nodo->next; // deslinkeo el nodo a eliminar
  }

}



int id = 0;
Process *crea_proceso(){
  Process *proceso = malloc(sizeof(Process));
  proceso->pid = id;
  id++;
  proceso->contador = 0;
  proceso->estado = "WAITING";
  proceso->subsequencia = 0;
  proceso->tiempo_stop = 0;
	proceso->veces_bloqueo = 0;
	proceso->veces_q_cpu_escoge = 0;
	proceso->comenzo = false;
	proceso->primer_tiempo_uso_cpu = 0;



  return proceso;
}

void selectionSort(int max_index, Process *arreglo) {

   int indexMin,i,j;

   for(i = 0; i < max_index-1; i++) {

      indexMin = i;

      for(j = i+1;j<max_index;j++) {
         if(arreglo[j].tiempo_inicio < arreglo[indexMin].tiempo_inicio) {

            indexMin = j;
         }
      }

      if(indexMin != i) {

         Process temp = arreglo[indexMin];
         arreglo[indexMin] = arreglo[i];
         arreglo[i] = temp;

      }


   }
}


int give_quantum(int quantum, int priority){
  if (priority> 1 && priority <= 32) {
    return (priority*quantum + 30*quantum)/62;

  }
  else{
    return (priority/32) * quantum;
  }

}


int lines_n(const char *name){

    FILE *fp = fopen(name,"r");
    int lines = 0;
    int ch;
    while(!feof(fp))
    {ch = fgetc(fp);
    if(ch == '\n'){
        lines++;
            };
    };
    fclose(fp);
    return lines;
}

int comp(const void *p1, const void *p2){

  struct Process *p_1 = (struct Process *) p1;
  struct Process *p_2 = (struct Process *) p2;
  return (p_1->tiempo_inicio - p_2->tiempo_inicio);

}

int queda_proceso(Process *proceso){
	int total = 0;
  for (int i = proceso->subsequencia; i < 2*proceso->n - 1; i++) {
    total = total + proceso->array[i];
}
return total-proceso->tiempo_stop;
}

void revisar_llegada(Queue *cola_procesos, int tiempo){

	for (int i = 0; i < cola_procesos->largo; i++) {
		if (cola_procesos->cola[i].tiempo_inicio == tiempo) {
			printf("Se ha creado el proceso: %s\n",cola_procesos->cola[i].nombre );
		}
}}

void revisar_wait(WaitList *cola){
  Nodo *actual = cola->inicio;
  for (int i = 0; i < cola->largo; i++) {//revisa los wait y actualiza los tiempos
    if (actual->proceso->tiempo_restante == 1) {
      actual->proceso->estado = "READY";
			printf("El proceso %s pasa a estado READY\n",actual->proceso->nombre );
      actual->proceso->subsequencia++;
      actual->proceso->tiempo_restante = actual->proceso->array[actual->proceso->subsequencia];
      erase_node(actual, cola);
			i--;
    }
    else{
      actual->proceso->tiempo_restante --;
    }
    actual = actual->next;
  }// end del for
}

// ------------- RR--------------------
void roundrobin(int qut, WaitList *cola_wait, Queue *cola_procesos) {
  int tiempo = 0;
	loop = 1;
  Process *proceso_actual = NULL;
	puts("________________________________________");
  printf("Tiempo actual: %d\n",tiempo );
  int deads = 0;
  while (loop == 1) {

    sleep(1);

    int accionador = 0;
    for (int j = 0; j < cola_procesos->largo; j++) {

      if (cola_procesos->cola[j].estado == "READY" &&
        cola_procesos->cola[j].tiempo_inicio <= tiempo) {
          accionador ++;
          int new_q = give_quantum(qut, cola_procesos->cola[j].prioridad);
          cola_procesos->cola[j].estado = "RUNNING";
          proceso_actual = &cola_procesos->cola[j];
					proceso_actual->veces_q_cpu_escoge ++;
					if (proceso_actual->comenzo == false){
						proceso_actual->primer_tiempo_uso_cpu = tiempo;
					}
					proceso_actual->comenzo = true;
					revisar_llegada(cola_procesos, tiempo);
          //printf("|    - - - - - - -   Scheduler continua con el proceso: %s    - - - - - - -     |\n", proceso_actual->nombre);
          proceso_actual->tiempo_restante = proceso_actual->array[proceso_actual->subsequencia] - proceso_actual->tiempo_stop;
					printf("Entra proceso: %s a cpu, tiempo restante en ella:%d\n",proceso_actual->nombre,proceso_actual->tiempo_restante );
					printf("|   Proceso:  %s   |    Ejecutado %i tiempos    |    Faltan %d tiempos   |\n",proceso_actual->nombre,proceso_actual->tiempo_ejecucion,queda_proceso(proceso_actual));

          while (new_q > 0 && loop == 1){
            proceso_actual->tiempo_restante --; //sera el tiempo de la subsecuencia activa
            proceso_actual->tiempo_ejecucion ++;

            if (proceso_actual->tiempo_restante == 0 &&
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
								printf("Tiempo de waiting del proceso:%s es:%d\n", proceso_actual->nombre,proceso_actual->tiempo_restante );
                revisar_wait(cola_wait);
								proceso_actual->veces_bloqueo ++; // suponemos que es solo cuando pasa de running a waiting, no cuando recorre quantum
                InsertAtTail(cola_wait, proceso_actual);
                tiempo++;
								revisar_llegada(cola_procesos, tiempo);
								puts("________________________________________");
                printf("Tiempo actual: %d\n",tiempo );
                break;
              }

            else if(proceso_actual->tiempo_restante == 0){
								printf("El proceso llamado:%s ha sido destruido\n",proceso_actual->nombre );
                //printf("|    - - - - - - -   Se destruye un proceso llamado: %s    - - - - - - -    |\n\n",proceso_actual->nombre );
                proceso_actual->estado = "DEAD";
								proceso_actual->tiempo_muerte = tiempo+1;
                proceso_actual = NULL;
                deads ++;
                revisar_wait(cola_wait);
                tiempo++;
								revisar_llegada(cola_procesos, tiempo);
								puts("________________________________________");
                printf("Tiempo actual: %d\n",tiempo );
                break;
                }

            else if (new_q == 1){
              proceso_actual->tiempo_stop = proceso_actual->tiempo_stop + give_quantum(qut, cola_procesos->cola[j].prioridad);
              proceso_actual->estado = "READY";
              revisar_wait(cola_wait);
              tiempo++;
							revisar_llegada(cola_procesos, tiempo);
							printf("Proceso %s se detiene por cumplir el quantum, le falta(n) %i tiempo(s) para cumplir esta secuencia\n",proceso_actual->nombre,proceso_actual->tiempo_restante);
							puts("________________________________________");
              printf("Tiempo actual: %d\n",tiempo );
              break;
            }
            new_q --;
            revisar_wait(cola_wait);
						signal(SIGINT, sigint_handler);
            tiempo ++;
						printf("Proceso_actual es:%s\n",proceso_actual->nombre );
						revisar_llegada(cola_procesos, tiempo);
						puts("________________________________________");
            printf("Tiempo actual: %d\n",tiempo );
          }

        } //if ready

			}// for i in cola
			if (accionador == 0){
			  revisar_wait(cola_wait);
				revisar_llegada(cola_procesos, tiempo);
			  tiempo++;
				puts("________________________________________");
			  printf("Tiempo actual: %d\n",tiempo );
			}
			if (cola_procesos->largo == deads){//era igual a 0
	      puts("****************Fin de la simulacion************");
	      puts("No quedan mas procesos en la cola, se apaga la CPU...");
	      break;/* code */
	    }
			signal(SIGINT, sigint_handler);
			}
			imprimir_estadisticas(tiempo, cola_procesos, deads); // while true
			}//funcion


void fcfs(WaitList *cola_wait, Queue *cola_procesos) {
  int tiempo = 0;
	loop = 1;
  Process *proceso_actual = NULL;
  int dead_processes = 0;
  while (loop == 1) {

    printf("Tiempo actual: %d\n",tiempo );

    sleep(1);


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
        else{
          actual->proceso->tiempo_restante --;


        }
        actual = actual->next;


      }// end del for

    }// end del 1er if

    if (proceso_actual == NULL) {
      /* code */


    for (int j = 0; j < cola_procesos->largo; j++) {

      if (cola_procesos->cola[j].tiempo_inicio == tiempo) {
        printf("Se ha creado el proceso: %s\n", cola_procesos->cola[j].nombre);

      }

      if (cola_procesos->cola[j].estado == "READY" &&
        cola_procesos->cola[j].tiempo_inicio <= tiempo) {
					if (cola_procesos->cola[j].comenzo == false) { // aqui guardo el tiempo de 1er uso de cpu
						cola_procesos->cola[j].primer_tiempo_uso_cpu = tiempo;
						cola_procesos->cola[j].comenzo = true;

						/* code */
					}

          cola_procesos->cola[j].estado = "RUNNING";

          /*En la linea anterior se cambia de A_i para tener una variable
          mas a la mano del tiempo restante en ese estado Running en este caso*/
          proceso_actual = &cola_procesos->cola[j];
          proceso_actual->tiempo_restante = proceso_actual->array[proceso_actual->subsequencia];
          //printf("Tiempo:%d\n",proceso_actual->array[proceso_actual->subsequencia] );
          printf("Entra proceso: %s a cpu, tiempo restante en ella:%d\n",proceso_actual->nombre,proceso_actual->tiempo_restante );
					printf("|   Proceso:  %s   |    Ejecutado %i tiempos    |    Faltan %d tiempos   |\n",proceso_actual->nombre,proceso_actual->tiempo_ejecucion,queda_proceso(proceso_actual));
					//printf("tiempo_inicio:%d, tiempo actual:%d\n",proceso_actual->tiempo_inicio, tiempo );
					proceso_actual->veces_q_cpu_escoge++;
          break;

      }
      }

    }
    if (proceso_actual != NULL) {

			revisar_llegada(cola_procesos, tiempo);
      //puts("entra a bajar el tiempo");
      proceso_actual->tiempo_restante --; //sera el tiempo de la subsecuencia activa
      proceso_actual->tiempo_ejecucion ++;// esto hacerlo si no es null
      //printf("Tiempo restante: %d\n", proceso_actual->tiempo_restante );
      printf("proceso_actual es:%s\n",proceso_actual->nombre );



    if (proceso_actual->tiempo_restante == 0 &&
      proceso_actual->subsequencia < proceso_actual->n * 2 -1 - 1) {// el ultimo es por el indice de arrays
        //puts("Se le acaba el tiempo en CPU,tiempo_restante es cero");
        printf("Se le acaba el tiempo en CPU al proceso:%s, entra a estado WAITING\n", proceso_actual->nombre);
        proceso_actual->subsequencia ++;
        proceso_actual->tiempo_restante = proceso_actual->array[proceso_actual->subsequencia];
        proceso_actual->estado = "WAITING";
				proceso_actual->veces_bloqueo ++;


        InsertAtTail(cola_wait, proceso_actual);
        //proceso_actual->tiempo_restante = proceso_actual->array[proceso_actual->subsequencia];
        printf("Tiempo de waiting del proceso:%s es:%d\n", proceso_actual->nombre,proceso_actual->tiempo_restante );
        //proceso_actual->tiempo_restante--;//esto es nuevo
        proceso_actual = NULL;
        //puts("Entra el proceso a waiting");


      /* code */
    }
    else if(proceso_actual->tiempo_restante == 0){
      printf("El proceso llamado:%s ha sido destruido\n",proceso_actual->nombre );

      proceso_actual->estado = "DEAD";
			proceso_actual->tiempo_muerte = tiempo;
      proceso_actual = NULL;

      dead_processes++;
      }
    }


    if (cola_procesos->largo == dead_processes) {//era igual a 0
      puts("****************Fin de la simulacion************");
      puts("No quedan mas procesos en la cola, se apaga la CPU...");

      break;
      /* code */
    }





    puts("________________________________________");
    signal(SIGINT, sigint_handler);
    tiempo++;
  }


	imprimir_estadisticas(tiempo, cola_procesos, dead_processes);


}



void RandomScheduler(WaitList *cola_wait, Queue *cola_procesos) {
  int tiempo = 0;
	loop = 1;
  Process *proceso_actual = NULL;
  bool posible= false;
  int dead_processes = 0;
  while (loop == 1) {
    printf("Tiempo actual: %d\n",tiempo );

    sleep(1);

    if (cola_wait->largo != 0) {

      Nodo *actual = cola_wait->inicio;
      //puts("efrain");
      for (int i = 0; i < cola_wait->largo; i++) {//revisa los wait y actualiza los tiempos
        //puts("efrain 2");
        if (actual->proceso->tiempo_restante == 0) {
          //puts("no se imprime");


          actual->proceso->estado = "READY";
          printf("El proceso %s pasa a estado READY\n",actual->proceso->nombre );
          //puts("Cambia estado");
          actual->proceso->subsequencia++;

          actual->proceso->tiempo_restante = actual->proceso->array[actual->proceso->subsequencia];
          //puts("no falla");
          erase_node(actual, cola_wait);
          i--;
          //puts("falla");
        }
        else{
          actual->proceso->tiempo_restante --;
        }
        actual = actual->next;


      }// end del for

    }// end del 1er if

    if (proceso_actual == NULL) {
      /* code */

     // para ver si hay un proceso realmente ready
    for (int i = 0; i < cola_procesos->largo; i++) {

			if (cola_procesos->cola[i].tiempo_inicio == tiempo) {
				printf("Se ha creado el proceso: %s\n",cola_procesos->cola[i].nombre );

			}

      if (cola_procesos->cola[i].tiempo_inicio <= tiempo && cola_procesos->cola[i].estado == "READY") {
        posible = true;
        //printf("El proceso posible es:%s, estado:%s\n",cola_procesos->cola[i].nombre,cola_procesos->cola[i].estado );
        }

      }

    while (proceso_actual == NULL && posible) {//mientras la CPU este desocupada
      //printf("posible: %d\n",posible );
      int j = rand() % cola_procesos->largo;
      //printf("cola_procesos largo:%d y rand:%d\n",cola_procesos->largo, rand() );
      //printf("Este es el j generado%d\n",j );
      /* code */

      //puts("Revisando cola de procesos...");
      if (cola_procesos->cola[j].estado == "READY" &&
        cola_procesos->cola[j].tiempo_inicio <= tiempo) {
					if (cola_procesos->cola[j].comenzo == false) { // aqui guardo el tiempo de 1er uso de cpu
						cola_procesos->cola[j].primer_tiempo_uso_cpu = tiempo;
						cola_procesos->cola[j].comenzo = true;
						/* code */
					}
          //printf("El j elegido es:%d\n",j );

          cola_procesos->cola[j].estado = "RUNNING";
          posible = false;

          /*En la linea anterior se cambia de A_i para tener una variable
          mas a la mano del tiempo restante en ese estado Running en este caso*/
          proceso_actual = &cola_procesos->cola[j];
          proceso_actual->tiempo_restante = proceso_actual->array[proceso_actual->subsequencia];
          //printf("Tiempo:%d\n",proceso_actual->array[proceso_actual->subsequencia] );
          printf("Entra proceso: %s a cpu tiempo, restante en ella:%d\n",proceso_actual->nombre,proceso_actual->tiempo_restante );
					printf("|   Proceso:  %s   |    Ejecutado %i tiempos    |    Faltan %d tiempos   |\n",proceso_actual->nombre,proceso_actual->tiempo_ejecucion,queda_proceso(proceso_actual));
					//printf("tiempo_inicio:%d, tiempo actual:%d\n",proceso_actual->tiempo_inicio, tiempo );
					proceso_actual->veces_q_cpu_escoge++;


      }
      }

    }
    if (proceso_actual != NULL) {
      //puts("entra a bajar el tiempo");
      proceso_actual->tiempo_restante --; //sera el tiempo de la subsecuencia activa
      proceso_actual->tiempo_ejecucion ++;// esto hacerlo si no es null
      //printf("Tiempo restante: %d\n", proceso_actual->tiempo_restante );
      printf("proceso_actual es:%s\n",proceso_actual->nombre );


    // if (proceso_actual->tiempo_restante == 0) {
    //   puts("Se le acaba el tiempo en CPU");
    //   /* code */
    // }

    if (proceso_actual->tiempo_restante == 0 &&
      proceso_actual->subsequencia < proceso_actual->n * 2 -1 - 1) {// el ultimo es por el indice de arrays
        //puts("Se le acaba el tiempo en CPU,tiempo_restante es cero");
        printf("Se le acaba el tiempo en CPU al proceso:%s, entra a estado WAITING\n", proceso_actual->nombre);
        proceso_actual->subsequencia ++;
        proceso_actual->tiempo_restante = proceso_actual->array[proceso_actual->subsequencia];
        proceso_actual->estado = "WAITING";
				proceso_actual->veces_bloqueo ++;

        //printf("El proceso:%s,esta en:  %s\n",proceso_actual->nombre, proceso_actual->estado );//borrar


        InsertAtTail(cola_wait, proceso_actual);
        //proceso_actual->tiempo_restante = proceso_actual->array[proceso_actual->subsequencia];
        printf("Tiempo de waiting del proceso:%s es:%d\n", proceso_actual->nombre,proceso_actual->tiempo_restante );

        proceso_actual = NULL;


      /* code */
    }
    else if(proceso_actual->tiempo_restante == 0){
      printf("El proceso llamado:%s ha sido destruido\n",proceso_actual->nombre );
      proceso_actual->estado = "DEAD";
			proceso_actual->tiempo_muerte = tiempo;
      proceso_actual = NULL;
      //cola_procesos->largo --;
      dead_processes ++;
      }
    }

    tiempo++;
		signal(SIGINT, sigint_handler);
		if (cola_procesos->largo == dead_processes) {//era igual a 0
      puts("****************Fin de la simulacion************");
      puts("No quedan mas procesos en la cola, se apaga la CPU...");

      break;
      /* code */
    }

    puts("________________________________________");
  }
  /* code */

	imprimir_estadisticas(tiempo, cola_procesos, dead_processes);
}


/*-----------------------MAIN----------------*/

int main(int argc, char const *argv[]) {
  /* code */

  const char *scheduler = argv[1];
  printf("El scheduler elegido es:%s\n",scheduler );
  FILE* archivo = fopen(argv[2], "r");

	int quantum = 3;
  if (argc > 2) {
    int quantum = atoi(argv[3]);
    printf("El quantum es: %d\n", quantum );

  }

  int numero_procesos = lines_n(argv[2]);
  int max_procesos = numero_procesos;


  Queue *cola_procesos = malloc(sizeof(Queue));
  cola_procesos->cola = malloc(sizeof(Process)*numero_procesos);
  int posicion = 0;
  cola_procesos->largo = max_procesos;

  while (numero_procesos > 0) {
    Process *proceso = crea_proceso();
    proceso->tiempo_stop =0;

    fscanf(archivo, "%s", proceso->nombre);


    fscanf(archivo, "%i", &proceso->prioridad);
    //printf("La Prioridad es:%d\n",proceso->prioridad );
    fscanf(archivo, "%i", &proceso->tiempo_inicio);

    fscanf(archivo, "%i", &proceso->n);
    //printf("El n del proceso es:%d\n",proceso->n );
    int a = 2 * proceso->n - 1;
    int *listaTiempos = malloc(sizeof(int)* (2*a-1));
    proceso->array = listaTiempos;
    proceso->estado = "READY";

    int aux = 0;
    while (a > 0) {
      fscanf(archivo, "%i", &listaTiempos[aux]);

      aux ++;
      a --;

    }

    cola_procesos->cola[posicion] = *proceso;
    posicion++;

    numero_procesos--;


  }

  qsort(cola_procesos->cola, max_procesos, sizeof(Process), comp);
  /*ORDENAMOS LA COLA SEGUN ORDEN DE INICIO*/

  WaitList *Cola_wait = malloc(sizeof(WaitList));
  Cola_wait->largo = 0;
  Cola_wait->fin = NULL;
  Cola_wait->inicio = NULL;


  puts("**********************");
  puts("Empieza la simulacion");
  puts("**********************");

	if (strcmp(argv[1],"roundrobin") == 0) {
		roundrobin(quantum,Cola_wait, cola_procesos);


	}
	else if (strcmp(argv[1],"fcfs") == 0) {
		fcfs(Cola_wait, cola_procesos);

	}
	else if (strcmp(argv[1],"random") == 0) {

		RandomScheduler(Cola_wait,cola_procesos);

	}



  return 0;
}
