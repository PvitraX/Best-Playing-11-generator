/*
 * linkedlist.h — Linked List operations
 * DSA #1: Singly Linked List
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "player.h"

/* Global head pointer — defined in linkedlist.c, used everywhere */
extern Node *head;

Node *createNode(Player p);
void  insertNode(Player p);
void  traverseList(void);
void  freeList(void);
int   countPlayers(void);

#endif
