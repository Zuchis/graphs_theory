// Implementado por Vinícius Bruch Zuchi e Tiago Heinrich

#include "graph.h"

int main (int argc, char *argv[])
{
    _list_header *graph = graph_create();
    _list_header *path = list_create();
    puts("Graph:\n");
    list_print(graph);
    path = graph_has_eulerian_circle(graph);
    path_print(path);
	return 0;
}
