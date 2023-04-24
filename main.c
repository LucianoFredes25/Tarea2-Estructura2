#include "list.h"
#include "hashmap.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nombre[50];
}Item;

typedef struct{
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

void mostrarMenu() {
  printf("\n---  Juego?  ---\n");
  printf("[1] Registrar Jugador.\n");
  printf("[2] Mostrar perfil de Jugador.\n");
  printf("[3] Agregar item a Jugador.\n");
  printf("[4] Eliminar item a Jugador.\n");
  printf("[5] Agregar puntos de habilidad a Jugador.\n");
  printf("[6] Mostrar jugadores con un item especifico.\n");
  printf("[7] Deshacer ultima accion del jugador.\n");
  printf("[8] Exportar Jugadores.\n");
  printf("[9] Cargar datos de Jugadores.\n");
  printf("[10] Salir.\n");
  printf("Seleccione una opción: ");
}

Jugador* obtenerDatosJugador(char nombre[50]){

  Jugador* newJ =(Jugador *) calloc(1, sizeof(Jugador));
  printf("Nombre : ");
  scanf("%s", nombre);
  newJ->PA = 0;
  newJ->CantidadItems = 0;
  newJ->listaItems = createList();
  return newJ;
}

void imprimirDatosJugador(Jugador* jugador, char nombre[50]){
  printf("\nPerfil de %s : Puntos de Habilidad = [%d] , Cantidad de Items [%d] ,\n", nombre, jugador->PA , jugador->CantidadItems);
  if(jugador->CantidadItems == 0)
    printf("No hay items asignados.\n");
  else{
    Item * it = firstList(jugador->listaItems);
    while(it != NULL){
      printf("%s", it->nombre);
      it = nextList(jugador->listaItems);
      if(it != NULL) printf(" , ");
    }
  }
}

//Opcion 1 Registrar jugador

void registrarJugador(HashMap* mapJugadores){
  char key[50];
  Jugador* newJ = obtenerDatosJugador(key);
  insertMap(mapJugadores, key, newJ);
}

//Opcion 2 Mostrar perfil jugador

void mostrarJugador(HashMap* mapJugadores){

  char key[50];
  printf("Ingrese el nombre del jugador: ");
  scanf("%s", key);

  Pair* player = searchMap(mapJugadores, key);
  if(player == NULL){
    printf("--- NO se encontro al jugador --- \n");
  }else{
    imprimirDatosJugador(player->value, key);
  }
  
}

//Opcion 3 agregar item
void agregarItem(HashMap* mapJugadores)
{
  char key[50];
  char 
  printf("Ingrese el nombre del jugador: ");
  scanf("%s", key);

  Pair* player = searchMap(mapJugadores, key);

  if(player == NULL){
    printf("--- NO se encontro al jugador --- \n");
    return;
  }
  
  printf("Ingrese el nombre del item");
  scanf("s",)
}

int main() {

  int opcion = 10;
  
  HashMap* mapJugadores = createMap(10000);
  HashMap* mapItems = createMap(10000);

  
  while (true) {

    mostrarMenu();
    
    scanf("%d", &opcion);
    printf("\n");
    
    switch(opcion){
      case 1:
        registrarJugador(mapJugadores);
        break;
      case 2:
        mostrarJugador(mapJugadores);
        break;
      case 
        3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
      case 10:
        break;
      default:
        printf("Opcion Invalida, ingrese nueva opcion\n");
    }
    if(opcion == 10)
      break;
  }

  return 0;
}