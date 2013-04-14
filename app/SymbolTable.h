#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "stdbool.h"
#include "Array.h"
#include "Token.h"

// These are for Symbol's type.

#define TERMINAL 260

typedef struct {
        int no;
        char *id;

        // Element type is Production.
        Array *P;
} NonTerminal;

typedef struct {
        int no;
        char *id;
} Terminal;

typedef struct {
        int type; // NONTERMINAL or TERMINAL.
        NonTerminal *NT;
        Terminal *T;
} Symbol;

typedef struct {
        // Element type is Symbol.
        Array *S;
} Production;

extern void storeNT(Token *t);
extern void storeT(Token *t);
extern void storeInWhichP(int NT_i, int P_i, int type, Token *tk);
extern void addInWhichP(int NT_i, int P_i, Symbol *s);
extern bool isNT(Token *t);

// NonTerminal utilities

void addNT(Token *t);
NonTerminal* newNT(Token *t);
int NT_IndexOf(Array *a, char *id);

// Terminal utilities

void addT(Token *t);
Terminal* newT(Token *token);
int T_IndexOf(Array *a, char *id);

// Symbol utilities

Symbol* newS_NT(NonTerminal *n);
Symbol* newS_T(Terminal *t);

// Producion utilities

Production* newP(Symbol *s);

#endif
