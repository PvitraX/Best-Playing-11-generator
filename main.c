/*
 * main.c — Smart Squad Selection System
 *
 * This is the ENTRY POINT of the program.
 * It handles: Menu, File I/O, Add/Search/Filter, and Playing XI.
 *
 * DSA used in this project:
 *   1. Linked List (linkedlist.c) — stores all players
 *   2. Max Heap    (heap.c)       — picks best players for XI
 *   3. Quick Sort  (sort.c)       — ranks players by rating
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "utils.h"
#include "linkedlist.h"
#include "heap.h"
#include "sort.h"

/* ============================================================
 *                      FILE HANDLING
 * ============================================================ */

/* Save entire linked list to players.txt — O(n) */
void saveToFile(void) {
    FILE *f = fopen(FILE_NAME, "w");
    if (!f) { printf("Cannot open file.\n"); return; }

    for (Node *c = head; c; c = c->next)
        fprintf(f, "%s|%d|%s|%d|%d|%.2f\n",
                c->data.name, c->data.age, c->data.role,
                c->data.runs, c->data.wickets, c->data.rating);
    fclose(f);
}

/* Load players from players.txt into linked list — O(n) */
void loadFromFile(void) {
    FILE *f = fopen(FILE_NAME, "r");
    char line[256];
    if (!f) return;

    while (fgets(line, sizeof(line), f)) {
        Player p;
        trimNewline(line);
        if (strlen(line) == 0) continue;

        if (sscanf(line, "%49[^|]|%d|%19[^|]|%d|%d|%f",
                   p.name, &p.age, p.role, &p.runs, &p.wickets, &p.rating) == 6) {
            if (validRole(p.role))
                insertNode(p);
        }
    }
    fclose(f);
}

/* ============================================================
 *                    MENU FEATURES
 * ============================================================ */

/* Add a new player interactively */
void addPlayer(void) {
    Player p;

    printf("\nEnter name: ");
    fgets(p.name, NAME_LEN, stdin);
    trimNewline(p.name);
    if (strlen(p.name) == 0) { printf("Name cannot be empty.\n"); return; }

    printf("Enter age: ");
    if (scanf("%d", &p.age) != 1 || p.age <= 0) {
        printf("Invalid age.\n"); clearInput(); return;
    }
    clearInput();

    printf("Enter role (Batsman / Bowler / All-rounder): ");
    fgets(p.role, ROLE_LEN, stdin);
    trimNewline(p.role);
    if (!validRole(p.role)) { printf("Invalid role.\n"); return; }

    printf("Enter runs: ");
    if (scanf("%d", &p.runs) != 1 || p.runs < 0) {
        printf("Invalid runs.\n"); clearInput(); return;
    }
    printf("Enter wickets: ");
    if (scanf("%d", &p.wickets) != 1 || p.wickets < 0) {
        printf("Invalid wickets.\n"); clearInput(); return;
    }
    clearInput();

    p.rating = calcRating(p.runs, p.wickets, p.role);
    insertNode(p);
    saveToFile();
    printf("Player added!\n");
}

/* Search by name — linear search O(n) */
void searchPlayer(void) {
    char name[NAME_LEN];
    printf("\nEnter player name: ");
    fgets(name, NAME_LEN, stdin);
    trimNewline(name);

    for (Node *c = head; c; c = c->next) {
        if (strEq(c->data.name, name)) {
            printf("\nPlayer found:\n");
            printHeader();
            printPlayer(&c->data);
            return;
        }
    }
    printf("Player '%s' not found.\n", name);
}

/* Filter players by role — O(n) */
void filterByRole(void) {
    char role[ROLE_LEN];
    int found = 0;

    printf("\nEnter role (Batsman / Bowler / All-rounder): ");
    fgets(role, ROLE_LEN, stdin);
    trimNewline(role);
    if (!validRole(role)) { printf("Invalid role.\n"); return; }

    for (Node *c = head; c; c = c->next) {
        if (strEq(c->data.role, role)) {
            if (!found) printHeader();
            printPlayer(&c->data);
            found = 1;
        }
    }
    if (!found) printf("No players with role '%s'.\n", role);
}

/* ============================================================
 *         GENERATE PLAYING XI (uses Heap + Array)
 * ============================================================
 *  1. Build max heap from all players    — O(n log n)
 *  2. Extract best player from heap      — O(log n) each
 *  3. Check if role slot is available
 *  4. Add to Playing XI array
 *  5. Repeat until XI is full or heap empty
 */

PitchReq getPitch(int ch) {
    PitchReq r = {"", 0, 0, 0};
    if (ch == 1) { strcpy(r.pitchName, "Batting Pitch");  r.batsmen=6; r.bowlers=3; r.allRounders=2; }
    if (ch == 2) { strcpy(r.pitchName, "Bowling Pitch");  r.batsmen=4; r.bowlers=5; r.allRounders=2; }
    if (ch == 3) { strcpy(r.pitchName, "Balanced Pitch"); r.batsmen=5; r.bowlers=4; r.allRounders=2; }
    return r;
}

void generateXI(void) {
    if (!head) { printf("\nNo players available.\n"); return; }

    printf("\nSelect pitch:\n");
    printf("  1. Batting Pitch\n  2. Bowling Pitch\n  3. Balanced Pitch\n");
    printf("Choice: ");

    int ch;
    if (scanf("%d", &ch) != 1) { printf("Invalid.\n"); clearInput(); return; }
    clearInput();

    PitchReq req = getPitch(ch);
    if (req.batsmen == 0) { printf("Invalid pitch.\n"); return; }

    int limits[3] = { req.batsmen, req.bowlers, req.allRounders };
    int picked[3] = { 0, 0, 0 };
    Player *xi[PLAYING_XI];
    int total = 0;

    MaxHeap heap;
    initHeap(&heap);
    buildHeap(&heap);       /* build from linked list */

    while (heap.size > 0 && total < PLAYING_XI) {
        Player *best = extractMax(&heap);
        int ri = roleIndex(best->role);

        if (ri != -1 && picked[ri] < limits[ri]) {
            xi[total++] = best;
            picked[ri]++;
        }
    }

    printf("\n--- Playing XI for %s ---\n", req.pitchName);
    printHeader();
    for (int i = 0; i < total; i++)
        printPlayer(xi[i]);

    printf("\nComposition: Bat %d/%d | Bowl %d/%d | AR %d/%d | Total %d/%d\n",
           picked[0], req.batsmen, picked[1], req.bowlers,
           picked[2], req.allRounders, total, PLAYING_XI);

    if (total < PLAYING_XI)
        printf("Could not fill XI — not enough players.\n");

    freeHeap(&heap);
}

/* ============================================================
 *                         MAIN
 * ============================================================ */

void showMenu(void) {
    printf("\n===== Smart playing 11 selector =====\n");
    printf("1. Add Player\n");
    printf("2. View All Players\n");
    printf("3. Search Player\n");
    printf("4. Filter by Role\n");
    printf("5. Generate Playing XI\n");
    printf("6. Show Rankings\n");
    printf("7. Exit\n");
    printf("Choice: ");
}

int main(void) {
    int choice;
    loadFromFile();

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Enter a number 1-7.\n");
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
            case 1: addPlayer();      break;
            case 2: traverseList();   break;
            case 3: searchPlayer();   break;
            case 4: filterByRole();   break;
            case 5: generateXI();     break;
            case 6: showRankings();   break;
            case 7: saveToFile(); printf("Goodbye!\n"); break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 7);

    freeList();
    return 0;
}
