#include "Parser.h"

/* syntax:
 * PS -> P PS | epsilon
 * P -> NT "->" STMTS
 * STMTS -> SYMBOLS STMTS'
 * STMTS' -> '|' SYMBOLS STMTS' | epsilon
 * SYMBOLS -> SYMBOL SYMBOLS | epsilon
 */

void parse() {
        parse_PS();
}

void parse_PS() {
        if() {
                parse_P();
                parse_PS();
        }
}

void parse_P() {
        match(NT);
        match("->");
        parse_STMTS();
}

void parse_STMTS() {
        parse_SYMBOLS();
        parse_SYMBOLS_();
}

void parse_STMTS_() {
        if() {
                match("|");
                parse_SYMBOLS();
                parse_SYMBOLS_();
        }
}

void parse_SYMBOLS() {
        if() {
                match(SYMBOL);
                parse_SYMBOLS();
        }
}
