typedef struct Edge{
    int w;
    int src;
    int dest;
    struct Edge *next;
    struct Edge *prev;
} Edge;

typedef struct Node{
    int id;
    int neig;
    struct Node *next;
    struct Node *prev;
    Edge *edges_head;
} Node;

typedef struct Graph {
    int N;
    Node *head;
} Graph;

struct Dijkstra{
    int vertexNum;
    int **edges;
};

int shortestPath(int src,int dest, Graph *g);
int Dijkstra(struct Dijkstra *graph, int src,int dest);
int shortestPathDijkstra(int src,int dest, Graph *g);
void get_edges(int src_A, Graph *g);
Graph *build_graph(int);
void set_edge(int, int, int , Graph *g);
Node *add_node(int, Graph *g);
void delete_node(int, Graph *g);
void printGraph(Graph *g);
void delete_gr(Graph*g);
void TSP(int, Graph *g);