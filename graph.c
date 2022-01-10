#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "graph.h"

static void add_edge(Edge *edge, Node *node);
static void remove_in_edges(int dest, Graph *gr);

void get_edges(int src, struct Graph *g)
{
   int dest;
    int w;
    while (scanf("%d", &dest)){
        scanf("%d", &w);
        set_edge(src, dest, w, g);
    }
    return;
}

Graph *build_graph(int N){
    Graph* g = (Graph *)malloc(sizeof(Graph));
    if(g==NULL){
        printf("Error allocating memory to graph!\n");
        exit(1);
    }
    g->head = NULL;
    g->N = N;
    return g;
}

void add_edge(Edge *e, Node *n){
    e->next = n->edges_head; 
    e->prev = NULL; 
    if (n->edges_head) n->edges_head->prev = e; 
    n->edges_head = e; 
}

void set_edge(int src, int dest, int w, Graph *g){
     Node* curr = NULL;    
    for (Node* n = g->head; n ; n = n->next){
        if (n->id == src){
            curr = n;
            break;
        }
    }
    Edge* edge = (Edge *)malloc(sizeof(Edge));
    if (edge == NULL){
        printf("Error allocating memory to edge!\n");
        exit(1);
    }
    edge->src = src;
    edge->dest = dest;
    edge->w = w;
    add_edge(edge, curr);
    curr->neig++;
}

Node *get_node(int id, Graph *g){
   Node* curr = g->head;
    while (curr){
        if (curr->id == id){
            return curr;
            break;
        }
        curr = curr->next;
    }
    return NULL;
}

void remove_out_edges(Node *node){
    Edge *edge = node->edges_head;
    while (edge){
        Edge *next = edge->next;
        free(edge);
        edge = next;
        node->neig--;
    }
    node->edges_head = NULL;
    return;
}

void connect(Node *n, Graph *g){
    n->next = g->head;
    n->prev = NULL;
    if (g->head != NULL) g->head->prev = n;
    g->head = n;
    return;
}

Node *add_node(int src, Graph *g){    
    Node* SRC = get_node(src, g);
    if (SRC) remove_out_edges(SRC);
    else{
        SRC = (Node *)malloc(sizeof(Node));
        if(SRC==NULL){
            printf("Error allocting memory to node!\n");
            exit(1);
        }
        SRC->id = src;
        SRC->edges_head = NULL;
        SRC->neig = 0;
        connect(SRC, g);
        g->N++;
    }
    return SRC;
}

void remove_node(Node *n, Graph *g)
{
    if (n->prev) n->prev->next = n->next;
    else g->head = n->next;
    if (n->next) n->next->prev = n->prev;
    free(n);
}

void remove_edge(Edge *e, Node *n){
if (e->prev == NULL)n->edges_head = e->next;
    else e->prev->next = e->next; 
    if (e->next) e->next->prev = e->prev; 
    free(e);
    n->neig--;
}

void remove_in_edges(int dest, Graph* g){
    for (Node* node = g->head; node ; node = node->next){       
        for (Edge* edge = node->edges_head; edge; edge = edge->next){          
            if (edge->dest == dest){
               remove_edge(edge, node);
               break; 
            }
        }
    }
}

void delete_node(int id, Graph *g){
    Node* SRC = get_node(id, g);
    remove_out_edges(SRC);
    remove_in_edges(SRC->id, g);
    remove_node(SRC, g);
    g->N--;
}

int shortestPath(int src,int dest, Graph* g){
    int num=g->N;
    int** mat = (int **)malloc(num * sizeof(int *));
    if(mat==NULL){
        printf("Error allocating memory!\n");
        exit(1);
    }
    for (int i = 0; i < g->N; i++){
        mat[i] = (int *)malloc(num * sizeof(int));
        if(mat[i]==NULL){
        printf("Error allocating memory!\n");
        exit(1);
        }
    }
    for (int i = 0; i < num; i++){
        for (int j = 0; j < num; j++)
        {
            mat[i][j] = INT_MAX;
            if (i == j) mat[i][j] = 0;
        }
    }
    for (Node *node = g->head; node ; node = node->next){
        for (Edge *edge = node->edges_head; edge ; edge = edge->next)
            mat[node->id][edge->dest] = edge->w;
    }
    struct Dijkstra* gr = (struct Dijkstra *)malloc(sizeof(*gr));
    gr->vertexNum = num;
    gr->edges = mat;
    int val = Dijkstra(gr, src, dest);
    for (int i = 0; i < num; i++){
        free(mat[i]);
    }
    free(mat);
    free(gr);
    return val;
}

void swap(int x, int y, int *a){
    int tmp = a[x];
    a[x] = a[y];
    a[y] = tmp;
}

void TSP(int nodes, struct Graph *g){
    int *ptr1, *ptr2;
    int val;
    ptr1 = (int *)malloc(nodes * sizeof(int));
    ptr2 = (int *)malloc(nodes * sizeof(int));
    for (int i = 0; i < nodes; ++i){
        scanf("%d", &val);
        ptr1[i] = val;
        ptr2[i] = 0;
    }
    int j=0;
    int f_ans = INT_MAX;
    int tempSum = 0;
    while(j<nodes-1){
        int tmp = shortestPath(ptr1[j], ptr1[j + 1], g);
        if (tmp == -1)
        {
            tempSum = 0;
            break;
        }
        tempSum = tempSum + tmp;
        j++;
    }
    if (tempSum < f_ans && tempSum != 0) f_ans = tempSum;
    int i = 0;
    int k;
    tempSum = 0;
    while (i < nodes){
        if (ptr2[i] < i){
            if (i % 2 != 0) swap(ptr2[i], i, ptr1);                
            else swap(0, i, ptr1);
            for (int j = 0; j < nodes - 1; j++){
                int tmp = shortestPath(ptr1[j], ptr1[j + 1], g);
                if (tmp == -1){
                    tempSum = 0;
                    break;
                }
                tempSum = tempSum + tmp;
            }
            if (tempSum < f_ans && tempSum != 0) f_ans = tempSum;
            tempSum = 0;
            ptr2[i]++;
            i = 0;
        }
        else ptr2[i++] = 0;
    }
    free(ptr1);
    free(ptr2); 
    if (f_ans == INT_MAX || f_ans == 0){
        printf("TSP shortest path: -1 \n");
        return;
    }   
    printf("TSP shortest path: %d \n", f_ans);    
}

void delete_gr(Graph* g){
    Node* n = g->head;
    Node* next = NULL;
    while (n){
        next = n->next;
        remove_out_edges(n);
        remove_node(n, g);
        n = next;
        g->N--;
    }
    free(g);
}

int minDist(int mdist[], int vset[], int n){
    static int minimum = -1;
    int minv = INT_MAX;
    for (int i = 0; i < n; i++){
        if (vset[i] == 0 && mdist[i] < minv){
            minv = mdist[i];
            minimum = i;
        }
    }
    return minimum;
}

int Dijkstra(struct Dijkstra *g, int src,int dest){
    int V = g->vertexNum;
    int dist[V]; 
    int included[V];   
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        included[i] = 0;
    }
    dist[src] = 0;
    for (int i = 0; i < V - 1; i++){
        int d = minDist(dist, included, V);
        included[d] = 1;
        for (int j = 0; j < V; j++){
            if (!included[j] && g->edges[d][j] != INT_MAX && dist[d] + g->edges[d][j] < dist[j])
            dist[j] = dist[d] + g->edges[d][j];
        }
    }   
    if(dist[dest] != INT_MAX) return dist[dest];
    else return -1;
}