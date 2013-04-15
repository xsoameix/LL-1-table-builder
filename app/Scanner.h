#ifndef SCANNER_H
#define SCANNER_H

#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Lib.h"
#include "Token.h"

Token* scan(char *string);

#endif
