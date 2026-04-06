/*
 * utils.c — Utility / helper function implementations
 * Contains: string operations, rating formula, print helpers
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

/* Remove trailing newline left by fgets */
void trimNewline(char *s) {
    int len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}

/* Flush leftover chars from stdin after scanf */
void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Case-insensitive string compare — returns 1 if equal */
int strEq(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower(*a) != tolower(*b))
            return 0;
        a++; b++;
    }
    return (*a == '\0' && *b == '\0');
}

/* Check if role is one of the 3 valid roles */
int validRole(const char *r) {
    return strEq(r, "Batsman") || strEq(r, "Bowler") || strEq(r, "All-rounder");
}

/* Map role to index: 0=Batsman, 1=Bowler, 2=All-rounder */
int roleIndex(const char *role) {
    if (strEq(role, "Batsman"))      return 0;
    if (strEq(role, "Bowler"))       return 1;
    if (strEq(role, "All-rounder"))  return 2;
    return -1;
}

/*
 * Rating formula — O(1)
 *   Batsman     -> 70% runs + 8 x wickets
 *   Bowler      -> 20% runs + 15 x wickets
 *   All-rounder -> 50% runs + 10 x wickets
 */
float calcRating(int runs, int wickets, const char *role) {
    if (strEq(role, "Batsman"))
        return runs * 0.70f + wickets * 8.0f;
    if (strEq(role, "Bowler"))
        return runs * 0.20f + wickets * 15.0f;
    return runs * 0.50f + wickets * 10.0f;
}

/* Print table header */
void printHeader(void) {
    printf("\n%-20s %-5s %-15s %-8s %-8s %-8s\n",
           "Name", "Age", "Role", "Runs", "Wkts", "Rating");
    printf("----------------------------------------------------------------------\n");
}

/* Print one player row */
void printPlayer(const Player *p) {
    printf("%-20s %-5d %-15s %-8d %-8d %-8.2f\n",
           p->name, p->age, p->role, p->runs, p->wickets, p->rating);
}
