// Implementado por Vin�cius Bruch Zuchi e Tiago Heinrich

#include "graph.h"

int main (int argc, char *argv[])
{
    _list_header *graph = graph_create();
    puts("Graph:\n");
    list_print(graph);
	return 0;
}
