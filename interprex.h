#ifndef interprex_H
#define interprex_H

#include "codex.h"

void checkType(TokenCode type1, TokenCode type2);
void generateCode(char *op);
void parseExpSem(FILE *source);


#endif 
