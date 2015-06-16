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
		printf("Please Select an option below:\n 1: Dijkstra\n2:Bellman-Ford\n3:Ford-Fulkerson\n4: Floyd Warshall\n5: Dijsktra for time or cost\n6: Floyd-Warshall for time or cost\n7:Delete Tree");
		scanf("%d",&op);
		switch (op){
			case 1:
				printf("Please Enter the initial vertex:\n"):
				scanf("%d",&src);
				tree = graph_dijkstra(graph,src);
				break;
			case 2:
				printf("Please Enter the initial vertex:\n"):
				scanf("%d",&src);
			    if(!(ret = graph_bellmanFord(graph,tree,src)
					printf("The graph has a negative cycle");
				break;
			case 3:
				printf("Please Enter the source and the sink respectively:\n");
			    scanf("%d%d",&src,&dest);
				maxFlow = graph_ford_fulkerson(graph,src,dest);
				
					
		}	
	}				
    printf("Please enter the source vertex followed by the destination vertex:\n");
    scanf("%d%d",&src,&dest);
    _list_header *pathCost = graph_dijkstra_with_option(graph,src,dest,COST);
    _list_header *pathTime = graph_dijkstra_with_option(graph,src,dest,TIME);
    return 0;
}
