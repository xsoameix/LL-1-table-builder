#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "Scanner.h"
#include "ParserTree.h"

extern Tree* parse(char *file);

void parse_PS();
void parse_P();
void parse_STMTS();
void parse_STMTS_();
void parse_TOKENS();
void syntaxError();
void match(int c);
void next();
void syntaxError();

#endif
