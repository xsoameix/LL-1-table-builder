#ifndef SCANNER_H
#define SCANNER_H

#include <libooc/object.h>


#undef CLASS
#define CLASS Scanner
#define _Scanner_PUBLIC_OVERRIDE_METHODS \
    (_Scanner_ctor), \
    (_Scanner_dtor)
#define _Scanner_PUBLIC_METHODS \
    (_Scanner_scan), \
    (_Scanner_max), \
    (_Scanner_space_p), \
    (_Scanner_token_p), \
    (_Scanner_open_brace_p), \
    (_Scanner_close_brace_p), \
    (_Scanner_colon_p), \
    (_Scanner_or_p), \
    (_Scanner_next_line_p), \
    (_Scanner_EOF_p), \
    (_Scanner_token)
#define _Scanner_PRIVATE_METHODS
#define _Scanner_ctor ctor, void, (va_list * args_ptr, args_ptr)
#define _Scanner_dtor dtor, void
#define _Scanner_scan scan, void
#define _Scanner_max max, char *, (char * z, z), (char * b, b)
#define _Scanner_space_p space_p, bool, (char c, c)
#define _Scanner_token_p token_p, bool, (char c, c)
#define _Scanner_open_brace_p open_brace_p, bool, (char c, c)
#define _Scanner_close_brace_p close_brace_p, bool, (char c, c)
#define _Scanner_colon_p colon_p, bool, (char c, c)
#define _Scanner_or_p or_p, bool, (char c, c)
#define _Scanner_next_line_p next_line_p, bool, (char c, c)
#define _Scanner_EOF_p EOF_p, bool, (char c, c)
#define _Scanner_token token, void *
def_public_methods()

#endif
