#include "list.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nombre[50];
}Item;

typedef struct{
  char nombre[50];
  int PA;
  int CantidadItems;
  List *listaItems;
}Jugador;

typedef struct{
  int tipo;
  char nombreJ[50];
  char auxIt[50];
  int PAux;
}Accion;


int main() {

  int opcion = 10'
  while (true) {

    mostrarMenu();
    
    scanf("%d", &opcion);
    printf("\n");
    
    
    
  }

  return 0;
}