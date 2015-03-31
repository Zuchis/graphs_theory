// Implementado por Vinícius Bruch Zuchi e Tiago Heinrich

#include "graph.h"

int main (int argc, char *argv[])
{
    FILE * entrada = fopen ("entrada.txt", "r");
    char str[500];
    char *str2;
    _list_header *list = list_create();
    _list_data aux;
    int u, no_nodes, i, degree_counter = 0;
    u = 0;
    i = 0;
	int **matrix;
    no_nodes = line_counter(entrada);
        while (!feof(entrada)){
        if (fgets(str,500,entrada) != "\n"){ //Esta parte do código pega linha por linha para analisar todas as adjacências do grafo
            str2 = strtok(str,":"); //Separando o vértice da vez que sempre será o número que vem antes do símbolo ':'
            aux.node = atoi(str2);
            aux.weight = 0;
            list_add_end(list,&aux);
            while((str2 != NULL)){ // este laço serve para capturar todos os vértices vizinhos do vértice que está sendo analisado
                str2 = strtok(NULL, "-");
                //puts(str2);
                //puts("\n");
                if ((str2 != '\n') && (str2 != '\0')){
                    aux.node = atoi(str2);
                }
                    //printf("No %d\n",aux.node);
                str2 = strtok(NULL, " ");
                //puts(str2);
                //puts("\n");
                if ((str2 != '\n') && (str2 != '\0')){
                    aux.weight = atoi(str2);
                    degree_counter++;
                    list_add_node(list,&aux,u);
                }
            }
            degree_counter = 0;
            u++;
        }
    }
/*    printf("Adjacency List: \n\n");*/
/*    list_print(list);*/
/*	matrix = create_adjacency_matrix();*/
/*	puts("Adjacency Matrix\n");*/
/*	print_matrix(matrix,no_nodes,no_nodes);*/
	dfs_header();
	
    return 0;
}
