#ifndef GRAPH_COLORING_H
#define GRAPH_COLORING_H

#include <stdbool.h>

// Узел для списка смежности
typedef struct E_i {
    int dest; // Куда ведет ребро (номер вершины)
    struct E_i* next; // Следующий сосед
} E_i;

// Сам граф
typedef struct G {
    int n; // Число вершин
    E_i** E_lists; // Массив указателей на списки соседей
} G;

// Функции для работы с графом
E_i* newListNode(int dest);
G* createGraph(int n);
void addEdge(G* g, int from, int to);
void freeGraph(G* g);

// Функции раскраски
bool isSafe(G* g, int v, int c, int* colors);
bool graphColoringUtil(G* g, int v, int* colors);
int* solveColoring(G* g);
void printColoringResult(G* g, int* colors);

// Функции тестирования
void runTest(const char* description, G* g);

#endif