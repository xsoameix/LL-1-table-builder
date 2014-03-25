#ifndef PARSER_H
#define PARSER_H

#include <libooc/object.h>


#undef CLASS
#define CLASS Parser
#define _Parser_PUBLIC_OVERRIDE_METHODS \
    (_Parser_ctor), \
    (_Parser_dtor)
#define _Parser_PUBLIC_METHODS \
    (_Parser_parse), \
    (_Parser_parse_NTS), \
    (_Parser_parse_NTS_), \
    (_Parser_parse_NTS__), \
    (_Parser_parse_NT), \
    (_Parser_parse_STMTS), \
    (_Parser_parse_STMTS_), \
    (_Parser_parse_TOKENS), \
    (_Parser_parse_TOKENS_), \
    (_Parser_next), \
    (_Parser_syntax_error)
#define _Parser_PRIVATE_METHODS \
    (_Parser_match)
#define _Parser_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Parser_dtor dtor, void
#define _Parser_parse parse, void *
#define _Parser_parse_NTS parse_NTS, void *
#define _Parser_parse_NTS_ parse_NTS_, void, (void * nonterminals, nonterminals)
#define _Parser_parse_NTS__ parse_NTS__, void, (void * nonterminals, nonterminals)
#define _Parser_parse_NT parse_NT, void, (void * nonterminals, nonterminals)
#define _Parser_parse_STMTS parse_STMTS, void, (void * nonterminal, nonterminal)
#define _Parser_parse_STMTS_ parse_STMTS_, void, (void * nonterminal, nonterminal)
#define _Parser_parse_TOKENS parse_TOKENS, void, (void * nonterminal, nonterminal)
#define _Parser_parse_TOKENS_ parse_TOKENS_, void, (void * tokens, tokens)
#define _Parser_match match, void, (enum TYPE expected, expected)
#define _Parser_next next, void
#define _Parser_syntax_error syntax_error, void
def_public_methods()

#endif
