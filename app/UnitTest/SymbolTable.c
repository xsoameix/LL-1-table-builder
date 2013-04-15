#include "SymbolTable.h"

static char* UStoreInWhichP();

char* USymbolTable() {
        mu_run_test(UStoreInWhichP);
        return 0;
}

static
char* UStoreInWhichP() {
        resetNT();
        storeNT(newToken("expr", NONTERMINAL));
        storeInWhichP(0, 0, NONTERMINAL, newToken("expr", NONTERMINAL));
        Array *NT = getNT();
        mu_assert("error, count of array of NT != 1", NT->count == 1);
        NonTerminal *n = (NonTerminal*) NT->item[0];
        mu_assert("error, NT[0]->no != 0", n->no == 0);
        mu_assert("error, NT[0]->id != \"expr\"", strcmp(n->id, "expr") == 0);
        mu_assert("error, NT[0]->P->count != 1", n->P->count == 1);
        Production *p = (Production*) n->P->item[0];
        mu_assert("error, NT[0]->P[0]->S->count != 1", p->S->count == 1);
        Symbol *s = (Symbol*) p->S->item[0];
        mu_assert("error, NT[0]->P[0]->S[0]->type != NONTERMINAL", s->type == NONTERMINAL);
        mu_assert("error, NT[0]->P[0]->S[0]->NT->id != \"expr\"", strcmp(s->NT->id, "expr") == 0);
        return 0;
}
