/*
 * heap.h — Max Heap operations
 * DSA #2: Max Heap (Priority Queue)
 */
#ifndef HEAP_H
#define HEAP_H

#include "player.h"

void    initHeap(MaxHeap *h);
void    swap(Player **a, Player **b);
void    heapify(MaxHeap *h, int i);
void    insertHeap(MaxHeap *h, Player *p);
Player *extractMax(MaxHeap *h);
void    freeHeap(MaxHeap *h);
void    buildHeap(MaxHeap *h);

#endif
