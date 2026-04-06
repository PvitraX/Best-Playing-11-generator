/*
 * utils.h — Utility / helper function declarations
 */
#ifndef UTILS_H
#define UTILS_H

#include "player.h"

void  trimNewline(char *s);
void  clearInput(void);
int   strEq(const char *a, const char *b);
int   validRole(const char *r);
int   roleIndex(const char *role);
float calcRating(int runs, int wickets, const char *role);
void  printHeader(void);
void  printPlayer(const Player *p);

#endif
