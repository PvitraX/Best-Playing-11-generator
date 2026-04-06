/*
 * sort.c — Quick Sort implementation + Rankings display
 *
 * DSA #3: QUICK SORT
 *   - Divide-and-Conquer algorithm
 *   - Average Time: O(n log n)
 *   - Worst Case:   O(n^2) — if already sorted
 *   - In-place (no extra array needed)
 *
 *   Steps:
 *     1. Pick the LAST element as pivot
 *     2. Partition: all elements > pivot go LEFT (descending order)
 *     3. Place pivot in its correct position
 *     4. Recursively sort left half and right half
 */
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "heap.h"        /* for swap() */
#include "linkedlist.h"
#include "utils.h"

/*
 * Partition function:
 *   - pivot = last element's rating
 *   - Move all players with rating > pivot to the left side
 *   - Return pivot's final index
 */
int partition(Player **arr, int lo, int hi) {
    float pivot = arr[hi]->rating;
    int i = lo - 1;

    for (int j = lo; j < hi; j++) {
        if (arr[j]->rating > pivot) {   /* descending: bigger goes left */
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[hi]);
    return i + 1;
}

/*
 * Recursive Quick Sort:
 *   - Base case: lo >= hi (0 or 1 element)
 *   - Partition, then sort left & right halves
 */
void quickSort(Player **arr, int lo, int hi) {
    if (lo >= hi) return;

    int pi = partition(arr, lo, hi);
    quickSort(arr, lo, pi - 1);   /* left half */
    quickSort(arr, pi + 1, hi);   /* right half */
}

/*
 * Show player rankings:
 *   1. Copy linked list pointers into an array
 *   2. Quick sort the array by rating (descending)
 *   3. Print ranked table
 */
void showRankings(void) {
    int n = countPlayers();
    if (n == 0) { printf("\nNo players to rank.\n"); return; }

    Player **arr = (Player **)malloc(sizeof(Player *) * n);
    if (!arr) { printf("Out of memory!\n"); return; }

    /* Copy pointers from linked list to array */
    int idx = 0;
    for (Node *c = head; c; c = c->next)
        arr[idx++] = &c->data;

    /* Sort using Quick Sort */
    quickSort(arr, 0, n - 1);

    /* Display */
    printf("\n--- Player Rankings (Best First) ---\n");
    printf("%-5s %-20s %-5s %-15s %-8s %-8s %-8s\n",
           "Rank", "Name", "Age", "Role", "Runs", "Wkts", "Rating");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
        printf("%-5d %-20s %-5d %-15s %-8d %-8d %-8.2f\n",
               i + 1, arr[i]->name, arr[i]->age, arr[i]->role,
               arr[i]->runs, arr[i]->wickets, arr[i]->rating);

    free(arr);
}
