#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_NODES 100
#define INF 1000000

typedef struct Node {
    char name[3];
    int x, y;
    int neighbors_count;
    struct Node* neighbors[MAX_NODES];
} Node;

typedef struct {
    Node* nodes[MAX_NODES];
    int count;
} Graph;

typedef struct {
    Node* node;
    double cost;
    double heuristic;
    struct AStarNode* parent;
} AStarNode;

Graph graph = { .count = 0 };

Node* find_node(char* name) {
    for (int i = 0; i < graph.count; i++) {
        if (strcmp(graph.nodes[i]->name, name) == 0) {
            return graph.nodes[i];
        }
    }
    return NULL;
}

void add_node(char* name, int x, int y) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->name, name);
    node->x = x;
    node->y = y;
    node->neighbors_count = 0;
    graph.nodes[graph.count++] = node;
}

void add_neighbor(char* node_name, char* neighbor_name) {
    Node* node = find_node(node_name);
    Node* neighbor = find_node(neighbor_name);
    if (node && neighbor) {
        node->neighbors[node->neighbors_count++] = neighbor;
    }
}

double heuristic(Node* a, Node* b) {
    return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

AStarNode* create_a_star_node(Node* node, double cost, double heuristic, AStarNode* parent) {
    AStarNode* a_star_node = (AStarNode*)malloc(sizeof(AStarNode));
    a_star_node->node = node;
    a_star_node->cost = cost;
    a_star_node->heuristic = heuristic;
    a_star_node->parent = parent;
    return a_star_node;
}

void a_star(Node* start, Node* goal) {
    AStarNode* open_list[MAX_NODES];
    int open_list_count = 0;
    int closed_list[MAX_NODES] = {0};

    open_list[open_list_count++] = create_a_star_node(start, 0, heuristic(start, goal), NULL);

    while (open_list_count > 0) {
        int current_index = 0;
        for (int i = 1; i < open_list_count; i++) {
            if (open_list[i]->cost + open_list[i]->heuristic < open_list[current_index]->cost + open_list[current_index]->heuristic) {
                current_index = i;
            }
        }

        AStarNode* current = open_list[current_index];
        if (current->node == goal) {
            printf("Path found: ");
            while (current) {
                printf("%s ", current->node->name);
                current = current->parent;
            }
            printf("\n");
            return;
        }

        for (int i = current_index; i < open_list_count - 1; i++) {
            open_list[i] = open_list[i + 1];
        }
        open_list_count--;

        closed_list[find_node(current->node->name) - graph.nodes[0]] = 1;

        for (int i = 0; i < current->node->neighbors_count; i++) {
            Node* neighbor = current->node->neighbors[i];
            if (closed_list[neighbor - graph.nodes[0]]) {
                continue;
            }

            double tentative_cost = current->cost + heuristic(current->node, neighbor);
            int in_open_list = 0;
            for (int j = 0; j < open_list_count; j++) {
                if (open_list[j]->node == neighbor) {
                    in_open_list = 1;
                    if (tentative_cost < open_list[j]->cost) {
                        open_list[j]->cost = tentative_cost;
                        open_list[j]->parent = current;
                    }
                    break;
                }
            }

            if (!in_open_list) {
                open_list[open_list_count++] = create_a_star_node(neighbor, tentative_cost, heuristic(neighbor, goal), current);
            }
        }
    }

    printf("No path found\n");
}

int main() {
    // Add nodes
    add_node("s", 0, 0);
    add_node("a1", 2, 1);
    add_node("a2", 2, 2);
    add_node("a3", 2, 3);
    add_node("b1", 4, 1);
    add_node("b2", 4, 2);
    add_node("b3", 4, 3);
    add_node("b4", 4, 4);
    add_node("c1", 6, 1);
    add_node("d", 8, 2);

    // Add neighbors
    add_neighbor("s", "a1");
    add_neighbor("s", "a2");
    add_neighbor("s", "a3");
    add_neighbor("a1", "b1");
    add_neighbor("a2", "b2");
    add_neighbor("a3", "b3");
    add_neighbor("a3", "b4");
    add_neighbor("b1", "c1");
    add_neighbor("b2", "d");

    // Execute A* algorithm
    Node* start = find_node("s");
    Node* goal = find_node("d");
    if (start && goal) {
        a_star(start, goal);
    } else {
        printf("Start or goal node not found\n");
    }

    return 0;
}
