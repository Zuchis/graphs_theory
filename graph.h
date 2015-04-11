#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int node;
    int weight;
    int visited;
}_list_data;

typedef struct __list_member{   // The itens in the list
    _list_data *data;           // Pointer to the allocated info
    struct __list_member *next;
    struct __list_member *prev;
    struct __list_member *up;
    struct __list_member *down;
}_list_member;

typedef struct{     // The header of the list
    int size;
    _list_member *first;
}_list_header;

_list_header *list_create();
int list_empty(_list_header*);  // Return 1 if the list is empty
int list_add_begining(_list_header*, _list_data*);  // Add an item on the begining of the list, returns thesize, or zero on failure
void list_add_end(_list_header*,_list_data*); // Add an item on the end of the list and return the size, or zero on failure
int list_add(_list_header*,_list_data*,int); // Add an item on a given position and returns the size,or zero on failure
int list_add_sorted(_list_header*,_list_data*); // Add an item in a sorted way. Return zero un failure
int list_size(_list_header*);   // Return the size of the list
void list_print(_list_header*); // Print the itens in the list. Works only for primitive types(float,int,char,etc)
int graph_add_row(_list_header*, _list_data*, int);
int line_counter(FILE*);
void print_vector(int*,int);
_list_header *graph_create(void);
int **create_adjacency_matrix(void);
void dfs_header(_list_header*);
void dfs(_list_header*, int);
int graph_is_connected (_list_header *);
_list_data *graph_remove_row(_list_header*,int,int);
int graph_degree_counter(_list_header *);
int graph_row_is_a_bridge(_list_header *, int, int);
int path_add_row_end(_list_header *, _list_data *);
int path_add_row_beginning(_list_header *, _list_data *);
void path_print(_list_header *);
_list_header *graph_has_eulerian_circle(_list_header *);
void eulerian_circle(_list_header *, _list_header *, int);
#endif
