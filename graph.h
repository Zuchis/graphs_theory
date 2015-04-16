#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{  // All the data used in the functions to manipulate a graph
    int node;
    int weight;
    int visited;
}_list_data;

typedef struct __list_member{   // The itens in the list
    _list_data *data;           // Pointer to the allocated info
    struct __list_member *next; // Pointers to the subsequent
    struct __list_member *prev; // rows of a node
    struct __list_member *up;   // Pointers to the vertices above
    struct __list_member *down; // and below of the current vertex, respectively
}_list_member;

typedef struct{     // The header of the list
    int size;
    _list_member *first;
}_list_header;

_list_header *list_create();
int list_empty(_list_header*);  // Return 1 if the list is empty
int list_add_begining(_list_header*, _list_data*);  // Add an item on the begining of the list, returns thesize, or zero on failure
void list_add_end(_list_header*,_list_data*); // Add an item on the end of the list and return the size, or zero on failure
int list_size(_list_header*);   // Return the size of the list
void list_print(_list_header*); // Print the items in the list
int graph_add_row(_list_header*, _list_data*, int); // Add a row to the vertex labeled by the integer value
int line_counter(FILE*); // returns the number of lines of the entered file, which contains the graph
void print_vector(int*,int); // print a vector at the given number
_list_header *graph_create(void);
int **create_adjacency_matrix(void);
void dfs_header(_list_header*,int); // Wrapper of the "Depth First Search" function, it initializes the visited status of all the vertex with 0 and then start the dfs at the given vertex
void dfs(_list_header*, int, int); // Check the connectivity of the graph, starting at the given vertex
int graph_is_connected (_list_header *); // Returns 1 if the graph is connected, returns 0 otherwise.
_list_data *graph_remove_row(_list_header*,int,int); // Removes the given row at the given vertex, returns the removed row
int graph_degree_counter(_list_header *); // Returns the sum of all degrees of the rows of the graph
int graph_row_is_a_bridge(_list_header *, int, int); // Returns 1 if the row is a bridge, returns 0 otherwise
int path_add_row_end(_list_header *, _list_data *); // Add a row to a path
int path_add_row_beginning(_list_header *, _list_data *); // Add a row in the beggining of a path
void path_print(_list_header *); // Print the path
_list_header *graph_has_eulerian_circle(_list_header *); // Wrapper of the Eulerian Circle Function, check if the graph has an eulerian circle using fleury's algorithm, returns the path regardless of the result
void eulerian_circle(_list_header *, _list_header *, int); // Recursive function to create the path of the fleury's algorithm
int graph_is_a_tree(_list_header *); // Returns 1 if the graph is a tree, returns 0 otherwise
void path_create_path (_list_header *, _list_header *, int); // Function to create a path of a connected graph, adding all the rows avaliable. It is used to check if the graph is a tree.
_list_header *graph_tree_centers(_list_header *); // Returns the centers of a tree
int graph_number_of_components (_list_header *); // Returns the number of components.
void tree_print_ancestors(_list_header *, int, int);
void tree_print_descendants(_list_header *, int);
void tree_print_children(_list_header *, int);
#endif
