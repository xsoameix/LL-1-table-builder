#ifndef SCANNER_H
#define SCANNER_H

#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Lib.h"
#include "Token.h"

extern Token* scan(char *string);
extern bool isArrow(char *s, int offset);
extern bool isOr(char *s, int offset);
extern bool isAlphaOrPunct(char *s, int offset);
extern bool isAtNewLine(char *s, int offset);
extern bool isEOF(char *s, int offset);

#endif
