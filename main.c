#include "graph.h"

int main (int argc, char *argv[])
{
    _list_header *graph = graph_create();
    _list_header *preOrder = list_create(), *inOrder = list_create(), *postOrder = list_create();
    puts("Graph:\n");
    graph_print(graph);
    puts("Pre-order:\n");
    tree_pre_order(graph, preOrder, graph->first->data->node);
    path_print(preOrder);
    graph_reset_visited_status(graph);
    puts("Simetric\n");
    tree_in_order(graph, inOrder, graph->first->data->node);
    path_print(inOrder);
    graph_reset_visited_status(graph);
    puts("Post-order\n");
    tree_post_order(graph, postOrder, graph->first->data->node);
    path_print(postOrder);
	return 0;
}
