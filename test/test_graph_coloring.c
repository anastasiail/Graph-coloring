#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/graph_coloring.h"

void runTest(const char* description, G* g) {
    printf("Тест %s\n", description);
    
    int* colors = solveColoring(g);
    
    if (colors != NULL) {
        printColoringResult(g, colors);
        free(colors);
    } else {
        printf("Раскраска не удалась\n");
    }
    
    freeGraph(g);
}

int main() {
    printf("Для пустого графа:\n");
    G* g0 = createGraph(0);
    int* colors0 = solveColoring(g0);
    if (colors0 == NULL) printf("Пустой граф обработан корректно\n");
    else exit(1);
    freeGraph(g0);

    printf("\nДля одной вершины:\n");
    G* g1 = createGraph(1);
    runTest("Одна вершина", g1);

    printf("\nДля двух вершин с ребром:\n");
    G* g2 = createGraph(2);
    addEdge(g2, 0, 1);
    runTest("Две соединенные вершины", g2);

    printf("\nДля K3:\n");
    G* g3 = createGraph(3);
    addEdge(g3, 0, 1);
    addEdge(g3, 1, 2);
    addEdge(g3, 2, 0);
    runTest("Треугольник K3", g3);

    printf("\nДля полного графа K4:\n");
    G* g4 = createGraph(4);
    addEdge(g4, 0, 1); addEdge(g4, 0, 2); addEdge(g4, 0, 3);
    addEdge(g4, 1, 2); addEdge(g4, 1, 3);
    addEdge(g4, 2, 3);
    runTest("Полный граф K4", g4);

    printf("\nДля колеса:\n");
    G* g5 = createGraph(6);
    for(int i = 1; i <= 5; i++) addEdge(g5, 0, i);
    addEdge(g5, 1, 2); addEdge(g5, 2, 3); addEdge(g5, 3, 4);
    addEdge(g5, 4, 5); addEdge(g5, 5, 1);
    runTest("Граф Колесо", g5);

    printf("\nДля K3,3:\n");
    G* g6 = createGraph(6);
    for(int i = 0; i < 3; i++) {
        for(int j = 3; j < 6; j++) {
            addEdge(g6, i, j);
        }
    }
    runTest("Граф K3,3", g6);

    printf("\nДля дерева:\n");
    G* g7 = createGraph(7);
    addEdge(g7, 0, 1); addEdge(g7, 0, 2);
    addEdge(g7, 1, 3); addEdge(g7, 1, 4);
    addEdge(g7, 2, 5); addEdge(g7, 2, 6);
    runTest("Дерево (7 вершин)", g7);

    printf("\nДля несвязного графа:\n");
    G* g9 = createGraph(6);
    addEdge(g9, 0, 1);
    addEdge(g9, 2, 3); addEdge(g9, 3, 4); addEdge(g9, 4, 2);
    runTest("Несвязный граф", g9);
    
    return 0;
}