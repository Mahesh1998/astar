#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

#define MAX_NEIGHBOR_NODES 100
#define MAX_NODES 100

/***************Variables***************/
struct astar_node
{
    int x;
    int y;
    char *name;
    int neighbors_count;
    struct astar_node* neighbor[MAX_NEIGHBOR_NODES];
};

struct astar_graph
{
    struct astar_node* nodes[MAX_NODES];
    int count;
};

struct astar_path
{
    struct astar_node* node;
    double distance;
    double heuristic_distance;
    struct astar_path *parent;
};

struct astar_graph graph = {.count = 0 };



/***************Function Declarations***************/
int num_lines_in_file(char *filename);
void read_input(int num_lines, char nodes_file[], char neighbor_file[]);
void check_source_destination_exists(char *source, char *destination, struct astar_node* nodes);
void astar(char *source, char *destination, struct astar_node* nodes);
struct astar_node* get_node(char *name);
void add_graph_node(char *name, int x, int y);
void add_neighbor_node(char *node_name, char *neighbor_name);



/***************Function Definitions***************/
struct astar_node* get_node(char *name)
{
    /*printf("finding %s \n", name);*/
    for (int i = 0; i < graph.count; i++) {
        /*printf("%s %s %d %d\n", graph.nodes[i]->name, name, strcmp(graph.nodes[i]->name, name), graph.nodes[i]->x);*/
        if (strcmp(graph.nodes[i]->name, name) == 0) {
            return graph.nodes[i];
        }
    }
    return NULL;
}

void add_graph_node(char *name, int x, int y)
{
    struct astar_node *node= (struct astar_node*) malloc(sizeof(struct astar_node));

    node->name = (char *) malloc(strlen(name) + 1);

    strcpy(node->name, name);
    node->x = x;
    node->y = y;
    node->neighbors_count = 0;
    for (int i = 0; i < MAX_NEIGHBOR_NODES; i++) {
        node->neighbor[i] = NULL;
    }
    graph.nodes[graph.count++] = node;
}

void add_neighbor_node(char *node_name, char *neighbor_name)
{
    struct astar_node *node= get_node(node_name);

    if (!node) {
        perror("Unable to find node, while adding neighbor");
        exit(1);
    }
    struct astar_node *neighbor = get_node(neighbor_name);

    if (!neighbor) {
        perror("Unable to find neighbor node, while adding neighbor");
        exit(1);
    }

    node->neighbor[node->neighbors_count] = neighbor;
    /*printf("printing neighbor %d %s %s\n", node->neighbors_count, node->name, node->neighbor[node->neighbors_count]->name);*/
    node->neighbors_count++;
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

void read_input(int num_lines, char *nodes_file, char *neighbor_file)
{
    FILE *coordinates = fopen(nodes_file, "r");

    if (coordinates == NULL) {
        perror("Unable to open file!");
        exit(1);
    }

    char line[20];
    int i = 0, index = 0;

    while (fgets(line, sizeof(line), coordinates) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
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

        add_graph_node(node_data[0], atoi(node_data[1]), atoi(node_data[2]));
        index++;

    }
    fclose(coordinates);


    FILE *directions = fopen(neighbor_file, "r");

    while (fgets(line, sizeof(line), directions) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
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

        add_neighbor_node(node_data[0], node_data[1]);
        index++;

    }

    fclose(directions);

    for (index = 0; index < graph.count; index++) {
        printf("%d  %d  %s  %d ",
                graph.nodes[index]->x,
                graph.nodes[index]->y,
                graph.nodes[index]->name,
                graph.nodes[index]->neighbors_count);



        for(int j = 0; j < graph.nodes[index]->neighbors_count; j++){
            printf("%s ", graph.nodes[index]->neighbor[j]->name);
        }
        printf("\n");
    }

}

double euclidean_distance(struct astar_node* a, struct astar_node* b) {
    return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

struct astar_path* create_a_star_node(struct astar_node* node, double distance, double heuristic_distance, struct astar_path* parent) {
    struct astar_path* a_star_node = (struct astar_path *)malloc(sizeof(struct astar_path));
    a_star_node->node = node;
    a_star_node->distance = distance;
    a_star_node->heuristic_distance = heuristic_distance;
    a_star_node->parent = parent;
    return a_star_node;
}

void a_star(struct astar_node* source, struct astar_node* destination) {
    struct astar_path* open_list[MAX_NODES];
    int open_list_count = 0;

    open_list[open_list_count++] = create_a_star_node(source, 0, euclidean_distance(source, destination), NULL);

    printf("Open List\n");

    for(int i = 0; i< open_list_count; i++){
        printf("%d  %d  %s  %d %lf %lf\n",
                open_list[i]->node->x,
                open_list[i]->node->y,
                open_list[i]->node->name,
                open_list[i]->node->neighbors_count,
                open_list[i]->distance,
                open_list[i]->heuristic_distance);
    }

    while (open_list_count > 0) {
        int current_index = 0;

        struct astar_path* current = open_list[current_index];
        if (current->node->name == destination->name) {
            printf("Path found: ");
            while (current) {
                printf("%s ", current->node->name);
                current = current->parent;
            }
            printf("\n");
            return;
        }

        printf("Priority of neighbor nodes of source node\n");

        for (int i = 0; i < current->node->neighbors_count; i++) {
            struct astar_node* neighbor = current->node->neighbor[i];

            double priority = euclidean_distance(current->node, neighbor)+ euclidean_distance(neighbor, destination);
            printf("%lf\n", priority);
        }
        break;

    }

}


int main(int argc, char *argv[])
{
    int num_lines = get_num_lines(argv[1]);
    read_input(num_lines, argv[1], argv[2]);
    char *source = argv[3];
    char *destination = argv[4];
    a_star(get_node(source), get_node(destination));
    return 0;

}
