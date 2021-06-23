#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int color;
    int num_connect;
    int *connect;
}dot;

void getEdge( dot *graph, int dinh, int v1, int v2){
    int min, max;
    min = v1 < v2 ? v1 : v2;
    max = v2 > v1 ? v2 : v1;
    int size = graph[ max].num_connect;
    graph[ max].connect[ size++] = min;
    graph[ max].num_connect = size;
}

void coloring( dot *graph, int dinh){
    int i, j, v, size;
    for( i = 0; i < dinh; i++){ //dinh i noi vs v
        size = graph[i].num_connect;
        for( j = 0; j < size; j++){
            v = graph[i].connect[j];
            if( graph[i].color == graph[v].color){
                graph[i].color = graph[i].color + 1;
                j = 0;
            }
        }
    }
}

void RGB( int i, char *s){
    switch ( i)
    {
    case 0:
        strcpy( s, "red");
        break;
    case 1:
        strcpy( s, "green");
        break;
    case 2:
        strcpy( s, "yellow");
        break;
    case 3:
        strcpy( s, "pink");
        break;
    case 4:
        strcpy( s, "orange");
        break;
    case 5:
        strcpy( s, "white");
        break;
    default:
        strcpy( s, "black");
        break;
    }
}

void printf_dot( dot *graph, int dinh){
    FILE *fp;
    int i, j, size;
    char s[10];
    fp = fopen( "dothimau.dot", "w");
    if( fp == NULL){
        printf("Error\n");
        exit(1);
    }

    fprintf( fp, "graph dothi\n{\n");
    for( i = 0; i < dinh; i++){
        RGB( graph[i].color, s);
        fprintf( fp, "\t%d [fillcolor=%s, style=filled];\n", i + 1, s);
    }
    for( i = 1; i < dinh; i++){
        size = graph[i].num_connect;
        for( j = 0; j < size; j++){
            fprintf( fp, "\t%d -- %d\n", i + 1, graph[i].connect[j] + 1);
        }
    }
    fprintf( fp, "}");
}

int main(){
    int dinh, canh;
    dot *graph;
    int i;
    int v1, v2;

    scanf("%d%d", &dinh, &canh);
    graph = (dot*)malloc( dinh*sizeof(dot));

    for( i = 0; i < dinh; i++){
        graph[i].connect = (int*)calloc( i, sizeof(int));
        graph[i].num_connect = 0;
        graph[i].color = 0;
    }
    
    for( i = 0; i < canh; i++){
        scanf("%d%d", &v1, &v2);
        if( v1 == v2 || v1 > dinh || v2 > dinh || v1 < 1 || v2 < 1){
            printf("Nhap loi!\n");
            i--;
        }else{
            getEdge( graph, dinh, v1 - 1, v2 - 1);
        }
    }

    coloring( graph, dinh);

    /*for( i = 0; i < dinh; i++){
        int j;
        int size = graph[i].num_connect;
        printf("Dinh %d: %d\n", i, graph[i].color);
        for( j = 0; j < size; j++){
            printf("%d   ", graph[i].connect[j]);
        }
        printf("\n");
    }*/

    printf_dot( graph, dinh);
}