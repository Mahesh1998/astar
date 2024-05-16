#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "min_heap.h"

struct node{
    int x;
    int y;
    char name[10];
    char next[100][100];
};

// char** split_data(char* data, char delimiter){
//     static
//     char* result = malloc();
//     while()
// }

int num_lines_in_file(char* filename){
    FILE *f = fopen(filename, "r");
    if (f == NULL){
        perror("Unable to open file!");
        exit(1);
    }

    char line[20];
    int num_lines = 0;

    while(fgets(line, sizeof(line), f) != NULL) {
        num_lines++;
    }
    fclose(f);
    return num_lines;
}

int main(){
    FILE *coordinates = fopen("input/input1/co-ordinates.txt", "r");
    if (coordinates == NULL){
        perror("Unable to open file!");
        exit(1);
    }

    char line[20];
    int i =0, index = 0;
    int num_lines = num_lines_in_file("input/input1/co-ordinates.txt");

    struct node nodes[num_lines];


    while(fgets(line, sizeof(line), coordinates) != NULL) {
        char *ptr;
        //split_data(line, ",");
        char node_data[10][10];
        ptr =  strtok(line, ",");
        i = 0;
        while(ptr != NULL){
            //node_data[i] = ptr;
            strcpy(node_data[i], ptr);
            //printf("%s (ptr) %s (node_data)\n", ptr, node_data[i]);
            i++;
            ptr = strtok( NULL, ",");
        }

        strcpy(nodes[index].name, node_data[0]);
        nodes[index].x = atoi(node_data[1]);
        nodes[index].y = atoi(node_data[2]);
        int next_index = 0;


        for(int j = 3; j < i; j++){
            strcpy(nodes[index].next[next_index++], node_data[j]);
        }
        index++;


        for(int j = 0; j < i; j++){
            printf("%s ", node_data[j]);
        }
        printf("\n\n");
     }
     fclose(coordinates);

     for (index = 0; index < num_lines; index++){
         printf("%d  %d  %s  ", &nodes[index].x, &nodes[index].y, nodes[index].name);
         int j = 0;
         while(nodes[index].next[j]){
             printf("%s  ", nodes[index].next[j++]);
        }
        printf("\n");
    }



   /*  FILE *directions = fopen("input/input1/directions.txt", "r");

     if(directions == NULL) {
         perror("Unable to open file!");
         exit(1);
    }


    while(fgets(line, sizeof(line), directions) != NULL) {
         char *ptr;
        //split_data(line, ",");
        char node_data[10][10];
        ptr =  strtok(line, ",");
        i = 0;
        while(ptr != NULL){
            //node_data[i] = ptr;
            strcpy(node_data[i], ptr);
            //printf("%s (ptr) %s (node_data)\n", ptr, node_data[i]);
            i++;
            ptr = strtok( NULL, ",");
        }

        for(int j = 0; j < i; j++){
            printf("%s ", node_data[j]);
        }
     }*/



   // fclose(directions);
    return 0;
}
