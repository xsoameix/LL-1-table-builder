#ifndef O_SCANNER_H
#define O_SCANNER_H

#include <libooc/object.h>


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Scanner
#define O_PARENT Object
#define O_Scanner_OVERRIDE_METHODS_LEN 2
#define O_Scanner_PUBLIC_METHODS_LEN 11
#define O_Scanner_PRIVATE_METHODS_LEN 0
#define O_Scanner_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Scanner_OVERRIDE_METHOD_1 dtor, void
#define O_Scanner_PUBLIC_METHOD_0 scan, void
#define O_Scanner_PUBLIC_METHOD_1 max, char *, (char * z, z), (char * b, b)
#define O_Scanner_PUBLIC_METHOD_2 space_p, bool, (char c, c)
#define O_Scanner_PUBLIC_METHOD_3 token_p, bool, (char c, c)
#define O_Scanner_PUBLIC_METHOD_4 open_brace_p, bool, (char c, c)
#define O_Scanner_PUBLIC_METHOD_5 close_brace_p, bool, (char c, c)
#define O_Scanner_PUBLIC_METHOD_6 colon_p, bool, (char c, c)
#define O_Scanner_PUBLIC_METHOD_7 or_p, bool, (char c, c)
#define O_Scanner_PUBLIC_METHOD_8 next_line_p, bool, (char c, c)
#define O_Scanner_PUBLIC_METHOD_9 EOF_p, bool, (char c, c)
#define O_Scanner_PUBLIC_METHOD_10 token, void *
#define O_Scanner_ctor O_Scanner_OVERRIDE_METHOD_0
#define O_Scanner_dtor O_Scanner_OVERRIDE_METHOD_1
#define O_Scanner_scan O_Scanner_PUBLIC_METHOD_0
#define O_Scanner_max O_Scanner_PUBLIC_METHOD_1
#define O_Scanner_space_p O_Scanner_PUBLIC_METHOD_2
#define O_Scanner_token_p O_Scanner_PUBLIC_METHOD_3
#define O_Scanner_open_brace_p O_Scanner_PUBLIC_METHOD_4
#define O_Scanner_close_brace_p O_Scanner_PUBLIC_METHOD_5
#define O_Scanner_colon_p O_Scanner_PUBLIC_METHOD_6
#define O_Scanner_or_p O_Scanner_PUBLIC_METHOD_7
#define O_Scanner_next_line_p O_Scanner_PUBLIC_METHOD_8
#define O_Scanner_EOF_p O_Scanner_PUBLIC_METHOD_9
#define O_Scanner_token O_Scanner_PUBLIC_METHOD_10
O_DEF_GLOBAL_METHODS()

#endif
