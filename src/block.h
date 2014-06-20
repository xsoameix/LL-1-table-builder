#ifndef O_BLOCK_H
#define O_BLOCK_H

#include <libooc/object.h>


#undef O_CLASS
#undef O_PARENT
#define O_CLASS Block
#define O_PARENT Object
#define O_Block_OVERRIDE_METHODS_LEN 3
#define O_Block_PUBLIC_METHODS_LEN 6
#define O_Block_PRIVATE_METHODS_LEN 0
#define O_Block_OVERRIDE_METHOD_0 ctor, void, (va_list * args_ptr, args_ptr)
#define O_Block_OVERRIDE_METHOD_1 dtor, void
#define O_Block_OVERRIDE_METHOD_2 inspect, char *
#define O_Block_PUBLIC_METHOD_0 set_id, void, (o_uint id, id)
#define O_Block_PUBLIC_METHOD_1 id, o_uint
#define O_Block_PUBLIC_METHOD_2 no, o_uint
#define O_Block_PUBLIC_METHOD_3 tokens, void *
#define O_Block_PUBLIC_METHOD_4 add_token, void, (void * token, token)
#define O_Block_PUBLIC_METHOD_5 expand, void
#define O_Block_ctor O_Block_OVERRIDE_METHOD_0
#define O_Block_dtor O_Block_OVERRIDE_METHOD_1
#define O_Block_inspect O_Block_OVERRIDE_METHOD_2
#define O_Block_set_id O_Block_PUBLIC_METHOD_0
#define O_Block_id O_Block_PUBLIC_METHOD_1
#define O_Block_no O_Block_PUBLIC_METHOD_2
#define O_Block_tokens O_Block_PUBLIC_METHOD_3
#define O_Block_add_token O_Block_PUBLIC_METHOD_4
#define O_Block_expand O_Block_PUBLIC_METHOD_5
O_DEF_GLOBAL_METHODS()

#endif
