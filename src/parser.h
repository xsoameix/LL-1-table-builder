#ifndef O_PARSER_H
#define O_PARSER_H

#include <libooc/object.h>


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Parser
#define O_PARENT Object
#define O_Parser_OVERRIDE_METHODS_LEN 2
#define O_Parser_PUBLIC_METHODS_LEN 13
#define O_Parser_PRIVATE_METHODS_LEN 2
#define O_Parser_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Parser_OVERRIDE_METHOD_1 dtor, void
#define O_Parser_PUBLIC_METHOD_0 parse, void *
#define O_Parser_PUBLIC_METHOD_1 parse_NTS, void, (void * nonterminals, nonterminals)
#define O_Parser_PUBLIC_METHOD_2 parse_NT, void, (void * nonterminals, nonterminals)
#define O_Parser_PUBLIC_METHOD_3 parse_TOKENS, void, (void * nonterminal, nonterminal)
#define O_Parser_PUBLIC_METHOD_4 parse_TOKENS_, void, (void * nonterminal, nonterminal)
#define O_Parser_PUBLIC_METHOD_5 parse_TOKENS__, void, (void * nonterminal, nonterminal)
#define O_Parser_PUBLIC_METHOD_6 parse_TOKENS___, void, (void * nonterminal, nonterminal)
#define O_Parser_PUBLIC_METHOD_7 parse_TOKENS____, void, (void * nonterminal, nonterminal)
#define O_Parser_PUBLIC_METHOD_8 parse_BLOCK, void, (void * production, production)
#define O_Parser_PUBLIC_METHOD_9 parse_BLOCK_, void, (void * block, block)
#define O_Parser_PUBLIC_METHOD_10 parse_ANY_TOKEN, void, (void * block, block)
#define O_Parser_PUBLIC_METHOD_11 next, void
#define O_Parser_PUBLIC_METHOD_12 syntax_error, void
#define O_Parser_PRIVATE_METHOD_0 match, void, (enum TYPE expected, expected)
#define O_Parser_PRIVATE_METHOD_1 discard, void, (enum TYPE expected, expected)
#define O_Parser_ctor O_Parser_OVERRIDE_METHOD_0
#define O_Parser_dtor O_Parser_OVERRIDE_METHOD_1
#define O_Parser_parse O_Parser_PUBLIC_METHOD_0
#define O_Parser_parse_NTS O_Parser_PUBLIC_METHOD_1
#define O_Parser_parse_NT O_Parser_PUBLIC_METHOD_2
#define O_Parser_parse_TOKENS O_Parser_PUBLIC_METHOD_3
#define O_Parser_parse_TOKENS_ O_Parser_PUBLIC_METHOD_4
#define O_Parser_parse_TOKENS__ O_Parser_PUBLIC_METHOD_5
#define O_Parser_parse_TOKENS___ O_Parser_PUBLIC_METHOD_6
#define O_Parser_parse_TOKENS____ O_Parser_PUBLIC_METHOD_7
#define O_Parser_parse_BLOCK O_Parser_PUBLIC_METHOD_8
#define O_Parser_parse_BLOCK_ O_Parser_PUBLIC_METHOD_9
#define O_Parser_parse_ANY_TOKEN O_Parser_PUBLIC_METHOD_10
#define O_Parser_next O_Parser_PUBLIC_METHOD_11
#define O_Parser_syntax_error O_Parser_PUBLIC_METHOD_12
#define O_Parser_match O_Parser_PRIVATE_METHOD_0
#define O_Parser_discard O_Parser_PRIVATE_METHOD_1
O_DEF_GLOBAL_METHODS()

#endif
