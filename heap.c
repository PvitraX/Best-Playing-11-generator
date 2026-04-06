/*
 * heap.c — Max Heap implementation
 *
 * DSA #2: MAX HEAP (Priority Queue)
 *   - A complete binary tree stored in an array
 *   - Parent index = (i - 1) / 2
 *   - Left child   = 2*i + 1
 *   - Right child  = 2*i + 2
 *   - Property: parent's rating >= children's rating
 *
 *   insertHeap()  : O(log n) — add at end, bubble UP
 *   extractMax()  : O(log n) — remove root, heapify DOWN
 *   heapify()     : O(log n) — fix one subtree
 *   buildHeap()   : O(n log n) — insert all players from list
 */
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "linkedlist.h"

/* Allocate the initial heap array */
void initHeap(MaxHeap *h) {
    h->cap  = HEAP_INIT_CAP;
    h->size = 0;
    h->arr  = (Player **)malloc(sizeof(Player *) * h->cap);
    if (!h->arr) { printf("Out of memory!\n"); exit(1); }
}

/* Swap two Player pointers */
void swap(Player **a, Player **b) {
    Player *t = *a;
    *a = *b;
    *b = t;
}

/*
 * Heapify DOWN from index i
 * Compares parent with left & right child,
 * swaps with the largest, then recurses.
 */
void heapify(MaxHeap *h, int i) {
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left  < h->size && h->arr[left]->rating  > h->arr[largest]->rating)
        largest = left;
    if (right < h->size && h->arr[right]->rating > h->arr[largest]->rating)
        largest = right;

    if (largest != i) {
        swap(&h->arr[i], &h->arr[largest]);
        heapify(h, largest);     /* recursive call down the tree */
    }
}

/*
 * Insert: place at end, then BUBBLE UP
 * Compare with parent; if bigger, swap and repeat.
 */
void insertHeap(MaxHeap *h, Player *p) {
    /* Double array size if full */
    if (h->size == h->cap) {
        h->cap *= 2;
        h->arr = (Player **)realloc(h->arr, sizeof(Player *) * h->cap);
        if (!h->arr) { printf("Out of memory!\n"); exit(1); }
    }

    h->arr[h->size] = p;
    int cur = h->size;
    h->size++;

    /* Bubble up */
    while (cur > 0) {
        int parent = (cur - 1) / 2;
        if (h->arr[parent]->rating >= h->arr[cur]->rating)
            break;                          /* heap property OK */
        swap(&h->arr[parent], &h->arr[cur]);
        cur = parent;
    }
}

/*
 * Extract the MAX (root) element.
 * Move last element to root, then heapify down.
 */
Player *extractMax(MaxHeap *h) {
    if (h->size == 0) return NULL;

    Player *best = h->arr[0];          /* root = highest rated */
    h->size--;
    if (h->size > 0) {
        h->arr[0] = h->arr[h->size];  /* move last to root */
        heapify(h, 0);                 /* restore heap */
    }
    return best;
}

/* Free heap memory */
void freeHeap(MaxHeap *h) {
    free(h->arr);
    h->arr  = NULL;
    h->size = 0;
    h->cap  = 0;
}

/* Build heap from linked list — traverse list, insert each player */
void buildHeap(MaxHeap *h) {
    for (Node *c = head; c != NULL; c = c->next)
        insertHeap(h, &c->data);
}
