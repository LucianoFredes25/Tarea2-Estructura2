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

  Jugador* nuevoJ =(Jugador *) calloc(1, sizeof(Jugador));
  printf("Nombre : ");
  scanf("%s", nuevoJ->nombre);
  nuevoJ->PA = 0;
  nuevoJ->CantidadItems = 0;
  nuevoJ->listaItems = createList();
  return nuevoJ;
  
}

Jugador* buscarJugador(List* listaBusqueda, char nombre[50]){
  Jugador* it = firstList(listaBusqueda);
  
  while(it != NULL){
    if(strcmp(it->nombre, nombre) == 0){
      return it;
    }
    it = nextList(listaBusqueda);
  }
  
  return it;
}

Item* buscarItem(List* listaBusqueda, char nombre[50]){
  Item* it = firstList(listaBusqueda);
  
  while(it != NULL){
    if(strcmp(it->nombre, nombre) == 0){
      return it;
    }
    it = nextList(listaBusqueda);
  }
  
  return it;
}

void imprimirDatosJugador(Jugador* jugador){
  printf("\nPerfil de %s : Puntos de Habilidad = [%d] , Cantidad de Items [%d] ,\n", jugador->nombre, jugador->PA , jugador->CantidadItems);
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

//Opcion 1 - Registrar Jugador
void registrarJugador(List*  listaJugadores){
  pushBack(listaJugadores, obtenerDatosJugador());
  printf("Jugador registrado correctamente!!\n");
}

//Opcion 2 - Mostrar Perfil Jugador

void mostrarPerfilJugador(List* listaJugadores){

  char nombreB[50];
  printf("Ingrese el nombre del jugador: ");
  scanf("%s", nombreB);

  Jugador* jugadorB = buscarJugador(listaJugadores, nombreB);

  
  if(jugadorB == NULL){
    printf("--- NO se encontro al jugador --- \n");
  }else{
    imprimirDatosJugador(jugadorB);
  }
  
}

//Opcion 3 - Agregar item a jugador

void agregarItemJugador(List* listaJugadores, char* nombreB, char* auxI, int es, List* listaAcciones){
  char blank[50], nombreI[50];
  
  Jugador* jugadorB = buscarJugador(listaJugadores, nombreB);

  if(jugadorB == NULL){
    printf("--- NO se encontro al jugador --- \n");
    return;
  }
  char opcion;
  
  if(es){
    Item* nuevoItem = (Item*) calloc(1, sizeof(Item));
    strcpy(nuevoItem->nombre, auxI);
    pushBack(jugadorB->listaItems, nuevoItem);
    jugadorB->CantidadItems++;
    return;
  }
  
  Item* nuevoItem = (Item*) calloc(1, sizeof(Item));
  printf("Nombre del item: ");
  fgets(blank, 50, stdin);
  fgets(nuevoItem->nombre, 50, stdin);
  nuevoItem->nombre[strcspn(nuevoItem->nombre, "\n")] ='\0';
  pushBack(jugadorB->listaItems, nuevoItem);
  jugadorB->CantidadItems++;
  printf("--- Se agrego correctamente el item!!! --- \n");

  Accion* nuevaA = calloc(1, sizeof(Accion));
  nuevaA->tipo = 1;
  nuevaA->PAux = 0;
  strcpy(nuevaA->nombreJ, nombreB);
  strcpy(nuevaA->auxIt, nuevoItem->nombre);
  pushBack(listaAcciones, nuevaA);
}

//Opcion 4 - Eliminar item a jugador

void eliminarItemJugador(List* listaJugadores, Jugador* jugadorB, char* nombreI, List* listaAcciones, int es){
  Item* itemB = buscarItem(jugadorB->listaItems, nombreI);
  if(itemB == NULL){
    printf("--- NO se encontro el item!!! --- \n");
  }else{

    if(!es){
      Accion* nuevaA = calloc(1, sizeof(Accion));
      nuevaA->tipo = 2;
      nuevaA->PAux = 0;
      strcpy(nuevaA->nombreJ, jugadorB->nombre);
      strcpy(nuevaA->auxIt, itemB->nombre);
      pushBack(listaAcciones, nuevaA);
    }
    
    popCurrent( jugadorB->listaItems);
    jugadorB->CantidadItems--;
    if(!es) printf("--- El item fue eliminado correctamente!!! --- \n");
  }
}

//Opcion 5 - Agregar puntos de habilidad
void agregarPuntos(List * listaJugadores , char* nombreB, int auxB, int es, List* listaAcciones){

  Jugador* jugadorB = buscarJugador(listaJugadores, nombreB);
  int puntos;
  if(jugadorB == NULL){
    printf("--- NO se encontro al jugador --- \n");
    return;
  }
  else{
    

    if(es){
      jugadorB->PA = auxB;
      return;
    }
    
    do{
      printf("Ingrese cantidad de puntos a asignar: ");
      scanf("%d", &puntos);
    } while(puntos <= 0);
    jugadorB->PA += puntos;
    printf("Puntos Asignados Correctamente!\n");
  }

  Accion* nuevaA = calloc(1, sizeof(Accion));
  nuevaA->tipo = 3;
  nuevaA->PAux = jugadorB->PA - puntos;
  strcpy(nuevaA->nombreJ, nombreB);

  pushBack(listaAcciones, nuevaA);
  
}

//Opcion 6 - Mostrar jugadores con un itme especifico
//esto sera una busqueda O(n^2) :(

void jugadorConItemS(List* listaJugadores){

  char blank[50], nombreI[50];

  printf("Ingrese el nombre del item: ");
  fgets(blank, 50, stdin);
  fgets(nombreI, 50, stdin);
  nombreI[strcspn(nombreI, "\n")] ='\0';

  Jugador* it = firstList(listaJugadores);

  List* nombreJugadores = createList();
  int contJug = 0;
  Item* itemB;
  
  while(it != NULL){

    itemB = buscarItem(it->listaItems , nombreI);

    if(itemB != NULL){
      pushBack(nombreJugadores, it->nombre);
      contJug++;
    }

    it = nextList(listaJugadores);
  }

  printf("Jugadores encontrados: %d \n", contJug);

  char* itn = firstList(nombreJugadores);

  while(itn !=NULL){
    printf("%s \n", itn);
    itn = nextList(nombreJugadores);
  }
  
  cleanList(nombreJugadores);
  free(nombreJugadores);
  
}
//Opcion 7 Deshacer acciones

void deshacerUltimaAccion(List* listaJugadores, List* listaAcciones){

  // no me lo toque -><-
  Accion* it = lastList(listaAcciones);

  if(it == NULL) return;
  
  if(it->tipo==1){
    Jugador* jugadorB = buscarJugador(listaJugadores, it->nombreJ);
    eliminarItemJugador(listaJugadores, jugadorB, it->auxIt, listaAcciones, 1);
  }else if(it->tipo==2){
    agregarItemJugador(listaJugadores, it->nombreJ, it->auxIt, 1, listaAcciones);
  }else{
    agregarPuntos(listaJugadores , it->nombreJ, it->PAux, 1, listaAcciones);
  }

  printf("--- Accion deshecha correctamente \n---");

  popBack(listaAcciones);
  
}



//Opcion 8 exportar jugadores
//PROBAR EN EL MENU IMPORTANDO EL ARCHIVO players100.csv Y EXPORTARLO A prueba.csv 
// hay un problema y nose que es .-. 

void exportarJugadores(List* listaJugadores){
    char nombreArchivo[50];  
  
    printf("Ingrese el nombre del archivo a exportar: ");
    scanf("%s", nombreArchivo);
    FILE* archivo = fopen(nombreArchivo, "w");

    if(archivo == NULL){
        printf("--- NO se pudo crear el archivo ---\n");
        return;
    }

    fprintf(archivo, "Nombre del jugador,Puntos de habilidad,Cantidad de items,Lista de items\n");

    Jugador* jugador;
    Item* item;
    for(jugador = firstList(listaJugadores); jugador != NULL; jugador = nextList(listaJugadores)){
        fprintf(archivo, "%s,%d,%d", jugador->nombre, jugador->PA, jugador->CantidadItems);
        for(item = firstList(jugador->listaItems); item != NULL; item = nextList(jugador->listaItems)){
            fprintf(archivo, ",%s", item->nombre);
           // prueba fprintf(archivo, ",");
            if(nextList(jugador->listaItems) != NULL){
                fprintf(archivo, "");
            }
        }
        fprintf(archivo, "\n");
    }
    fclose(archivo);
    printf("--- Los datos se han exportado correctamente ---\n");
}


//Opcion 9 Importar jugadores
void importarCSV(List *listaJugadores) {
  
    char nombreArchivo[50];  
    FILE *archivo;
    char linea[1024]; 
  
    printf("Ingrese el nombre del archivo a importar: ");
    scanf("%s", nombreArchivo);
    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
    printf("Error al abrir el archivo.\n");
    return;
    }
  
    while (fgets(linea, 1024, archivo)) {
        Jugador *jugador = (Jugador*)malloc(sizeof(Jugador));
        jugador->listaItems = createList();

        char *nombre = strtok(linea, ",");
        strcpy(jugador->nombre, nombre);

        char *pa = strtok(NULL, ",");
        jugador->PA = atoi(pa);

        char *cantidad_items = strtok(NULL, ",");
        jugador->CantidadItems = atoi(cantidad_items);

        for (int i = 0; i < jugador->CantidadItems; i++) {
            char *nombre_item = strtok(NULL, ",");
            Item *item = (Item*)malloc(sizeof(Item));
            strcpy(item->nombre, nombre_item);

            pushBack(jugador->listaItems, item);
        }
      
        pushBack(listaJugadores, jugador);
    }
    printf("Datos de jugadores cargados correctamente!" );
    fclose(archivo);
}

int main() {

  int opcion = 10, aux;
  char nombreB[30], blank[50], nombreI[50];
  List *listaJugadores = createList();
  List *listaAcciones = createList();
  
  while (true) {

    mostrarMenu();
    
    scanf("%d", &opcion);
    printf("\n");
    
    switch (opcion) {
    case 1:
      registrarJugador(listaJugadores);
      break;
    case 2:
      mostrarPerfilJugador(listaJugadores);
      break;
    case 3:
      printf("Ingrese el nombre del jugador: ");
      scanf("%s", nombreB);
      agregarItemJugador(listaJugadores,  nombreB,blank, 0, listaAcciones);
      break;
    case 4:
      printf("Ingrese el nombre del jugador: ");
      scanf("%s", nombreB);

      Jugador* jugadorB = buscarJugador(listaJugadores, nombreB);

      if(jugadorB == NULL){
        printf("--- NO se encontro al jugador --- \n");
        break;
      }

      printf("Ingrese el nombre del item: ");
      fgets(blank, 50, stdin);
      fgets(nombreI, 50, stdin);
      nombreI[strcspn(nombreI, "\n")] ='\0';
      
      eliminarItemJugador(listaJugadores, jugadorB, nombreI, listaAcciones, 0);
      break;
    case 5:
      printf("Ingrese el nombre del jugador: ");
      scanf("%s", nombreB);
      agregarPuntos(listaJugadores , nombreB, 0, 0, listaAcciones);
      break;
    case 6:
      jugadorConItemS(listaJugadores);
      break;
    case 7:
      deshacerUltimaAccion(listaJugadores, listaAcciones);
      break;
    case 8:
      exportarJugadores(listaJugadores);
      break;
    case 9:
      importarCSV(listaJugadores);
      break;
    case 10:

      break;
    default:
      printf("Opcion Invalida, ingrese nueva opcion\n");
    }
    if (opcion == 10)
      break;
  }

  return 0;
}