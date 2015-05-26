#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
enum {COST,TIME};
typedef struct{  // All the data used in the functions to manipulate a graph
    int node;
    double weight;
    double time;
    double flow,capacity;
    int visited;
    int predecessor;
}_list_data;

typedef struct __list_member{   // The itens in the list
    _list_data *data;           // Pointer to the allocated info
    struct __list_member *next; // Pointers to the subsequent
    struct __list_member *prev; // edges of a node
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
void graph_print(_list_header*); // Print the items in the graph
void graph_print_with_time(_list_header *);
int graph_add_edge(_list_header*, _list_data*, int); // Add an edge to the vertex labeled by the integer value
int line_counter(FILE*); // returns the number of lines of the entered file, which contains the graph
void print_vector(int*,int); // print a vector at the given number
_list_header *graph_create(void);
_list_header *graph_create_with_time(void);
_list_header *graph_create_with_capacity(void);
int **create_adjacency_matrix(void);
void dfs_header(_list_header*,int); // Wrapper of the "Depth First Search" function, it initializes the visited status of all the vertex with 0 and then start the dfs at the given vertex
void dfs(_list_header*, int, int); // Check the connectivity of the graph, starting at the given vertex
int graph_is_connected (_list_header *); // Returns 1 if the graph is connected, returns 0 otherwise.
_list_data *graph_remove_edge(_list_header*,int,int); // Removes the given edge at the given vertex, returns the removed edge
int graph_degree_counter(_list_header *); // Returns the sum of all degrees of the edges of the graph
int graph_edge_is_a_bridge(_list_header *, int, int); // Returns 1 if the edge is a bridge, returns 0 otherwise
int path_add_edge_sorted(_list_header *, _list_data *);
int path_add_edge_end(_list_header *, _list_data *); // Add a edge to a path
int path_add_edge_beginning(_list_header *, _list_data *); // Add a edge in the beggining of a path
void path_print(_list_header *); // Print the path
void print_edges(_list_header *);
_list_header *graph_has_eulerian_circle(_list_header *); // Wrapper of the Eulerian Circle Function, check if the graph has an eulerian circle using fleury's algorithm, returns the path regardless of the result
void eulerian_circle(_list_header *, _list_header *, int); // Recursive function to create the path of the fleury's algorithm
int graph_is_a_tree(_list_header *); // Returns 1 if the graph is a tree, returns 0 otherwise
void path_create_path (_list_header *, _list_header *, int); // Function to create a path of a connected graph, adding all the edges avaliable. It is used to check if the graph is a tree.
_list_header *graph_tree_centers(_list_header *); // Returns the centers of a tree
int graph_number_of_components (_list_header *); // Returns the number of components.
void tree_print_ancestors(_list_header *, int, int);
void tree_print_descendants(_list_header *, int);
void tree_print_children(_list_header *, int);
void tree_pre_order (_list_header *, _list_header *, int);
void list_purge(_list_header *);// purges the list or the path...
void tree_in_order (_list_header *, _list_header *, int);
void tree_post_order (_list_header *, _list_header *, int);
void graph_reset_visited_status(_list_header *);
int node_counter(_list_header *);
int get_edge_count(_list_header *, int);
int graph_total_edge_count(_list_header *);
int allMarked(int *, int); // returns 1 if all the vertices have been marked, returns 0 otherwise
_list_header *graph_dijkstra (_list_header *, int); // returns the spanning tree for the given graph
void print_double_matrix(double **, int , int );
int graph_bellmanFord (_list_header *, _list_header *, int);
_list_header *graph_floydWarshall(_list_header *);
_list_header *graph_floydWarshall_with_path_reconstrution(_list_header *, int , int , int );
_list_header *graph_direct_transitive_closure(_list_header *, int);
_list_header *graph_indirect_transitive_closure(_list_header *, int);
void graph_has_cycle_recursion(_list_header *, _list_data *,int, int *); // the 'counter' integer is used to set the visited status of the vertices
int graph_has_cycle(_list_header *);
_list_header *graph_PRIM(_list_header *);
_list_header *graph_kruskal(_list_header *);
#endif
