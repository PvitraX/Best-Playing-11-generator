/*
 * player.h — Shared struct definitions and constants
 * This header is included by ALL other files.
 */
#ifndef PLAYER_H
#define PLAYER_H

#define NAME_LEN      50
#define ROLE_LEN      20
#define FILE_NAME     "players.txt"
#define PLAYING_XI    11
#define HEAP_INIT_CAP 16

/* -------- Player Struct -------- */
typedef struct {
    char  name[NAME_LEN];
    int   age;
    char  role[ROLE_LEN];   /* "Batsman", "Bowler", "All-rounder" */
    int   runs;
    int   wickets;
    float rating;
} Player;

/* -------- Linked List Node -------- */
typedef struct Node {
    Player       data;
    struct Node *next;
} Node;

/* -------- Max Heap -------- */
typedef struct {
    Player **arr;   /* array of Player pointers */
    int      size;
    int      cap;
} MaxHeap;

/* -------- Pitch Requirement -------- */
typedef struct {
    char pitchName[20];
    int  batsmen;
    int  bowlers;
    int  allRounders;
} PitchReq;

#endif
