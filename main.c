#include "graph.h"
int main (int argc, char *argv[])
{
    _list_header *graph = graph_create();
    puts("Original graph:\n");
    graph_print(graph);
 /*   puts("\n");
    puts("Floyd-Warshall:\n");
    graph_floydWarshall(graph);*/
    puts("direct transitive closure for the node 0: \n");
    _list_header *direct = graph_direct_transitive_closure(graph, 0);
    path_print(direct);
    puts("indirect transitive closure for the node 0: \n");
    _list_header *indirect = graph_indirect_transitive_closure(graph, 0);
    path_print(indirect);
    return 0;
}
