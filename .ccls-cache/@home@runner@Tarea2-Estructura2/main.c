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
  char nombre[50];
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

Jugador* obtenerDatosJugador(){
  
  Jugador* newJ = (Jugador *) calloc(1, sizeof(Jugador));
  printf("Nombre : ");
  scanf("%s", newJ->nombre);
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
  Jugador* newJ = obtenerDatosJugador();
  insertMap(mapJugadores, newJ->nombre, newJ);
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
void agregarItem(HashMap* mapJugadores)
{
  
  char key[50];
  
  printf("Ingrese el nombre del jugador: ");
  scanf("%s", key);

  Pair* player = searchMap(mapJugadores, key);

  if(player == NULL){
    printf("--- NO se encontro al jugador --- \n");
    return;
  }

  char blank[50];
  char keyItem[50];
  
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

void eliminarItem(HashMap* mapJugadores){
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
  ((Jugador*)(player->value))->CantidadItems--;
  
  if(((Item*)(bPar->value))->cantidad == 0){
    eraseMap(((Jugador*)(player->value))->mapItems, keyItem);
  }
  
}

//opcion 5 Agregar PA
void asignarPuntos(HashMap * mapJugadores){

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

void itemEspecifico(HashMap* mapJugadores){
  
  char blank[50];
  char key[50];
  char keyItem[50];
  printf("Nombre del item a buscar: ");
  fgets(blank, 50, stdin);
  fgets(keyItem, 50, stdin);
  keyItem[strcspn(keyItem, "\n")] ='\0';

  List* nombreJugadores = createList();

  Pair* it = firstMap(mapJugadores);
  Pair* bPar;
  int cont = 0;

  
  while(it != NULL){
    bPar = searchMap( ((Jugador*)(it->value))->mapItems , keyItem);

    if(bPar==NULL) printf("No halle nada \n");
    
    if( bPar != NULL){
      cont++;
      pushBack(nombreJugadores, ((Jugador*)(it->value))->nombre );
    }
    it = nextMap(mapJugadores);
  }

  char* itn = firstList(nombreJugadores);

  printf("se encontraron %d con el item.\n", cont);
  
  while(itn !=NULL){
    printf("%s \n", itn);
    itn = nextList(nombreJugadores);
  }
  
  cleanList(nombreJugadores);
  free(nombreJugadores);
  
}

//opcion 7 deshacer ultima accion

void deshacerAccion(HashMap* mapJugadores){
  
  char claveJugador[50];
  char claveItem[50];
  printf("Ingrese el nombre del jugador: \n");
  scanf("%s",claveJugador);
  
  Pair* player = (Pair*) searchMap(mapJugadores, claveJugador);

  if (player == NULL){
    printf("--- NO se encontro al jugador --- \n");
    return;
  }
  Pair* it = firstMap(mapJugadores);
  while (it != NULL){
    Pair* itemPar = searchMap(((Jugador*)(it->value))->mapItems, claveItem);
    if (itemPar == NULL){
      printf("El jugador no ha realizado ninguna acción");
      return;
    }
  }
}

//opcion 8 exportar
void exportarDatos(HashMap* mapJugadores){
  
}

//Opcion 9 importar 
//al momento de importar y mostrar los item de un jugador no los reconoce todos
void importarDatos(HashMap* mapJugadores)
{
 char nombreArchivo[50];
    FILE* archivo;
    int numJugadores = 0;

    printf("Ingrese el nombre del archivo a importar: ");
    scanf("%s", nombreArchivo);
    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }

    char buffer[1024];
    char* campos[11];
    while (fgets(buffer, 1024, archivo) != NULL) {
        char* token = strtok(buffer, ",");
        int i = 0;
        while (token != NULL && i < 10) {
            campos[i] = token;
            token = strtok(NULL, ",");
            i++;
        }

        if (i != 10) {
            printf("Error al leer la línea del archivo: %s\n", buffer);
            continue;
        }

        Jugador* jugador = (Jugador*)malloc(sizeof(Jugador));
        strcpy(jugador->nombre, campos[0]);
        jugador->PA = atoi(campos[1]);

        jugador->CantidadItems = atoi(campos[2]);

        jugador->mapItems = createMap(10000);
        for (int j = 0; j < jugador->CantidadItems; j++) {
            char* nombreItem = campos[j + 3];
            Pair* itemPair = searchMap(jugador->mapItems, nombreItem);
            if (itemPair == NULL) {
                Item* item = (Item*)malloc(sizeof(Item));
                strcpy(item->nombre, nombreItem);
                item->cantidad = 1;
                insertMap(jugador->mapItems, item->nombre, item);
            }
            else {
                ((Item*)itemPair->value)->cantidad++;
            }
        }

        insertMap(mapJugadores, jugador->nombre, jugador);
        numJugadores++;
    }

    fclose(archivo);
    printf("Se importaron %d jugadores desde el archivo %s\n", numJugadores, nombreArchivo);
}

int main() {

  int opcion = 10;
  
  HashMap* mapJugadores = createMap(10000);

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
        agregarItem(mapJugadores);
        break;
      case 4:
        eliminarItem(mapJugadores);
        break;
      case 5:
        asignarPuntos(mapJugadores);
        break;
      case 6:
        itemEspecifico(mapJugadores);
        break;
      case 7:
        deshacerAccion(mapJugadores);
        break;
      case 8:
        exportarDatos(mapJugadores);
        break;
      case 9:
        importarDatos(mapJugadores);
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