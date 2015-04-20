#include "graph.h"
int main (int argc, char *argv[])
{
    _list_header *graph = graph_create();
    puts("Original graph:\n");
    graph_print(graph);
    _list_header *spanningTree = dijkstra(graph, graph->first->data->node);
    puts("\n\n");
    puts("Spanning Tree:\n");
    graph_print(spanningTree);
	return 0;
}
