#include "graph.h"
int main (int argc, char *argv[])
{
    _list_header *graph = graph_create_with_capacity();
    int n = node_counter(graph), w = graph_total_edge_count(graph);
    printf("Number of vertices: %d\nNumber of edges: %d\n\n",n,w);
    puts("Original graph:\n");
    graph_print_with_capacity(graph);
    puts("\n");
    double flow = bfs_with_augmented_path(graph,0,3);
    //double flow = graph_ford_fulkerson(graph,0,3);
    printf("Max flow = %lf\n",flow);
    return 0;
}
