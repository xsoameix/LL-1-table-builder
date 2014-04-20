#include <stdio.h>
#include <libooc/string.conflict.h>
#include <libooc/array.h>
#include <libooc/hash.h>
#include <libooc/file.h>
#include "scanner.h"
#include "parser.h"
#include "table.h"

int
main(void) {
    String_init();
    Array_init();
    Hash_init();
    File_init();
    Scanner_init();
    Parser_init();
    Table_init();
    void * input = new(File, "src/example.syntax");
    void * content = File_read(input);
    void * scanner = new(Scanner, content);
    void * parser = new(Parser, scanner);
    void * nonterminals = Parser_parse(parser);
    void * table = new(Table, nonterminals);
    void * output = new(File, "src/example.c");
    Table_write_to(table, output);
    delete(parser);
    delete(scanner);
    delete(input);
    delete(output);
    return 0;
}
