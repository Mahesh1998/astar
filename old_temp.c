#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_NEIGHBOR_NODES 100
#define MAX_NODES 100

/***************Variables***************/
struct astar_node
{
    int x;
    int y;
    char *name;
    int neighbor_count;
    astar_node*neighbor[MAX_NEIGHBOR_NODES];
};

struct astar_graph
{
    astar_node*nodes[MAX_NODES];
    int count;
};

struct astar_path
{
    astar_node*node;
    double distance;
    double heuristic_distance;
    astar_path *parent;
};

astar_graph graph = {.count = 0 };



/***************Function Declarations***************/
int num_lines_in_file(char *filename);
void read_input(astar_node* nodes, int num_lines, char nodes_file[],
                char neighbor_file[]);
void check_source_destination_exists(char *source, char *destination,
                                     astar_node* nodes);
void astar(char *source, char *destination, astar_node* nodes);
astar_node*get_node(char *name);
void add_graph_node(char *name, int x, int y);
void add_neighbor_node(char *node_name, char *neighbor_name);



/***************Function Definitions***************/
astar_node*get_node(char *name)
{
    for (int i = 0; i < graph.count; i++) {
        if (strcmp(graph.nodes[i]->name, name) == 0) {
            return graph.nodes[i];
        }
    }
    return NULL;
}

void add_graph_node(char *name, int x, int y)
{
    astar_node*node= (node*) malloc(sizeof(node));

    strcpy(node->name, name);
    node->x = x;
    node->y = y;
    node->neighbors_count = 0;
    graph.nodes[graph.count++] = node;
}

void add_neighbor_node(char *node_name, char *neighbor_name)
{
    astar_node*node= get_node(node_name);

    if (!node) {
        perror("Unable to find node, while adding neighbor");
        exit(1);
    }
    astar_node*neighbor = get_node(neighbor_name);

    if (!neighbor) {
        perror("Unable to find neighbor node, while adding neighbor");
        exit(1);
    }
}


int get_num_lines(char *filename)
{
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    char line[20];
    int num_lines = 0;

    while (fgets(line, sizeof(line), f) != NULL) {
        num_lines++;
    }
    fclose(f);
    return num_lines;
}

void read_input(int num_lines, char nodes_file[], char neighbor_file[])
{
    FILE *coordinates = fopen(nodes_file, "r");

    if (coordinates == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    char line[20];
    int i = 0, index = 0;

    while (fgets(line, sizeof(line), coordinates) != NULL) {
        char *ptr;

        //split_data(line, ",");
        char node_data[10][10];

        ptr = strtok(line, ",");
        i = 0;
        while (ptr != NULL) {
            strcpy(node_data[i], ptr);
            //printf("%s (ptr) %s (node_data)\n", ptr, node_data[i]);
            i++;
            ptr = strtok(NULL, ",");
        }

        add_graph_node(node_data[0], atoi(node_data[1], atoi(node_data[2]);
        /*

            nodes[index].name = malloc(strlen(node_data[0])+1);

            nodes[index].x = atoi(node_data[1]);
            nodes[index].y = atoi(node_data[2]);
            nodes[index].next_length = i-3;
            strcpy(nodes[index].name, node_data[0]);



            int next_index = 0;
            for(int j = 3; j < i; j++){
            strcpy(nodes[index].next[next_index], node_data[j]);
            next_index++;
            }
        */
        index++;}
        fclose(coordinates);
    #if 0
        for (int j = 0; j < i; j++) {
        printf("%s ", node_data[j]);}

        printf("\n\n");}

    #endif

        for (index = 0; index < graph.count;
            index++) {
        printf("%d  %d  %s  %d ",
                graph.nodes[index].x,
                graph.nodes[index].y,
                graph.nodes[index].name,
                graph.nodes[index].
                neighbor_count);
        //  int j = 0;
        //  //printf("\n %d size of next array\n", sizeof(nodes[index].next));
        //  while(j < nodes[index].next_length){
        //      printf("%s  ", nodes[index].next[j++]);
        // }
        // printf("\n");
        }


        }

/*
   void check_source_destination_exists(char *source, char *destination, astar_node*nodes){

   }

   void astar(char *source, char *destination, astar_node*nodes){

   }
 */
int main(int argc, char *argv[])
{
int num_lines =
get_num_lines(argv[1]);
/*Create Array of nodes
astar_node nodes[num_lines];

    printf("%d number of lines\n", num_lines);
    printf("%d size of structure\n", sizeof(nodes));
*/
read_input(nodes, num_lines,
            argv[1], argv[2]);
char *source = argv[2];
char *destination = argv[3];
check_source_destination_exists
(source, destination, nodes);
astar(source, destination, nodes);
return 0;}
