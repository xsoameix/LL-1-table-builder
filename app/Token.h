#ifndef TOKEN_H
#define TOKEN_H

// For Scanner & Parser
#define TOKEN 256
#define ARROW 257
#define OR    258
#define NT    259

typedef struct {
        char *id;
        int type;
} Token;

#endif
