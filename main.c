#include "graph.h"
int main (int argc, char *argv[])
{
    _list_header *graph = graph_create();
    puts("Original graph:\n");
    graph_print(graph);
    _list_header *spanningTree = list_create();
    if (graph_bellmanFord(graph, spanningTree, graph->first->data->node)){
     puts("\n\n");
     puts("Spanning Tree:\n");
     graph_print(spanningTree);
    }
	return 0;
}
