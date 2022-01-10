#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int main(){
    setvbuf(stdout, NULL, _IONBF, 0);
    struct Graph *gr = NULL;
    char c;
    int input_num;
    while (scanf("%c", &c)){
        if (c == '\n')break;
        if (c == 'A'){
            if (gr != NULL){
                delete_gr(gr);
                gr = NULL;
            }
            scanf("%d", &input_num); 
            gr = build_graph(input_num);
        }
        else if (c == 'n') {
            int src_A;
            while (scanf("%d", &src_A)){
                    add_node(src_A, gr);
                    get_edges(src_A, gr); 
            }
        }
        else if (c == 'B'){
            int num_B;
            scanf("%d", &num_B);
            Node *my_src = add_node(num_B, gr);
            get_edges(my_src->id, gr);
        }
        else if (c == 'D'){
            int to_remove;
            scanf("%d", &to_remove);
            delete_node(to_remove, gr);
        }
        else if (c == 'S'){
            int src;
            int dest;
            scanf("%d", &src);
            scanf("%d", &dest);
            int ans = shortestPath(src, dest, gr);
            printf("Dijsktra shortest path: %d \n", ans);
        }
        else if (c == 'T'){
            int k;
            scanf("%d", &k);
            TSP(k, gr);
        }
    }
    delete_gr(gr);
    return 0;
}