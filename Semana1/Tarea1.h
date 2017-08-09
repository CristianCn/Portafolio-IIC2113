#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <string.h>


int loop;

typedef struct Process  {
	int pid;
	int prioridad;
	char *estado;
  char nombre[256];
	int contador;
  int tiempo_ejecucion;
  int tiempo_inicio;
  int sec_tiempos;
	int n;
	int *array;
	int tiempo_restante;
	int subsequencia; //El indice de la subsecuencia de A_i o B_i
	int tiempo_stop;
	int veces_q_cpu_escoge;
	int veces_bloqueo;
	int primer_tiempo_uso_cpu;
	bool comenzo;
	int tiempo_muerte;

}Process;

typedef struct Queue {
	Process *cola;
	int largo;

}Queue;



typedef struct Nodo  {
	struct Process *proceso;
	struct Nodo *next;
	struct Nodo *prev;
}Nodo;

typedef struct WaitList {
	Nodo *inicio;
  Nodo *fin;
  int largo;

}WaitList;
