// Implementado por Vinícius Bruch Zuchi e Tiago Heinrich

#include "graph.h"

int main (int argc, char *argv[])
{
    _list_header *list = graph_create();
	list_print(list);
    graph_remove_row(list,0,1);
    list_print(list);
	return 0;
}
