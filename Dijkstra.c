#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 9

void printSolution(int dist[], int n, int found[]) {
    printf("Distance: ");
    for (int i = 0; i < n; i++)
        if (dist[i] == INT_MAX)
            printf("* ");
        else
            printf("%d ", dist[i]);
    printf("\nFound: ");
    for (int i = 0; i < n; i++)
        printf("%d ", found[i]);
    printf("\n\n");
}

void dijkstraMatrix(int graph[V][V], int src) {
    int dist[V];
    int found[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, found[i] = 0;

    dist[src] = 0;
    for (int count = 0; count < V - 1; count++) {
        int u, min = INT_MAX;
        for (int v = 0; v < V; v++)
            if (found[v] == 0 && dist[v] <= min)
                min = dist[v], u = v;

        found[u] = 1;

        for (int v = 0; v < V; v++)
            if (!found[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];

        printSolution(dist, V, found);
    }
}

struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct AdjList* array, int src, int dest, int weight) {
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = array[src].head;
    array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = array[dest].head;
    array[dest].head = newNode;
}

void dijkstra(struct AdjList* array, int src) {
    int dist[V];
    int found[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, found[i] = 0;

    dist[src] = 0;
    for (int count = 0; count < V - 1; count++) {
        int u, min = INT_MAX;
        for (int v = 0; v < V; v++)
            if (found[v] == 0 && dist[v] <= min)
                min = dist[v], u = v;

        found[u] = 1;

        struct AdjListNode* pCrawl = array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            if (!found[v] && dist[u] != INT_MAX && dist[u] + pCrawl->weight < dist[v])
                dist[v] = dist[u] + pCrawl->weight;
            pCrawl = pCrawl->next;
        }

        printSolution(dist, V, found);
    }
}

int main() {
    int graphMatrix[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    struct AdjList array[V];
    for (int i = 0; i < V; i++)
        array[i].head = NULL;

    addEdge(array, 0, 1, 4);
    addEdge(array, 0, 7, 8);
    addEdge(array, 1, 2, 8);
    addEdge(array, 1, 7, 11);
    addEdge(array, 2, 3, 7);
    addEdge(array, 2, 8, 2);
    addEdge(array, 2, 5, 4);
    addEdge(array, 3, 4, 9);
    addEdge(array, 3, 5, 14);
    addEdge(array, 4, 5, 10);
    addEdge(array, 5, 6, 2);
    addEdge(array, 6, 7, 1);
    addEdge(array, 6, 8, 6);
    addEdge(array, 7, 8, 7);

    printf("Dijkstra Algorithm\n");
    dijkstraMatrix(graphMatrix, 0);
    dijkstra(array, 0);

    return 0;
}
