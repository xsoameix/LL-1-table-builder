#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include <stdio.h>

typedef bool* Set;
typedef bool Element;

extern void addElement(Set s, int i);
extern void unionSet(Set a, Set b, int len);
extern void flushSet(Set s, int len);
extern void printElements(Set s, int len);

#endif
