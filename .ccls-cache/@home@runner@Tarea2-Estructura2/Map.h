#ifndef MAP_H
#define MAP_H

typedef struct Map Map;

Map * createMapa(int (*is_equal)(void* key1, void* key2));

void insertMapa(Map * map, void * key, void * value);

void * eraseMapa(Map * map, void * key);

void * searchMapa(Map * map, void * key);

void * firstMapa(Map * map);

void * nextMapa(Map * map);

void setSortFunction(Map* map, int (*lower_than)(void* key1, void* key2));

#endif /* MAP_h */
