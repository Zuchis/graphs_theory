#include "graph.h"

_list_header *list_create(){
    _list_header *list=(_list_header*)malloc(sizeof(_list_header));
    if(list!=NULL){
        list->size=0;
        list->first=NULL;
        return list;
    }else{
        return NULL;
    }
}

int list_add_begining(_list_header *list, _list_data *data){
    _list_member *new=(_list_member*)malloc(sizeof(_list_member));
    _list_data *datanew=(_list_data*)malloc(sizeof(_list_data));
    if(new!=NULL && datanew!=NULL){
        memcpy(datanew,data,sizeof(_list_data));
        new->data=datanew;
        new->down=list->first;
        new->prev=NULL;
        new->up=NULL;
        new->next=NULL;
        if(new->down!=NULL)
            new->down->up=new;
        list->first=new;
        list->size++;
        return list->size;
    }
    return 0;
}

int list_add_end(_list_header *list, _list_data *data){
    if(list_empty(list)==1){
        return list_add_begining(list,data);
    }else{
        _list_member *aux=list->first;
        while(aux->down!=NULL){
            aux=aux->down;
        }
        _list_data *datanew=(_list_data*)malloc(sizeof(_list_data));
        _list_member *new=(_list_member*)malloc(sizeof(_list_member));
        if(new!=NULL){
            new->next=NULL;
            new->prev=NULL;
            new->data=datanew;
            memcpy(new->data,data,sizeof(_list_data));
            aux->down=new;
            new->up=aux;
            list->size++;
            return list->size;
        }
    }
    return 0;
}

int list_add_node(_list_header *list, _list_data *data, int pos){
    if ((!list_empty(list)) && (pos < list->size)){
         int i = 0;
        _list_member *new=(_list_member*)malloc(sizeof(_list_member));
        _list_data *datanew=(_list_data*)malloc(sizeof(_list_data));
        _list_member *aux=list->first;
        if(new!=NULL && datanew!=NULL){
            memcpy(datanew,data,sizeof(_list_data));
            new->data=datanew;
            new->up = NULL;
            new->down = NULL;
            while(i != pos){
                aux = aux->down;
                i++;
            }
            while(aux->next !=NULL){
                aux = aux->next;
            }
            aux->next = new;
            new->prev = aux;
            new->next = NULL;
            return 1;
        }
    }
    return 0;
}
_list_header *graph_create()
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
	return list;
}



int list_empty(_list_header *list){
    if(list->size==0)
        return 1;
    else
        return 0;
}

int list_size(_list_header* list){
	_list_member *aux = list->first;
	int i = 0;
	while (aux->down != NULL){
		aux=aux->down;
		i++;
	}
	return i;
}

void list_print(_list_header *list){
    _list_member *aux=list->first;
    _list_member *aux2 = aux;
    while (aux2->down!=NULL){
        printf("%d --> ", aux->data->node);
        while(aux->next!=NULL){
            aux=aux->next;
            printf("%d (%d) --> ",aux->data->node,aux->data->weight);
        }
        puts("//\n");
        aux2=aux2->down;
        aux = aux2;
    }
	 while(aux->next!=NULL){
		       aux=aux->next;
		       printf("%d (%d) --> ",aux->data->node,aux->data->weight);
		   }
	//free(aux);
	//free(aux2);
}

int line_counter (FILE * fp)
{
    char sample_chr;
    int no_lines = 0;
    rewind(fp);
    sample_chr = getc(fp);

    while (sample_chr != EOF)
    {

        if (sample_chr == ':'){
            //sempre que for encontrado o símbolo ':', o número de linhas acrescentará, pois todas as linhas possuem este símbolo
            no_lines++;
        }

        sample_chr = getc(fp);
    }
    rewind(fp);
    return no_lines;
}

void print_vector(int *vec,int n){
    int i;
    for (i = 0; i < n; i++){
        printf("%d",vec[i]);
    }
    puts("\n");
}

void print_matrix(int **matrix, int m, int n)
{
	int i, j;
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			printf("%3d",matrix[i][j]);
		}
		puts("\n");
	}
}

int **create_adjacency_matrix(void)
{
	FILE * entrada = fopen ("entrada.txt", "r");
	char str[500];
	char *str2;
	int i, j, n, u = 0;
	n = line_counter(entrada);
	rewind(entrada);
	int **matrix;

	if ((matrix = (int **)malloc(n*sizeof(int*)))!= NULL){
		for (i = 0; i < n; i++){
			if((matrix[i] = (int*)malloc(n*sizeof(int*))) == NULL){
				printf("falha na alocação\n");
				exit(EXIT_FAILURE);
			}
		}
	} else {
		printf("falha na alocação\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++)
			matrix[i][j] = 0;
	}
	while (!feof(entrada)){
		   fgets(str,500,entrada);
       	   if (strcmp(str,"\n") != 0){ //Esta parte do código pega linha por linha para analisar todas as adjacências do grafo
		       str2 = strtok(str,":"); //Separando o vértice da vez que sempre será o número que vem antes do símbolo ':'
		       i = atoi(str2);
		       while((str2 != NULL)){ // este laço serve para capturar todos os vértices vizinhos do vértice que está sendo analisado
		           str2 = strtok(NULL, " ");
		           if ((strcmp(str2,"\n") != 0) && (strcmp(str2,"\0") != 0) && (strcmp("n",str2) != 0)){
		               j = atoi(str2);
		               matrix[i][j]++; // acrescenta +1 para cada vez que a ligação entre dois vértices for encontrada
		               u++; // a variável 'u' contará o número de arestas
		           }
		       }
		   }
	    }
	rewind(entrada);
	return matrix;
}

void dfs_header(_list_header *list)
{
	_list_member *aux = list->first;
	_list_member *aux2 = aux;
	while (aux != NULL){
		aux->data->visited = 0;      
		aux = aux->down;
	}
	dfs(aux2,aux2->data->node);
}

void dfs(_list_member *aux, int n)
{
	if (aux == NULL){
		printf("NULL Graph);
		return;
	}
	while(aux != NULL && aux->data->node != n){
		aux = aux->down;
	}
	if(aux != NULL && aux->data->visited == 0){
		aux->data->visited = 1;
		if (aux->next != NULL)
			printf("%d --> %d",aux->data->node, aux->next->data->node);
		//PAREI AQUI LOLOLOLOLO SATAN 666
}













