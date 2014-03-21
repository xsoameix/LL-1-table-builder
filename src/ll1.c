#include <stdio.h>
#include <libooc/file.h>

#include "scanner.h"
#include "parser.h"
#include "table_builder.h"

int
main(void) {
    String_init();
    Array_init();
    Hash_init();
    File_init();
    Scanner_init();
    Parser_init();
    TableBuilder_init();
    void * file = new(File, "src/example.syntax");
    void * content = File_read(file);
    void * scanner = new(Scanner, content);
    void * parser = new(Parser, scanner);
    void * nonterminals = Parser_parse(parser);
    void * builder = new(TableBuilder, nonterminals);
    void * table = TableBuilder_build(builder);
    delete(parser);
    delete(scanner);
    delete(file);
    return 0;
}
