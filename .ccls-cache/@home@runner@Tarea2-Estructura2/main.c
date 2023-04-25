#include "list.h"
#include "hashmap.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nombre[50];
  int cantidad;
}Item;

typedef struct{
  int PA; //puntos de habilidad
  int CantidadItems;
  HashMap *mapItems;
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
/*
printf("...");
puts(...);
fflush();
  */
Jugador* obtenerDatosJugador(char nombre[50]){

  Jugador* newJ =(Jugador *) calloc(1, sizeof(Jugador));
  printf("Nombre : ");
  scanf("%s", nombre);
  newJ->PA = 0;
  newJ->CantidadItems = 0;
  newJ->mapItems = createMap(10000);
  return newJ;
}

void mostrarItem(Item* item){
  printf("%s : %d", item->nombre, item->cantidad);
}

void imprimirDatosJugador(Jugador* jugador, char nombre[50]){
  printf("\nPerfil de %s : Puntos de Habilidad = [%d] , Cantidad de Items [%d]\n", nombre, jugador->PA , jugador->CantidadItems);
  if(jugador->CantidadItems == 0)
    printf("No hay items asignados.\n");
  else{
    Pair* it = firstMap(jugador->mapItems);
    while(it != NULL){
      mostrarItem(it->value);
      it = nextMap(jugador->mapItems);
      if(it != NULL) printf(" ,\n");
    }
  }
}

//Opcion 1 Registrar jugador

void registrarJugador(HashMap* mapJugadores){
  char key[50];
  Jugador* newJ = obtenerDatosJugador(key);
  insertMap(mapJugadores, key, newJ);
  printf("Jugador registrado correctamente!\n");
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
void agregarItem(HashMap* mapJugadores , HashMap * mapItems)
{
  char blank[50];
  char key[50];
  char keyItem[50];
  printf("Ingrese el nombre del jugador: ");
  scanf("%s", key);

  Pair* player = searchMap(mapJugadores, key);

  if(player == NULL){
    printf("--- NO se encontro al jugador --- \n");
    return;
  }
  
  printf("Nombre del item: ");
  fgets(blank, 50, stdin);
  fgets(keyItem, 50, stdin);
  keyItem[strcspn(keyItem, "\n")] ='\0';


  Pair* bPar = searchMap(((Jugador*)(player->value))->mapItems, keyItem);

  if(bPar == NULL){
    Item* new = calloc(1, sizeof(Item));
    strcpy(new->nombre, keyItem);
    new->cantidad =  1;
    insertMap( ((Jugador*)(player->value))->mapItems, keyItem, new);
  }else{
    ((Item*)(bPar->value))->cantidad++;
  }
  
  ((Jugador*)(player->value))->CantidadItems++;
  printf("--- Se agrego correctamente el item!!! --- \n");
  
}

//opcion 4 Eliminar item a jugador

void eliminarItem(HashMap* mapJugadores , HashMap * mapItems){
  char blank[50];
  char key[50];
  char keyItem[50];
  printf("Ingrese el nombre del jugador: ");
  scanf("%s", key);

  Pair* player = searchMap(mapJugadores, key);

  if(player == NULL){
    printf("--- NO se encontro al jugador --- \n");
    return;
  }
  
  printf("Nombre del item: ");
  fgets(blank, 50, stdin);
  fgets(keyItem, 50, stdin);
  keyItem[strcspn(keyItem, "\n")] ='\0';


  Pair* bPar = searchMap(((Jugador*)(player->value))->mapItems, keyItem);

  if(bPar == NULL){
    printf("--- NO se encontro el item!!! --- \n");
    return; 
  }

  ((Item*)(bPar->value))->cantidad--;

  if(((Item*)(bPar->value))->cantidad == 0){
    eraseMap(((Jugador*)(player->value))->mapItems, keyItem);
  }
  
}

//opcion 5 Agregar PA
void asignarPuntos(HashMap * mapJugadores){
  char blank[50];
  char key[50];
  int puntos;
  printf("Ingrese el nombre del jugador: ");
  scanf("%s", key);

  Pair* player = searchMap(mapJugadores, key);

  if(player == NULL){
    printf("--- NO se encontro al jugador --- \n");
    return;
  }

  printf("Ingrese puntos a añadir : ");
  scanf("%d", &puntos);
  ((Jugador*)(player->value))->PA += puntos;
  printf("Puntos añadidos correctamente!\n");
}
  

//opcion 6 mostrar jugadores con un item especifico

//void item

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
      case 3:
        agregarItem(mapJugadores, mapItems);
        break;
      case 4:
        eliminarItem(mapJugadores, mapItems);
        break;
      case 5:
        asignarPuntos(mapJugadores);
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