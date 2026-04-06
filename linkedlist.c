/*
 * linkedlist.c — Singly Linked List implementation
 *
 * DSA #1: LINKED LIST
 *   - Each node holds a Player + pointer to the next node
 *   - insertNode()   : O(n)  — appends at the end
 *   - traverseList() : O(n)  — prints every node
 *   - countPlayers() : O(n)  — counts all nodes
 *   - freeList()     : O(n)  — deallocates all nodes
 */
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "utils.h"

/* The single global head of our linked list */
Node *head = NULL;

/* Allocate a new node and copy player data into it */
Node *createNode(Player p) {
    Node *n = (Node *)malloc(sizeof(Node));
    
    n->data = p;
    n->next = NULL;
    return n;
}

/* Insert a player at the END of the list */
void insertNode(Player p) {
    Node *newNode = createNode(p);

    if (head == NULL) {          /* empty list */
        head = newNode;
        return;
    }

    Node *cur = head;
    while (cur->next != NULL)    /* walk to last node */
        cur = cur->next;
    cur->next = newNode;         /* link new node */
}

/* Traverse and display all players */
void traverseList(void) {
    if (!head) { printf("\nNo players found.\n"); return; }

    printHeader();
    Node *cur = head;
    while (cur != NULL) {
        printPlayer(&cur->data);
        cur = cur->next;
    }
}

/* Free every node in the list */
void freeList(void) {
    Node *cur = head;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    head = NULL;
}

/* Count total nodes — O(n) */
int countPlayers(void) {
    int count = 0;
    for (Node *c = head; c; c = c->next)
        count++;
    return count;
}
