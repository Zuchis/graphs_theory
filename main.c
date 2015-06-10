#include "graph.h"
int main (int argc, char *argv[])
{
    _list_header *graph = graph_create_with_time();
    int n = node_counter(graph), w = graph_total_edge_count(graph);
    int src,dest;
    printf("Number of vertices: %d\nNumber of edges: %d\n\n",n,w);
    puts("Original graph:\n");
    graph_print_with_time(graph);
    puts("\n");
    printf("Please enter the source vertex followed by the destination vertex:\n");
    scanf("%d%d",&src,&dest);
    _list_header *pathCost = graph_dijkstra_with_option(graph,src,dest,COST);
    _list_header *pathTime = graph_dijkstra_with_option(graph,src,dest,TIME);
    return 0;
}
