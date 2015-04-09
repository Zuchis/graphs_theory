// Implementado por Vinícius Bruch Zuchi e Tiago Heinrich

#include "graph.h"

int main (int argc, char *argv[])
{
    _list_header *list = graph_create();
	list_print(list);
    graph_is_connected(list);
	return 0;
}
