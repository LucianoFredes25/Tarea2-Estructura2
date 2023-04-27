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
  newJ->mapItems = createMap(1000);

  return newJ;
}

void mostrarItem(Item* item){
  //printf("%s: %d", item->nombre, item->cantidad);
   printf("%s", item->nombre);
}

void imprimirDatosJugador(Jugador* jugador){
  printf("\nPerfil de %s :\n\nPuntos de Habilidad = [%d] \nCantidad de Items = [%d]\n\n", jugador->nombre, jugador->PA , jugador->CantidadItems);
  if(jugador->CantidadItems == 0)
    printf("No hay items asignados.\n");
  else{
    Pair* it = firstMap(jugador->mapItems);
    while(it != NULL){
      mostrarItem(it->value);
      it = nextMap(jugador->mapItems);
      if(it != NULL) printf("\n");
    }
  }
}

HashMap* getMapJ(Jugador* iyo){
  return iyo->mapItems;
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
    imprimirDatosJugador(player->value);
  }
  
}

//Opcion 3 agregar item
void agregarItem(HashMap* mapJugadores, List* listaAcciones, int reverse, char nomAux[50], char itemAux[50])
{

  char key[50];
  if(!reverse){
    printf("Ingrese el nombre del jugador: ");
    scanf("%s", key);
  }else strcpy(key, nomAux);
  
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

  HashMap* mapita = getMapJ(player->value);

  Pair* bPar = searchMap(mapita, keyItem);

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
  char keyItem[50];
  
  printf("Nombre del item: ");
  fgets(blank, 50, stdin);
  fgets(keyItem, 50, stdin);
  keyItem[strcspn(keyItem, "\n")] ='\0';

  Pair* it = firstMap(mapJugadores);

  long cont = 0;

  //La busqueda O(n^2) tiene justificacion :(
  
  while(it!=NULL){
    Pair* it2 = firstMap(((Jugador*)(it->value))->mapItems);
    while(it2!=NULL){

      if( is_equal(  ((Item*)(it2->value))->nombre , keyItem) ){
        cont++;
        printf("-> %s \n", ((Jugador*)(it->value))->nombre );        
        break;
      }
      
      it2 = nextMap(((Jugador*)(it->value))->mapItems);
    }
    it = nextMap(mapJugadores);
  }

  printf("se encontraron %ld jugadores con el item.\n", cont);
  
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
  //char nombreArchivo[50];

  //printf("Ingrese el archivo a exportar: ");
  //scanf("%s, nombreArchivo");

  //FILE* archivo = fopen(nombreArchivo, "w");
  //if (archivo == NULL){}
  //printf("Error al abrir el archivo de exportación \n");
  //return;

  //fprintf(archivo,"Nombre, Puntos de habilidad, #items, Item 1, Item 2, Item 3, Item 4, Item 5, Item 6, Item 7, Item 8");

  //Pair* it = (Pair*) firstMap(mapJugadores);

  //while (it != NULL){}
  //fprintf(archivo,"%c, %d, %d",it->nombre,it->PA,it->CantidadItems);

  //Pair* parDelitem = (Pair*) firstMap(jugador->mapItems);

  //while (parDelitem != NULL){}
  //fprintf(archivo,"");
  //parDelitem = nextMap(jugador->mapItems);

  //fprintf(archivo,"");
  //it = nextMap(mapJugadores);

  //viva 
  
}

//Opcion 9 importar 
//
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
    while (fgets(buffer, 1024, archivo) != NULL) {
        Jugador* jugador = (Jugador*)malloc(sizeof(Jugador));


        char* token = strtok(buffer, ",");
        if (token == NULL) {
            printf("Error al leer la línea del archivo: %s\n", buffer);
            free(jugador);
            continue;
        }
        strcpy(jugador->nombre, token);

        jugador->PA = 0;
        jugador->CantidadItems = 0;
        jugador->mapItems = createMap(1000);

        while ((token = strtok(NULL, ",")) != NULL) {
            if (jugador->PA == 0) {
                jugador->PA = atoi(token);
            } else if (jugador->CantidadItems == 0) {
                jugador->CantidadItems = atoi(token);
            } else {
          
                Pair* itemPair = searchMap(jugador->mapItems, token);
                if (itemPair == NULL) {
                    Item* item = (Item*)malloc(sizeof(Item));
                    strcpy(item->nombre, token);
                    item->cantidad = 1;
                    insertMap(jugador->mapItems, item->nombre, item);
                } else {
                    ((Item*)itemPair->value)->cantidad++;
                }
            }
        }

        if (jugador->PA == 0 || jugador->CantidadItems == 0) {
            printf("Error al leer la línea del archivo: %s\n", buffer);
            free(jugador);
            continue;
        }

        insertMap(mapJugadores, jugador->nombre, jugador);
        numJugadores++;
    }

    fclose(archivo);
    printf("Se importaron %d jugadores desde el archivo %s\n", numJugadores, nombreArchivo);
}

//-------------------------------------------
//                 NO TOCAR
//       ESTA COSA SIGUE MOLESTANDO
//-------------------------------------------

int main() {

  int opcion = 10;
  
  HashMap* mapJugadores = createMap(5000);
  List* listaAcciones = createList();

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
        agregarItem(mapJugadores, listaAcciones, 0, "", "");
        break;
      case 4:
        eliminarItem(mapJugadores, listaAcciones, 0, "", "");
        break;
      case 5:
        asignarPuntos(mapJugadores, listaAcciones, 0, "");
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
      default:
        printf("Opcion Invalida, ingrese nueva opcion\n");
    }
    if(opcion == 10)
      break;
  }

  return 0;
}