#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/graph_coloring.h"

E_i* newListNode(int dest) {
    E_i* newNode = (E_i*)malloc(sizeof(E_i));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

G* createGraph(int n) {
    G* g = (G*)malloc(sizeof(G));
    
    g->n = n;
    g->E_lists = (E_i**)calloc(n, sizeof(E_i*));
    
    return g;
}

void addEdge(G* g, int from, int to) {
    if (g == NULL) return;

    // Ребро из from в to
    E_i* newNodeTo = newListNode(to);
    newNodeTo->next = g->E_lists[from];
    g->E_lists[from] = newNodeTo;

    // Ребро из to в from
    E_i* newNodeFrom = newListNode(from);
    newNodeFrom->next = g->E_lists[to];
    g->E_lists[to] = newNodeFrom;
}

void freeGraph(G* g) {
    if (g == NULL) return;

    for (int i = 0; i < g->n; i++) {
        E_i* current = g->E_lists[i];
        while (current != NULL) {
            E_i* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(g->E_lists);
    free(g);
}

// Проверка, можно ли покрасить вершину v в цвет c
bool isSafe(G* g, int v, int c, int* colors) {
    E_i* current = g->E_lists[v];
    while (current != NULL) { // Проверяем всех соседей вершины v
        int neighbor = current->dest;
        if (colors[neighbor] == c) { // Если у кого-то из соседей есть этот цвет, то нельзя
            return false;
        }
        current = current->next;
    }
    return true;
}

bool graphColoringUtil(G* g, int v, int* colors) {
    if (v == g->n) { // Если перебрали все вершины
        return true;
    }

    for (int c = 1; c <= 5; c++) { // Пробуем 5 цветов
        if (isSafe(g, v, c, colors)) {
            colors[v] = c; // Красим

            if (graphColoringUtil(g, v + 1, colors)) { // Вызываем рекурсию для следующей вершины
                return true;
            }

            colors[v] = 0; // Если раскраска не получилась
        }
    }

    return false; // Все 5 цветов неудачно
}

int* solveColoring(G* g) {
    if (g == NULL || g->n == 0) return NULL;

    int* colors = (int*)calloc(g->n, sizeof(int)); // Цвета для вершин
    
    if (graphColoringUtil(g, 0, colors)) {
        return colors;
    } else {
        free(colors);
        return NULL;
    }
}

void printColoringResult(G* g, int* colors) {
    if (colors == NULL) {
        printf("5 цветов не хватило\n");
        return;
    }

    printf("Результат раскраски:\n");
    const char* colorNames[] = {"Нет", "Красный", "Зеленый", "Синий", "Желтый", "Фиолетовый"};

    for (int i = 0; i < g->n; i++) {
        int c = colors[i];
        printf("Вершина %d: [%d] %-10s | Соседи: ", i, c, (c >= 1 && c <= 5) ? colorNames[c] : "???");
        
        E_i* curr = g->E_lists[i];
        while (curr != NULL) {
            printf("%d(цв.%d) ", curr->dest, colors[curr->dest]);
            curr = curr->next;
        }
        printf("\n");
    }
}