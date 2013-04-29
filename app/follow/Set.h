#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include <stdio.h>

typedef bool* Set;
typedef bool Element;

void addElement(Set s, int i);
void unionSet(Set a, Set b, int len);
void flushSet(Set s, int len);
void printElements(Set s, int len);

#endif
