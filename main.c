#include "codex.h"
#include "scanix.h"
#include "interprex.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <source file>\n", argv[0]);
        return 1;
    }

    FILE *source = fopen(argv[1], "r");
    if (!source) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    lookahead = getNextToken(source);
    parseProgram(source);

    if (lookahead.code != TOKEN_EOF) {
        printf("Syntax error: unexpected token %s\n", lookahead.lexeme);
        return 1;
    }

    printf("Parsing completed successfully.\n");
    fclose(source);
    return 0;
}