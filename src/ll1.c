#include <stdio.h>
#include <libooc/string.conflict.h>
#include <libooc/array.h>
#include <libooc/hash.h>
#include <libooc/file.h>
#include "scanner.h"
#include "parser.h"
#include "nonterminal.h"
#include "terminal.h"
#include "token.h"
#include "production.h"
#include "block.h"
#include "table.h"

static void
init(void) {
    // libooc
    String_init();
    Array_init();
    Hash_init();
    File_init();

    Scanner_init();
    Parser_init();
    Table_init();
    Token_init();
    Nonterminal_init();
    Terminal_init();
    Production_init();
    Block_init();
}

int
main(void) {
    init();
    void * input = new(File, "src/example.syntax");
    void * content = File_read(input);
    void * scanner = new(Scanner, content);
    void * parser = new(Parser, scanner);
    void * nonterminals = Parser_parse(parser);
    void * table = new(Table, nonterminals);
    void * output = new(File, "src/example.c");
    Table_write_to(table, output);
    delete(table);
    delete(output);
    delete(parser);
    delete(scanner);
    delete(input);
    return 0;
}
