#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Graph{
    int vertices;
    char* vertex_names;
    int** graph;
    int** d_table;
};


struct Graph* init_graph(int n)
{
    struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph));
    g->vertices = n;
    char* vertex_names = malloc(n * sizeof(char));
    for(int i = 0 ;i < n; i++)
    {
        vertex_names[i] = 65 + i;
    }
    g->vertex_names = vertex_names;
    return g;
}

struct Graph* init_mat(struct Graph* g)
{
    int mat[5][5] = {
        {0,5,0,10,0},
        {5,0,2,0,5},
        {0,2,0,2,2},
        {10,0,2,0,0},
        {0,5,2,0,0},
    };

    int** temp = malloc(g->vertices * sizeof(int*));
    for(int i = 0 ;i < g->vertices; i++)
    {
        temp[i] = malloc(g->vertices * sizeof(int));
    }
    for(int i = 0 ; i < g->vertices; i++)
        for(int j = 0 ;j < g->vertices; j++)
            temp[i][j] = mat[i][j];

    g->graph = temp;
    return g;
}
int char_to_int(char ch)
{
    return ch - 65;
}

int not_total_visited(int a, int b)
{
    if(a == b)
        return 0;
    else
        return 1;
}
void init_shortest_path(struct Graph* g)
{
    int shortest_distance[g->vertices];
    int inf = INT_MAX;
    for(int i = 0 ;i < g->vertices; i++)
        shortest_distance[i] = inf;

    char previous_node[g->vertices];

    int visited[g->vertices];
    for(int i = 0 ;i < g->vertices; i++)
        visited[i] = 0;

    int start_point = char_to_int('A');
    shortest_distance[start_point] = 0;
    previous_node[start_point] = '/';
    int total_visited = 0;
    while(total_visited <  g->vertices)
    {
        int sd,sv;

        for(int i = 0 ;i < g->vertices; i++)
        {
            if(g->graph[start_point][i] != 0)
            {
                if(shortest_distance[start_point] + g->graph[start_point][i] <= shortest_distance[i]){
                    shortest_distance[i] = shortest_distance[start_point] + g->graph[start_point][i];
                    previous_node[i] = 65 + start_point;
                }

            }
        }
        visited[start_point] = 1;
        total_visited++;

        sd = INT_MAX;
        sv = -1;
        for(int i = 0; i < g->vertices; i++)
        {
            if(shortest_distance[i] < sd && visited[i] == 0)
            {
                sd = shortest_distance[i];
                sv = i;
            }
        }
        if(sv == -1)
            break;
        start_point = sv;

    }
    for(int i = 0; i < g->vertices; i++)
    {
        printf("%c %d %c", g->vertex_names[i], shortest_distance[i], previous_node[i]);
        printf("\n");
    }
}

int main()
{
    struct Graph* g = init_graph(5);
    g = init_mat(g);
    init_shortest_path(g);
}
