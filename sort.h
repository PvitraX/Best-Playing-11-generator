/*
 * sort.h — Quick Sort operations
 * DSA #3: Quick Sort
 */
#ifndef SORT_H
#define SORT_H

#include "player.h"

int  partition(Player **arr, int lo, int hi);
void quickSort(Player **arr, int lo, int hi);
void showRankings(void);

#endif
