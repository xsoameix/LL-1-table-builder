#include "Set.h"

void addElement(Set s, int i) {
        s[i] = true;
}

void unionSet(Set a, Set b, int len) {
        for(int i = 0; i < len; i++) {
                a[i] = a[i] || b[i];
        }
}

void flushSet(Set s, int len) {
        for(int i = 0; i < len; i++) {
                s[i] = false;
        }
}

void printElements(Set s, int len) {
        for(int i = 0; i < len; i++) {
                if(s[i]) {
                        printf("%d ", i);
                }
        }
        printf("\n");
}
