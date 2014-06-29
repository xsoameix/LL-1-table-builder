#include <stdio.h>
#include <libooc/string.conflict.h>
#include <libooc/array.h>
#include <libooc/hash.h>
#include <libooc/file.h>
#include <libooc/object_type.h>
#include "scanner.h"
#include "parser.h"
#include "nonterminal.h"
#include "terminal.h"
#include "token.h"
#include "production.h"
#include "block.h"
#include "table.h"

void
ll1_init(int argc, char * argv[]) {
    char * file = argc > 1 ? argv[1] : "src/example.syntax";
    o input = new(File, file);
    o content = File_read(input);
    o scanner = new(Scanner, content);
    o parser = new(Parser, scanner);
    o nonterminals = Parser_parse(parser);
    o table = new(Table, nonterminals);
    o output = new(File, "src/example.c");
    Table_write_to(table, output);
    delete(table);
    delete(output);
    delete(parser);
    delete(scanner);
    delete(input);
}
