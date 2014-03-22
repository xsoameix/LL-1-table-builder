#include <stdio.h>
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
    void * file = new(File, "src/example.syntax");
    void * content = File_read(file);
    void * scanner = new(Scanner, content);
    void * parser = new(Parser, scanner);
    void * nonterminals = Parser_parse(parser);
    void * builder = new(Table, nonterminals);
    void * table = Table_build(builder);
    delete(parser);
    delete(scanner);
    delete(file);
    return 0;
}
