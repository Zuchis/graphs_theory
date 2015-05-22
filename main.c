#include "graph.h"
int main (int argc, char *argv[])
{
    _list_header *graph = graph_create_with_time();
    int n = node_counter(graph), w = graph_total_edge_count(graph);
    printf("Number of vertices: %d\nNumber of edges: %d\n\n",n,w);
    puts("Original graph:\n");
    graph_print_with_time(graph);
    puts("\n");
    _list_header *costPath = graph_floydWarshall_with_path_reconstrution(graph,0,3,COST);
    _list_header *timePath = graph_floydWarshall_with_path_reconstrution(graph,0,3,TIME);
    return 0;
}
