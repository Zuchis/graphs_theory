#include "graph.h"
int main (int argc, char *argv[])
{
    _list_header *graph = graph_create_with_time();
    int n = node_counter(graph), w = graph_total_edge_count(graph);
    int src,dest, op, ret;
    char option;
	double maxFlow;
	_list_header *tree = list_create();
    printf("Number of vertices: %d\nNumber of edges: %d\n\n",n,w);
    puts("Original graph:\n");
    graph_print_with_time(graph);
    puts("\n");
    while (1){
		printf("Please Select an option below:\n1: Dijkstra\n2: Bellman-Ford\n3: Ford-Fulkerson\n4: Floyd Warshall\n5: Dijsktra for time or cost\n6: Floyd-Warshall for time or cost\n7: Delete Tree\n8: Print the Current Tree\n9: Fleury Algorithm\n0: Exit\n");
		scanf("%d",&op);
        if (op == 0)
            break;
		switch (op){
			case 1:
				printf("Please Enter the initial vertex:\n");
				scanf("%d",&src);
				tree = graph_dijkstra(graph,src);
				break;
			case 2:
				printf("Please Enter the initial vertex:\n");
				scanf("%d",&src);
			    if(!(ret = graph_bellmanFord(graph,tree,src)))
					printf("The graph has a negative cycle\n");
				break;
			case 3:
				printf("Please Enter the source and the sink respectively:\n");
			    scanf("%d%d",&src,&dest);
				maxFlow = graph_ford_fulkerson(graph,src,dest);
                printf("The maximum flow is %d\n",maxFlow);
                break;
            case 4:
                printf("Please enter the initial vertex:\n");
                scanf("%d",&src);
                graph_floydWarshall(graph);
                break;
            case 5:
                printf("Please enter the initial and destiny vertex:\n");
                scanf("%d%d",&src,&dest);
                printf("Please enter your option (C or T):\n");
                scanf("%c",&option);
                if (option == 'C')
                    tree = graph_floydWarshall_with_path_reconstrution(graph,src,dest,COST);
                else
                    tree = graph_floydWarshall_with_path_reconstrution(graph,src,dest,TIME);
                break;
            case 6:
                printf("Please enter the initial and destiny vertex:\n");
                scanf("%d%d",&src,&dest);
                printf("Please enter your option (C or T):\n");
                scanf("%c",&option);
                if (option == 'C')
                    tree = graph_dijkstra_with_option(graph,src,dest,COST);
                else
                    tree = graph_dijkstra_with_option(graph,src,dest,TIME);
                break;
            case 7:
                if(tree != NULL){
                list_purge(tree);
                free(tree);
                tree = NULL;
                } else
                    printf("The tree is already null\n");
                break;
            case 8:
                graph_print(tree);
                break;
            case 9:
                tree = graph_has_eulerian_circle(graph);
                break;
            default:
                printf("Not a valid option\n");
		}
        puts("\n\n");
	}
    return 0;
}
