#include "graph.h"
#define MAX(x,y) (x > y ? x : y)
#define MIN(x,y) (x < y ? x : y)

const int maximum_number = INT_MAX;
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

void list_add_end(_list_header *list, _list_data *data){
    if(list_empty(list)==1){
        list_add_begining(list,data);
    }else{
        _list_member *aux=list->first;
        while(aux->down!=NULL){
            aux=aux->down;
            if (aux->data->node == data->node){
                // puts("Well, looks like our sloppy programmer over here has made a noob mistake,\nthere is a node which has already been inserted!\n");
                return;
            }
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
            return;
        }
    }
    return;
}

int graph_add_edge(_list_header *list, _list_data *data, int pos){
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

int node_counter(_list_header *graph)
{
    _list_member *aux = graph->first;
    int i = 0;
    while(aux != NULL){
        i++;
        aux = aux->down;
    }
    return i;
}

int get_edge_count (_list_header *graph, int node)
{
    _list_member *aux = graph->first;
    while (aux != NULL && aux->data->node != node)
        aux = aux->down;
    if (aux == NULL){
        puts("Non-existent node");
        return 0;
    }
    int i = 0;
    aux = aux->next;
    while(aux != NULL){
        i++;
        aux = aux->next;
    }
    return i;
}

int graph_total_edge_count(_list_header *graph)
{
    _list_member *aux2, *aux = graph->first;
    int i = 0;
    while (aux != NULL){
        aux2 = aux->next;
        while(aux2 != NULL){
            i++;
            aux2 = aux2->next;
        }
        aux = aux->down;
    }
    return i;
}

_list_header *graph_create()
{
    FILE * entrada = fopen ("graph.txt", "r");
    _list_header *list = list_create();
    _list_data aux, aux2;
    while (!feof(entrada)){ // This loop will catch line per line of the file
        fscanf(entrada,"%d",&aux.node); // This separates the vertex from its edges
        aux.weight = 0;
        if (aux.node != -1)
            list_add_end(list,&aux); // Add the caught vertex
        do {
            fscanf(entrada,"%d%lf",&aux2.node,&aux2.weight);
            if (aux2.node != -1){
                graph_add_edge(list,&aux2,aux.node);
            }
        } while (aux2.node != -1);
    }
    fclose(entrada);
    return list;
}

_list_header *graph_create_with_time()
{
    FILE * entrada = fopen ("graph.txt", "r");
    _list_header *list = list_create();
    _list_data aux, aux2;
    while (!feof(entrada)){ // This loop will catch line per line of the file
        fscanf(entrada,"%d",&aux.node); // This separates the vertex from its edges
        aux.weight = 0;
        if (aux.node != -1)
            list_add_end(list,&aux); // Add the caught vertex
        do {
            fscanf(entrada,"%d%lf%lf",&aux2.node,&aux2.weight,&aux2.time);
            if (aux2.node != -1){
                graph_add_edge(list,&aux2,aux.node);
            }
        } while (aux2.node != -1);
    }
    fclose(entrada);
    return list;
}

_list_header *graph_create_with_capacity()
{
    FILE * entrada = fopen ("graph.txt", "r");
    _list_header *list = list_create();
    _list_data aux, aux2;
    while (!feof(entrada)){ // This loop will catch line per line of the file
        fscanf(entrada,"%d",&aux.node); // This separates the vertex from its edges
        aux.weight = 0;
        if (aux.node != -1)
            list_add_end(list,&aux); // Add the caught vertex
        do {
            fscanf(entrada,"%d%lf%lf",&aux2.node,&aux2.weight,&aux2.capacity);
            if (aux2.node != -1){
                aux2.flow = 0.0;
                graph_add_edge(list,&aux2,aux.node);
            }
        } while (aux2.node != -1);
    }
    fclose(entrada);
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

void graph_print(_list_header *list){
    if(list->first != NULL){
        _list_member *aux=list->first;
        _list_member *aux2 = aux;
        while (aux2!=NULL){
            printf("%d --> ", aux->data->node);
            while(aux->next!=NULL){
                aux=aux->next;
                printf("%d (%2.2lf) --> ",aux->data->node,aux->data->weight);
            }
            puts("//\n");
            aux2=aux2->down;
            aux = aux2;
        }
        return;
    }
    puts("Null graph\n");
    return;
}

void graph_print_with_time(_list_header *list)
{
    if(list->first != NULL){
        _list_member *aux=list->first;
        _list_member *aux2 = aux;
        while (aux2!=NULL){
            printf("%d --> ", aux->data->node);
            while(aux->next!=NULL){
                aux=aux->next;
                printf("%d (%2.2lf,%2.2lf) --> ",aux->data->node,aux->data->weight,aux->data->time);
            }
            puts("//\n");
            aux2=aux2->down;
            aux = aux2;
        }
        return;
    }
    puts("Null graph\n");
    return;
}

void graph_print_with_capacity(_list_header *list)
{
    if(list->first != NULL){
        _list_member *aux=list->first;
        _list_member *aux2 = aux;
        while (aux2!=NULL){
            printf("%d --> ", aux->data->node);
            while(aux->next!=NULL){
                aux=aux->next;
                printf("%d (%2.2lf,%2.2lf) --> ",aux->data->node,aux->data->weight,aux->data->capacity);
            }
            puts("//\n");
            aux2=aux2->down;
            aux = aux2;
        }
        return;
    }
    puts("Null graph\n");
    return;
}

int line_counter (FILE * fp)
{
    char sample_chr;
    int no_lines = 0;
    rewind(fp);
    sample_chr = getc(fp); // get the first char of the file
    while (sample_chr != EOF) // Check every single char of the file
    {

        if (sample_chr == ':'){ // It is simpler to use the ':' symbol rather than a \n, because every line of the file has only one ':' symbol
            no_lines++;         // So whenever it is captured by the 'sample_chr' variable, the line counter is increased.
        }

        sample_chr = getc(fp);
    }
    fclose(fp);
    return no_lines; // return the number of lines
}

void print_vector(int *vec,int n){
    int i;
    for (i = 0; i < n; i++){
        printf("%d",vec[i]);
    }
    puts("\n");
}

void print_int_matrix(int **matrix, int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            printf("%3d",matrix[i][j]);
        }
        puts("\n");
    }
}

void print_double_matrix(double **matrix, int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            printf("%3.1lf   ",matrix[i][j]);
        }
        puts("\n");
    }
}
/* ***************************************************************************
 * The logic of the adjacency function is very similar of the adjacency list,*
 * the only changes are how the data is capture with the strtok function, and*
 * the edges are inserted on a matrix, rather on a list
 * ***************************************************************************/
int **create_adjacency_matrix(void)
{
    FILE * entrada = fopen ("graph.txt", "r");
    char *str;
    char *str2;
    int i, j, n, u = 0;
    n = line_counter(entrada);
    rewind(entrada);
    int **matrix;
    int m = n*4 + 1;
    if ((str =(char*)malloc(m*sizeof(char))) == NULL)
        exit(EXIT_FAILURE);
    str[m] = '\0';
    /**********************************************************************************************************************/
    //Allocation of the adjacency matrix, based on the number of lines of the file, in other words, the number of vertices
    if ((matrix = (int **)malloc(n*sizeof(int*)))!= NULL){
        for (i = 0; i < n; i++){
            if((matrix[i] = (int*)malloc(n*sizeof(int*))) == NULL){
                printf("Failure in allocation\n");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        printf("Failure in allocation\n");
        exit(EXIT_FAILURE);
    }
    /**********************************************************************************************************************/
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++)
            matrix[i][j] = 0;
    }
    while (!feof(entrada)){
        fgets(str,m,entrada);
        if (str2 != NULL){
            str2 = strtok(str,":"); // Separation of the vertex from its edges
            i = atoi(str2);
            while((str2 != NULL)){
                str2 = strtok(NULL, " "); // Capture of each of the edges of the current vertex
                if (str2 != NULL){
                    j = atoi(str2);
                    matrix[i][j]++;
                    u++;
                }
            }
        }
    }
    rewind(entrada);
    return matrix;
}

void dfs_header(_list_header *list, int node)
{
    if (list == NULL){
        printf("Null graph");
        return;
    }
    _list_member *aux = list->first;
    _list_member *aux2 = aux;
    while (aux != NULL){ // Set all the visited status to 0
        aux->data->visited = 0;
        aux = aux->down;
    }
    dfs(list,node,1); // Start the dfs iterations at the given node/vertex
    return;
}

void dfs(_list_header *list, int n, int counter) // the 'counter' integer is used to set the visited status of the vertices
{
    _list_member *aux2 = list->first;
    _list_member *aux = NULL;
    while (aux2 != NULL && aux2->data->node != n)
        aux2 = aux2->down;
    if (aux2 == NULL){
        puts("Element not contained in the graph");
        return;
    }
    if (aux2->data->visited == 0){
        aux2->data->visited = counter;
        counter++; // Everytime a non-visited vertex is encountered, the counter is increased, thus,
    }              // the path length to all the vertices, parting from the initial one, will be given.
    else
        return;
    aux = aux2->next;
    while (aux != NULL) {
        // printf("%d --> %d path length: %d\n",aux2->data->node, aux->data->node, aux2->data->visited);
        dfs(list,aux->data->node,counter);
        aux = aux->next;
    }
    return;
}

void graph_has_cycle_recursion(_list_header *graph, _list_data *previousNode,int currentNode, int *flag) // the 'counter' integer is used to set the visited status of the vertices
{
    if (!(*flag)){
        _list_member *aux2, *aux = graph->first;
        while (aux != NULL && aux->data->node != currentNode)
            aux = aux->down;
        if (aux == NULL){
            puts("Element not contained in the graph");
            return;
        }
        if (aux->data->visited == 0){
            aux->data->visited = 1;
            aux->data->predecessor = previousNode->node;
        } else if (aux->data->visited == 1){
            if (currentNode == previousNode->predecessor)
                return;
            else{
                *flag = 1;
                return;
            }
        } else
            return;
        aux2 = aux->next;
        while (aux2 != NULL) {
            // printf("%d --> %d path length: %d\n",aux2->data->node, aux->data->node, aux2->data->visited);
            graph_has_cycle_recursion(graph,aux->data,aux2->data->node,flag);
            aux2 = aux2->next;
        }
        aux->data->visited = 2;
        return;
    }
    return;
}
//Check if the graph has a cycle, returns 1 if it has a cycle, returns 0 otherwise
int graph_has_cycle(_list_header *graph)
{
    int flag = 0;
    _list_member *aux = graph->first;
    while (aux != NULL){
        aux->data->visited = 0;
        aux = aux->down;
    }
    aux = graph->first;
    graph_has_cycle_recursion(graph,aux->data,aux->data->node,&flag);
    while(aux != NULL){
        if (aux->data->visited == 0)
            graph_has_cycle_recursion(graph,aux->data,aux->data->node,&flag);
        aux = aux->down;
    }
    return flag;
}

int graph_is_connected (_list_header *list)
{
    int i = 1;
    int flag = 0;
    _list_member *aux = list->first;
    dfs_header(list,aux->data->node);
    while(aux!= NULL){
        //printf("The current node being analyzed is: %d, and its visited status is: %d\n",aux->data->node,aux->data->visited);
        if (aux->data->visited == 0){ // If there's a vertex which hasn't been visited, this means that the graph is not connected, and we turn the flag on
            flag = 1;
            i++; // Increment the number of components
            dfs(list,aux->data->node,1); // Apply the dfs again on the non-visited vertex, and start check again.
            puts("\n");
        }
        aux = aux->down;
    }
    if (flag){
        printf("The graph is not connected, and it has %d different components\n\n",i);
        return 0;
    }
    //printf("The graph is connected\n");
    return 1;
}

int graph_number_of_components (_list_header *list){ // Similar to the "graph_is_connected" function,
    int i = 1;                                       // the only difference is that the focus of this function is to return the number of components
    _list_member *aux = list->first;
    dfs_header(list,aux->data->node);
    while(aux!= NULL){
        if (aux->data->visited == 0){
            i++;
            dfs(list,aux->data->node,1);
        }
        aux = aux->down;
    }
    return i;
}

_list_data *graph_remove_edge(_list_header *list, int node, int edge) // Removes the given edge at the given node/vertex
{
    _list_member *aux, *aux2;
    _list_data *removededge;
    aux = list->first;
    while(aux != NULL && aux->data->node != node)
        aux = aux->down;
    if (aux == NULL){
        puts("Node is not contained on the list");
        return NULL;
    }
    aux2 = aux->next;
    while (aux2 != NULL && aux2->data->node != edge)
        aux2 = aux2->next;
    if (aux2 == NULL){
        puts("Non-existent edge\n");
        return NULL;
    }
    aux2->prev->next = aux2->next;
    if(aux2->next != NULL)
        aux2->next->prev = aux2->prev;

    removededge = aux2->data;
    free(aux2);
    return removededge;
}

int graph_edge_is_a_bridge(_list_header *list, int node, int edge)
{
    _list_member *aux = list->first;
    _list_data *testededge;
    int n1, n2;
    n1 = graph_number_of_components(list); // Count the number of components with the edge
    testededge = graph_remove_edge(list,node,edge);
    n2 = graph_number_of_components(list); // Count the number of components without the edge
    graph_add_edge(list,testededge,node);
    if (n2 > n1) // If the number of components increased after the edge removal, then the edge is a bridge.
        return 1;
    return 0;
}

int graph_degree_counter(_list_header *list) // very simple function to count the sum of the degrees of all the vertices of the graph
{
    int degreeCounter = 0;
    _list_member *aux2, *aux = list->first;
    while (aux != NULL){
        aux2 = aux->next;
        while(aux2 != NULL){
            degreeCounter++;
            aux2 = aux2->next;
        }
        aux = aux->down;
    }
    return degreeCounter;
}

_list_header *graph_has_eulerian_circle(_list_header *list) // This function is the wrapper, it set the things up for the
{                                                           // iterations of the fleury's algorithm
    if(graph_is_connected(list)){ // First check if the graph is connected
        _list_header *path = list_create();
        _list_member *aux2, *aux = list->first;
        eulerian_circle(list,path,aux->data->node); // Starts the iterations
        aux = path->first; // Get the initial vertex
        aux2 = aux;
        while(aux2->next!=NULL)
            aux2=aux2->next; // go to the end of the path
        if (aux->data->node != aux2->data->node){ // If the last vertex of the path is not the first...
            puts("The graph doesn't contain an eulerian circle\n"); // Then the graph doesn't contain an eulerian circle
            return path;
        }
        puts("The graph contains an eulerian circle\n");
        return path;
    }
    puts("The graph is not connected, therefore it can't have an eulerian circle\n");
    return NULL;
}

void eulerian_circle(_list_header *list, _list_header *path, int edge) // If the graph contains an eulerian circle, this function
{                                                                     // Will successfully create a path starting and ending on
    _list_member *aux2, *aux = list->first;                           // the same vertex and passing through all the edges
    _list_data *removededge;
    while(aux != NULL && aux->data->node != edge)
        aux = aux->down;
    if (aux == NULL){
        puts("node not inserted on the list");
        return;
    }
    path_add_edge_end(path,aux->data); // Add the vertex of destination of the last edge removed.
    aux2 = aux->next;
    while (aux2 != NULL){
        if (aux->next->next == NULL){ // If the edge is the last incident edge of the vertex...
            removededge = graph_remove_edge(list,aux->data->node,aux2->data->node); // it will mandatorily remove it
            graph_remove_edge(list, removededge->node, aux->data->node);
            eulerian_circle(list,path,removededge->node); // go to the next edge
        }
        else if (!graph_edge_is_a_bridge(list,aux->data->node,aux2->data->node)){ // If the edge is not a bridge, it can be removed
            removededge = graph_remove_edge(list,aux->data->node,aux2->data->node);
            graph_remove_edge(list, removededge->node, aux->data->node);
            aux2 = aux->next;
            eulerian_circle(list,path,removededge->node);
        }
        aux2 = aux2->next; // otherwise go to the next one
        if (aux2 == NULL && aux->next != NULL) // just a basic check if the aux2 didn't get lost while roaming through the edges
            aux2 = aux->next;
    }
    return;
}

int path_add_edge_beginning(_list_header *list, _list_data *data)
{
    _list_member *new=(_list_member*)malloc(sizeof(_list_member));
    _list_data *datanew=(_list_data*)malloc(sizeof(_list_data));
    if(new!=NULL && datanew!=NULL){
        memcpy(datanew,data,sizeof(_list_data));
        new->down = NULL;
        new->up = NULL;
        new->data=datanew;
        new->next=list->first;
        new->prev=NULL;
        if(new->next!=NULL)
            new->next->prev=new;
        list->first=new;
        list->size++;
        return list->size;
    }
    return 0;
}

_list_data *path_remove_beginning(_list_header *list)
{
    if(list_empty(list)==1){
        return NULL;
    }else{
        _list_member *t=list->first;
        _list_data *data=t->data;
        list->first=t->next;
        if(t->next!=NULL)
            t->next->prev=NULL;
        list->size--;
        free(t);
        return data;
    }
}

int path_add_edge_end(_list_header *list, _list_data *data)
{
    if(list_empty(list)==1){
        return list_add_begining(list,data);
    }else{
        _list_member *aux=list->first;
        while(aux->next!=NULL)
            aux=aux->next;

        _list_data *datanew=(_list_data*)malloc(sizeof(_list_data));
        _list_member *new=(_list_member*)malloc(sizeof(_list_member));
        if(new!=NULL){
            new->next=NULL;
            new->up = NULL;
            new->down = NULL;
            new->data=datanew;
            memcpy(new->data,data,sizeof(_list_data));
            aux->next=new;
            new->prev=aux;
            list->size++;
            return list->size;
        }
    }
    return 0;
}

int path_add_edge_sorted(_list_header *list, _list_data *data)
{
    if(list_empty(list)==1 || data->weight<=list->first->data->weight){
        return path_add_edge_beginning(list,data);
    }else{
        int i;
        _list_member *aux=list->first;
        while(aux->next!=NULL && aux->next->data->weight < data->weight){
            aux=aux->next;
        }
        _list_data *datanew=(_list_data*)malloc(sizeof(_list_data));
        _list_member *new=(_list_member*)malloc(sizeof(_list_member));
        if(new!=NULL){
            new->next=aux->next;
            new->data=datanew;
            memcpy(datanew,data,sizeof(_list_data));
            aux->next=new;
            new->prev=aux;
            list->size++;
            return list->size;
        }
    }
}

void path_print(_list_header *path) // print the path, very similar to the graph_print one
{
    if (path != NULL){
        _list_member *aux=path->first;
        while(aux!=NULL){
            printf("%d --> ",aux->data->node);
            aux=aux->next;
        }
        puts("//\n");
        return;
    }
    puts("Null path");
    return;
}

void print_edges(_list_header *edges)
{
    if (edges == NULL){
        puts("It's null :(\n ");
        return;
    } else if (edges->first == NULL){
        puts("It's null :(\n ");
        return;
    }
    _list_member *aux = edges->first;
    while (aux != NULL){
        printf("%d -> %d (%lf)\n",aux->data->predecessor,aux->data->node,aux->data->weight);
        aux = aux->next;
    }
    puts("\n");
}

void list_purge(_list_header *list) // purges the list or the path...
{
    if (list != NULL && !list_empty(list)){
        _list_member *aux2, *aux, *aux3 = list->first;
        while (aux3 != NULL){
            aux = aux3;
            aux2 = aux->next;
            aux3 = aux3->down;
            while(aux != NULL){
                free(aux);
                aux = aux2;
                if(aux2 != NULL)
                    aux2 = aux2->next;
            }
        }
        list->first = NULL;
    }
}

int graph_is_a_tree(_list_header *graph)
{
    if (!graph_is_connected(graph)){
        puts("The graph is not connected, therefore it can't be a tree.\n");
        return 0;
    }
    _list_member *aux2, *aux = graph->first;
    _list_header *path = list_create();
    path_create_path(graph, path, aux->data->node); // Check every possible edge and its destination vertex
    aux = path->first;
    while(aux != NULL){ // These two loops compare every single combination of two connections of the graph
        aux2 = path->first;
        while(aux2 != NULL){
            if (aux != aux2 && aux2->data->node == aux->data->node) // If there's two connections which leads to the same vertex, and they're connected, then the graph is not a tree, for it has a cycle.
                return 0;
            aux2= aux2->next;
        }
        aux = aux->next;
    }
    return 1;
}

void path_create_path (_list_header *graph, _list_header *path, int edge) // Almost identical to the eulerian_circle algorithm, the only difference being that this function doesn't
{                                                                        // check if the edges are bridges
    _list_member *aux2, *aux = graph->first;
    _list_data *removededge2, *removededge;
    while(aux != NULL && aux->data->node != edge)
        aux = aux->down;
    if (aux == NULL){
        puts("node not inserted on the list\n");
        return;
    }
    path_add_edge_end(path,aux->data);
    aux2 = aux->next;
    while (aux2 != NULL){
        /* if (aux->next->next == NULL){
           removededge = graph_remove_edge(list,aux->data->node,aux2->data->node);
           graph_remove_edge(list, removededge->node, aux->data->node);
           }*/
        // else if (!graph_edge_is_a_bridge(list,aux->data->node,aux2->data->node)){
        removededge = graph_remove_edge(graph,aux->data->node,aux2->data->node);
        removededge2 =  graph_remove_edge(graph, removededge->node, aux->data->node);
        path_create_path(graph,path,removededge->node);
        aux2 = aux->next;
        // }
        // aux2 = aux2->next;
        // if (aux2 == NULL && aux->next != NULL)
        //   aux2 = aux->next;
    }
    return;
}

_list_header *graph_tree_centers(_list_header *graph)
{
    _list_header *treeCenters = list_create();
    _list_header *graphcpy = graph_create(); // creates a copy of the graph, because the function to check if the graph is a tree destroys the graph.
    int i = 1<<16; // the initial smallest eccentricity
    _list_data treeCenter;
    int eccentricity = 0; // the biggest path of each vertex
    if (graph_is_a_tree(graphcpy)){ // First, check if the graph is a tree...
        _list_member *aux2, *aux = graph->first;
        while(aux != NULL){
            dfs_header(graph, aux->data->node); // Calculate the path length of all the vertices from the initial one, and do this to all the vertices in the graph
            aux2 = graph->first;
            while(aux2 != NULL){
                if (aux2->data->visited >= eccentricity){ // Get the biggest path parting from the current vertex being analyzed
                    eccentricity = aux2->data->visited;
                }
                aux2=aux2->down;
            }
            if (eccentricity < i) // Get the smallest eccentricity from all the vertices
                i = eccentricity;
            aux = aux->down;
            eccentricity = 0; // set the eccentricity to 0 to check the next vertex
        }
        aux = graph->first;
        eccentricity = 0;
        while(aux != NULL){ // now we check each one of the vertices has the smallest eccentricity already calculated
            dfs_header(graph, aux->data->node);
            aux2 = graph->first;
            while(aux2 != NULL){
                if (aux2->data->visited >= eccentricity){
                    treeCenter.visited = aux2->data->visited;
                    treeCenter.node = aux->data->node;
                    // printf("node: %d, e : %d\n",treeCenter.node,treeCenter.visited);
                }
                aux2=aux2->down;
            }
            if (treeCenter.visited == i-1){ // If it has the smallest eccentricity... (it has to be i-1 because the visited status starts with 1, and not 0)
                path_add_edge_end(treeCenters, &treeCenter); // add to the tree centers list
            }
            aux = aux->down;
            eccentricity = 0;
        }
        return treeCenters;

    }
    puts("The graph is not a tree\n");
    return NULL;
}

void tree_print_children(_list_header *graph, int node)
{
    _list_member *aux = graph->first;
    while (aux != NULL && aux->data->node != node)
        aux = aux->down;
    if (aux == NULL){
        puts("Non-existent node\n");
        return;
    }
    printf("Children of %d : \n",aux->data->node);
    aux = aux->next;
    while(aux != NULL){
        printf("%2d ",aux->data->node);
        aux = aux->next;
    }
    puts("\n");
}

void tree_print_descendants(_list_header *graph, int node)
{
    _list_member *aux2, *aux = graph->first;
    while (aux != NULL && aux->data->node != node)
        aux = aux->down;
    if (aux == NULL){
        puts("Non-existent node\n");
        return;
    }
    // printf("Descendants %d : \n",aux->data->node);
    if (aux->data->visited != 1){
        aux->data->visited = 1;
        printf("%2d", aux->data->node);
    } else {
        return;
    }
    aux2 = aux->next;
    while(aux2 != NULL){
        tree_print_descendants(graph, aux2->data->node);
        aux2 = aux2->next;
    }
    return;
}

void tree_print_ancestors(_list_header *graph, int node, int target)
{
    _list_member *aux2, *aux3, *aux = graph->first;
    while (aux != NULL){
        if (aux->data->node != target){
            aux2 = aux->next;
            while (aux2 != NULL){
                if (aux2->data->node == node){
                    if (aux2->data->node == target){
                        printf("%2d", aux->data->node);
                        aux->data->visited = 1;
                        tree_print_ancestors(graph,aux->data->node,target);
                        // break;
                    } else {
                        aux3 = graph->first;
                        while (aux3 != NULL && aux3->data->node != aux2->data->node)
                            aux3 = aux3->down;
                        if(aux3 == NULL)
                            return;
                        if (aux->data->visited != 1){
                            //aux3->data->visited = 1;
                            printf("%2d", aux->data->node);
                            aux->data->visited = 1;
                            tree_print_ancestors(graph,aux->data->node,target);
                            // break;
                        } else {
                            return;
                        }
                    }
                }
                aux2 = aux2->next;
            }
        }
        aux = aux->down;
    }
}

void tree_pre_order (_list_header *graph, _list_header *route, int node)
{
    _list_member *aux2, *aux = graph->first;
    while (aux != NULL && aux->data->node != node)
        aux = aux->down;
    if(aux == NULL){
        puts("Node not found");
        return;
    }
    if (aux->data->visited != 1){
        aux->data->visited = 1;
        path_add_edge_end(route, aux->data);
    } else {
        return;
    }
    aux2 = aux->next;
    while(aux2 != NULL){
        // path_add_edge_end(route, aux2->data);
        tree_pre_order(graph, route, aux2->data->node);
        aux2 = aux2->next;
    }
}

void tree_in_order (_list_header *graph, _list_header *route, int node)
{
    _list_member *aux2, *aux = graph->first;
    while (aux != NULL && aux->data->node != node)
        aux = aux->down;
    if(aux == NULL){
        puts("Node not found");
        return;
    }
    if (aux->data->visited != 1){
        aux->data->visited = 1;
        if (aux->next->next == NULL || aux->next == NULL){
            path_add_edge_end(route, aux->data);
            if (aux != graph->first)
                return;
        }
    } else {
        return;
    }
    int i, n = get_edge_count(graph, aux->data->node);
    aux2 = aux->next;
    if ((n % 2) == 0){
        for (i = 0; i < n/2; i++){
            tree_in_order(graph, route, aux2->data->node);
            aux2 = aux2->next;
        }
        path_add_edge_end(route, aux->data);
        for (i = n/2; i < n; i++){
            tree_in_order(graph, route, aux2->data->node);
            aux2 = aux2->next;
        }
    } else {
        for (i = 0; i < (n/2); i++){
            tree_in_order(graph, route, aux2->data->node);
            aux2 = aux2->next;
        }
        tree_in_order(graph,route, aux2->data->node);
        path_add_edge_end(route, aux->data);
        for (i = (n/2)+1; i < n; i++){
            tree_in_order(graph, route, aux2->data->node);
            aux2 = aux2->next;
        }
    }
}

void tree_post_order (_list_header *graph, _list_header *route, int node)
{
    _list_member *aux2, *aux = graph->first;
    while (aux != NULL && aux->data->node != node)
        aux = aux->down;
    if(aux == NULL){
        puts("Node not found");
        return;
    }
    if (aux->data->visited != 1){
        aux->data->visited = 1;
        if (aux->next->next == NULL){
            path_add_edge_end(route, aux->data);
            return;
        }
    }
    else {
        return;
    }
    aux2 = aux->next;
    while(aux2 != NULL){
        tree_post_order(graph, route, aux2->data->node);
        aux2 = aux2->next;
    }
    path_add_edge_end(route, aux->data);
}

void graph_reset_visited_status(_list_header *graph)
{
    _list_member *aux = graph->first;
    while(aux != NULL){
        aux->data->visited = 0;
        aux = aux->down;
    }
}

int allMarked(int *selected, int n) // returns 1 if all the vertices have been marked, returns 0 otherwise
{
    int i, flag = 1;
    for (i = 0; i < n; i++){
        if (selected[i] == 0){
            flag = 0;
            break;
        }
    }
    return flag;
}

_list_header *graph_dijkstra (_list_header *graph, int node) // returns the spanning tree for the given graph, the variable 'node' is the initial node for the algorithm
{
    _list_header *spanningTree = list_create();
    _list_member *aux2, *aux = graph->first;
    _list_data new;
    // the variable 'n' contains the number of nodes/vertices of the graph.
    int n = node_counter(graph), i, next, smallest, j, veryBigNumber = 1<<16;
    double *est =(double*)malloc(sizeof(double) * n);
    int  *pred =(int*)malloc(sizeof(int) * n), *selected =(int*)malloc(sizeof(int) * n);
    double **weights = (double **)malloc(sizeof(double*) * n);
    for (i = 0; i < n; i++){
        weights[i] = (double*)malloc(sizeof(double) * n);
    }
    if (est == NULL || pred == NULL){
        puts("lewl the allocation failed, try harder scrub\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < n; i++){
        est[i] = veryBigNumber;  // initializing the estimated best path vector, with a very big number (2^16)
        pred[i] = -1;            // initializing the predecessors vector, all with -1
        selected[i] = 0;         // initializing the selected vector, which will be used to mark the vertex that already has the algorithm applied
        for (j = 0; j < n; j++){
            weights[i][j] = -1;  // initializing the matrix which will contain all the weights of the edges of the graph
        }
    }
    est[node] = 0;
    // putting all the weights into a matrix for quicker and easier access
    while (aux != NULL){
        aux2 = aux->next;
        while(aux2 != NULL){
            weights[aux->data->node][aux2->data->node] = aux2->data->weight;
            aux2 = aux2->next;
        }
        aux = aux->down;
    }
    //print_double_matrix(weights,n,n);
    i = node; // start the iterations with the initial node
    while (!allMarked(selected, n)){
        selected[i] = 1; // mark the vertex of the current iteration
        smallest = veryBigNumber; // the variable 'smallest' will determine what is the smallest estimated way,
        for (j = 0; j < n; j++){  // thus providing the next vertex for the next iteration
            if (j != node){
                if (weights[i][j] != -1){  // Here is the relaxing process...
                    if (est[j] > est[i] + weights[i][j]){
                        est[j] =  est[i] + weights[i][j];
                        pred[j] = i;
                    }
                }
            }
        }
        for (j = 0; j < n; j++){ // check the best estimated way for all the vertices that hasn't been marked yet...
            if (est[j] < smallest && selected[j] != 1){ // check if the vertex hasn't been marked, this will guarantee that the algorithm do exactly n = number of vertices iterations
                smallest = est[j];
                next = j;
            }
        }
        i = next;  // ... and send it to the next iteration
    }
    for (i = 0; i < n; i++){ // spanning tree creation
        new.node = i;
        list_add_end(spanningTree, &new);
        for (j = 0; j < n; j++){
            if(pred[j] == i && j != node){
                new.node = j;
                new.weight = est[j] - est[i];
                graph_add_edge(spanningTree, &new, i);
            }
        }
    }
    return spanningTree;
}

int graph_bellmanFord (_list_header *graph, _list_header *spanningTree, int node)
{
    _list_member *aux2, *aux;
    _list_data new;
    int i, u, v, j, w, n = node_counter(graph);
    double *dist =(double*)malloc(sizeof(double) * n);
    int *pred =(int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++){
        dist[i] = 1<<16;
        pred[i] = -1;
    }
    dist[node] = 0;
    for (i = 0; i < n-1; i++){
        aux = graph->first;
        while (aux != NULL){
            u = aux->data->node;
            aux2 = aux->next;
            while(aux2 != NULL){
                v = aux2->data->node;
                w = aux2->data->weight;
                if ((dist[u] + w) < dist[v]){
                    dist[v] = dist[u] + w;
                    pred[v] = u;
                }
                aux2 = aux2->next;
            }
            aux = aux->down;
        }
    }
    aux = graph->first;
    while (aux != NULL){
        u = aux->data->node;
        aux2 = aux->next;
        while(aux2 != NULL){
            v = aux2->data->node;
            w = aux2->data->weight;
            if ((dist[u] + w) < dist[v]){
                puts("The graph has a negative-weight cycle\n");
                return 0;
            }
            aux2 = aux2->next;
        }
        aux = aux->down;
    }
    for (i = 0; i < n; i++){ // spanning tree creation
        new.node = i;
        list_add_end(spanningTree, &new);
        for (j = 0; j < n; j++){
            if(pred[j] == i && j != node){
                new.node = j;
                new.weight = dist[j] - dist[i];
                graph_add_edge(spanningTree, &new, i);
            }
        }
    }
    return 1;
}

_list_header *graph_floydWarshall(_list_header *graph)
{
    int i,j,k, n = node_counter(graph);
    _list_member *aux2, *aux = graph->first;
    double **weights = (double**)malloc(n*sizeof(double*));
    if (weights != NULL){
        for (i = 0; i < n; i++){
            weights[i] = (double*)malloc(n*sizeof(double));
            if (weights[i] == NULL)
                exit(EXIT_FAILURE);
        }
    } else {
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < n ; i++){
        for (j = 0; j < n; j++){
            weights[i][j] = maximum_number;
        }
        weights[i][i] = 0;
    }
    while (aux != NULL){
        aux2 = aux->next;
        while (aux2 != NULL){
            weights[aux->data->node][aux2->data->node] = aux2->data->weight;
            aux2 = aux2->next;
        }
        aux = aux->down;
    }
    for (k = 0; k < n; k++){
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                weights[i][j] = MIN(weights[i][j],weights[i][k]+weights[k][j]);
            }
        }
    }
    print_double_matrix(weights,n,n);
    return NULL;
}

_list_header *graph_floydWarshall_with_path_reconstrution(_list_header *graph, int u, int v, int option)
{
    _list_header *path = list_create();
    int i,j,k, n = node_counter(graph), before, after, ul = u, vl = v ;
    _list_member *aux2, *aux = graph->first;
    _list_data e;
    double **weights = (double**)malloc(n*sizeof(double*));
    int **next = (int**)malloc(n*sizeof(int*));
    if (weights != NULL && next != NULL){
        for (i = 0; i < n; i++){
            weights[i] = (double*)malloc(n*sizeof(double));
            next[i] = (int*)malloc(n*sizeof(int));
            if (weights[i] == NULL || next[i] == NULL)
                exit(EXIT_FAILURE);
        }
    } else {
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < n ; i++){
        for (j = 0; j < n; j++){
            weights[i][j] = maximum_number;
            next[i][j] = -1;
        }
        weights[i][i] = 0;
    }
    while (aux != NULL){
        aux2 = aux->next;
        while (aux2 != NULL){
            if (option == COST)
                weights[aux->data->node][aux2->data->node] = aux2->data->weight;
            else
                weights[aux->data->node][aux2->data->node] = aux2->data->time;
            next[aux->data->node][aux2->data->node] = aux2->data->node;
            aux2 = aux2->next;
        }
        aux = aux->down;
    }
    for (k = 0; k < n; k++){
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                before = weights[i][j];
                weights[i][j] = MIN(weights[i][j],weights[i][k]+weights[k][j]);
                after = weights[i][j];
                if (after != before)
                    next[i][j] = next[i][k];
            }
        }
    }
    switch (option)
    {
        case TIME:
            printf("Smallest route considering time from %d to %d: %lf\n\n",u,v,weights[u][v]);
            break;

        case COST:
            printf("Smallest route considering cost from %d to %d: %lf\n\n",u,v,weights[u][v]);
            break;

        default:
            printf("Chose a valid option scrub\n\n");
            break;
    }

    printf("The route from %d to %d is: \n",u,v);
    if (next[u][v] == -1){
        puts("The graph is not connected ??\n\n");
        return NULL;
    }

    e.node = u;
    path_add_edge_end(path,&e);
    while(ul != vl){
        ul = next[ul][vl];
        e.node = ul;
        path_add_edge_end(path,&e);
    }
    path_print(path);
    return path;
}

_list_header *graph_direct_transitive_closure(_list_header *graph, int node)
{
    _list_header *out = list_create();
    _list_member *aux = graph->first;
    dfs_header(graph, node);
    while(aux != NULL){
        if (aux->data->node != node){
            if(aux->data->visited != 0){
                path_add_edge_end(out, aux->data);
            }
        }
        aux = aux->down;
    }
    return out;
}

_list_header *graph_indirect_transitive_closure(_list_header *graph, int node)
{
    _list_header *out = list_create();
    _list_member *aux2, *aux = graph->first;
    while(aux != NULL){
        if (aux->data->node != node){
            dfs_header(graph,aux->data->node);
            aux2 = graph->first;
            while(aux2 != NULL && aux2->data->node != node)
                aux2 = aux2->down;
            if (aux2->data->visited != 0){
                path_add_edge_end(out, aux->data);
            }
        }
        aux = aux->down;
    }
    return out;
}

_list_header *graph_PRIM(_list_header *graph)
{
    _list_member *aux2, *aux = graph->first;
    _list_header *tree = list_create();
    int j, i, src, u, n = node_counter(graph);
    int *marked =(int*)malloc(n*sizeof(int));
    double **weights =(double**)malloc(n*sizeof(double*));
    if(weights != NULL){
        for(i = 0; i < n; i++){
            if ((weights[i] = (double*)malloc(n*sizeof(double)))== NULL)
                exit(EXIT_FAILURE);
        }
    } else
        exit(EXIT_FAILURE);
    _list_data minimumEdge;
    minimumEdge.weight = maximum_number;
    for(i = 0; i < n; i++){
        marked[i] = 0;
        for(j = 0; j < n; j++)
            weights[i][j] = maximum_number;
    }
    while (aux != NULL){
        list_add_end(tree,aux->data);
        aux2 = aux->next;
        while (aux2 != NULL){
            weights[aux->data->node][aux2->data->node] = aux2->data->weight;
            if (aux2->data->weight < minimumEdge.weight){
                minimumEdge.weight = aux2->data->weight;
                minimumEdge.node = aux2->data->node;
                src = aux->data->node;
            }
            aux2 = aux2->next;
        }
        aux = aux->down;
    }
    weights[src][minimumEdge.node] = maximum_number;
    graph_add_edge(tree,&minimumEdge,src);
    marked[src] = 1;
    marked[minimumEdge.node] = 1;
    for(u = 1; u < n-1;u++){
        minimumEdge.weight = maximum_number;
        for(i = 0; i < n; i++){
            if(marked[i]){
                for(j = 0; j < n; j++){
                    if((weights[i][j] < minimumEdge.weight) && (!marked[j])){
                        minimumEdge.weight = weights[i][j];
                        minimumEdge.node = j;
                        src = i;
                    }
                }
            }
        }
        graph_add_edge(tree,&minimumEdge,src);
        weights[src][minimumEdge.node] = maximum_number;
        if(graph_has_cycle(tree)){
            graph_remove_edge(tree,src,minimumEdge.node);
            u--;
        } else
            marked[minimumEdge.node] = 1;
    }
    return tree;
}

_list_header *graph_kruskal(_list_header *graph)
{
    _list_member *aux2, *aux = graph->first;
    int i, n = node_counter(graph),u;
    _list_header *out = list_create(), *edges = list_create();
    while (aux !=  NULL){
        list_add_end(out,aux->data);
        aux2 = aux->next;
        while(aux2 != NULL){
            aux2->data->predecessor = aux->data->node;
            path_add_edge_sorted(edges,aux2->data);
            aux2 = aux2->next;
        }
        aux = aux->down;
    }
    aux = edges->first;
    for (u = 0; u < n-1; u++){
        if (aux == NULL){
            puts("Reached the end of the edges... Error encountered\n");
            return NULL;
        }
        graph_add_edge(out,aux->data,aux->data->predecessor);
        if(graph_has_cycle(out)){
            graph_remove_edge(out,aux->data->predecessor,aux->data->node);
            u--;
        }
        aux = aux->next;
    }
    return out;
}

int exist_edge(_list_header *graph, int src, int dest)
{
    _list_member *aux2, *aux = graph->first;
    while(aux != NULL && aux->data->node != src)
        aux = aux->down;
    if(aux == NULL){
        puts("Error, node not found.\n");
        return 0;
    }
    aux2 = aux->next;
    while(aux2 != NULL){
        if(aux2->data->node == dest)
            return 1;
        aux2 = aux2->next;
    }
    return 0;
}

void set_visited_zero(_list_header *graph)
{
    _list_member *aux = graph->first;
    while (aux != NULL){
        aux->data->visited = 0;
        aux = aux->down;
    }
}

_list_data *get_edge(_list_header *graph, int src, int dest)
{
    _list_member *aux2, *aux = graph->first;
    _list_data *edge;
    while(aux->data->node != src)
        aux = aux->down;
    aux2 = aux->next;
    while(aux2 != NULL && aux2->data->node != dest)
        aux2 = aux2->next;
    memcpy(edge,aux->data,sizeof(_list_data));
    return edge;
}

_list_member *get_vertex(_list_header *graph, int v)
{
    _list_member *aux = graph->first;
    while(aux != NULL && aux->data->node != v)
        aux = aux->down;
    if (aux == NULL)
        exit(EXIT_FAILURE);
    return aux;
}

double bfs_with_augmented_path(_list_header *graph, int s, int t)
{
    set_visited_zero(graph);
    double minFlow = (double)maximum_number;
    _list_header *queue = list_create();
    _list_member *aux2,*aux;
    _list_data *edge;
    int flag = 0;
    bfs_with_augmented_path_recursion(graph,queue,t,s,s,&flag);
    aux = get_vertex(graph,t);
    if(aux->data->visited == 0)
        return -1;
    while(aux->data->node != s){
        //path_add_edge_end(path,aux->data);
        edge = get_edge(graph,aux->data->predecessor,aux->data->node);
        minFlow = MIN(minFlow,edge->capacity);
        aux = get_vertex(graph,aux->data->predecessor);
    }
    //path_add_edge_end(path,aux->data);
    list_purge(queue);
    free(queue);
    return minFlow;
}

void bfs_with_augmented_path_recursion(_list_header *graph, _list_header *queue, int t, int current, int pred, int *flag)
{
    if (!(*flag)){
        _list_member *aux2, *aux = graph->first;
        _list_data *removed;
        while (aux->data->node != current)
            aux = aux->down;
        if (aux->data->visited != 1){
            aux->data->visited = 1;
            aux->data->predecessor = pred;
            if(aux->data->node == t){
                *flag = 1;
                return;
            }
            aux2 = aux->next;
            while(aux2 != NULL){
                if(aux2->data->capacity > 0){
                    path_add_edge_end(queue,aux2->data);
                    if(aux2->data->node == t)
                        bfs_with_augmented_path_recursion(graph,queue,t,aux2->data->node,aux->data->node,flag);
                }
                aux2 = aux2->next;
            }
        } else {
            return;
        }
        removed = path_remove_beginning(queue);
        if(removed == NULL){
            *flag = 1;
            return;
        }
        if(!(*flag))
            bfs_with_augmented_path_recursion(graph,queue,t,removed->node,aux->data->node,flag);
    }
}

void update_edge_capacity(_list_header *graph, int src, int dest, double flow)
{
    _list_member *aux2, *aux = graph->first;
    while(aux != NULL && aux->data->node != src)
        aux = aux->down;
    if(aux == NULL){
        puts("node not found\n");
        return;
    }
    aux2 = aux->next;
    while(aux2 != NULL && aux2->data->node != dest)
        aux2 = aux2->next;
    if(aux2 == NULL){
        puts("edfe not found\n");
        return;
    }
    aux2->data->capacity -= flow;
}

double graph_ford_fulkerson(_list_header *graph, int s, int t)
{
    int n = node_counter(graph), i, j;
    double minFlow, maxFlow = 0.0;
    _list_member *aux2, *aux = graph->first;
    _list_data newEdge;
    _list_header *gf = list_create(); // residual net
    while (aux != NULL){
        list_add_end(gf,aux->data);
        aux2 = aux->next;
        while(aux2 != NULL){
            aux2->data->predecessor = aux->data->node;
            graph_add_edge(gf,aux2->data,aux->data->node);
            if(!exist_edge(graph,aux2->data->node,aux->data->node)){
                newEdge.node = aux->data->node;
                newEdge.capacity = 0;
                newEdge.weight = aux2->data->weight;
                graph_add_edge(gf,&newEdge,aux2->data->node);
            }
            aux2 = aux2->next;
        }
        aux = aux->down;
    }
    minFlow = bfs_with_augmented_path(gf,s,t);
    while (minFlow != -1){
        aux = get_vertex(gf,t);
        while (aux->data->node != s){
            update_edge_capacity(gf,aux->data->predecessor,aux->data->node,minFlow);
            update_edge_capacity(gf,aux->data->node,aux->data->predecessor,-minFlow);
            aux = get_vertex(gf,aux->data->predecessor);
        }
        maxFlow += minFlow;
        minFlow = bfs_with_augmented_path(gf,s,t);
    }
    return maxFlow;
}
