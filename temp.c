#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "min_heap.h"

struct node{
    int x;
    int y;
    char *name[10];
    char *next[100];
};

// char** split_data(char* data, char delimiter){
//     static
//     char* result = malloc();
//     while()
// }

int main(){
    FILE *coordinates = fopen("input/input1/co-ordinates.txt", "r");
    if (coordinates == NULL){
        perror("Unable to open file!");
        exit(1);
    }

    char line[20];
    int i =0;
    int num_lines = 0;

    while(fgets(line, sizeof(line), coordinates) != NULL) {
        num_lines++;
    }
    fclose(coordinates);

    while(fgets(line, sizeof(line), coordinates) != NULL) {
        num_lines++;
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
        printf("\n\n");
     }
     fclose(coordinates);


     struct body bodies[n];

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
