#include "codex.h"

Token getNextToken(FILE *source) {
    Token token;
    char ch;
    int i = 0;

    
    while ((ch = fgetc(source)) == ' ' || ch == '\n' || ch == '\t');

    if (ch == EOF) {
        token.code = TOKEN_EOF;
        return token;
        
    }

    
    if (isalpha(ch)) {
        token.lexeme[i++] = ch;
        while (isalnum(ch = fgetc(source))) {
            token.lexeme[i++] = ch;
        }
        token.lexeme[i] = '\0';
        ungetc(ch, source);

        if (isKeyword(token.lexeme)) {
            if (strcmp(token.lexeme, "program") == 0) token.code = TOKEN_PROGRAM;
            else if (strcmp(token.lexeme, "var") == 0) token.code = TOKEN_VAR;
            else if (strcmp(token.lexeme, "int") == 0) token.code = TOKEN_INT;
            else if (strcmp(token.lexeme, "begin") == 0) token.code = TOKEN_BEGIN;
            else if (strcmp(token.lexeme, "end") == 0) token.code = TOKEN_END;
            else if (strcmp(token.lexeme, "writeln") == 0) token.code = TOKEN_WRITELN;
            else if (strcmp(token.lexeme, "readln") == 0) token.code = TOKEN_READLN;
            else if (strcmp(token.lexeme, "if") == 0) token.code = TOKEN_IF;
            else if (strcmp(token.lexeme, "then") == 0) token.code = TOKEN_THEN;
            else if (strcmp(token.lexeme, "endif") == 0) token.code = TOKEN_ENDIF;
        } else {
            token.code = TOKEN_ID;
        }
        return token;
    }

    
    if (isdigit(ch)) {
        token.lexeme[i++] = ch;
        while (isdigit(ch = fgetc(source))) {
            token.lexeme[i++] = ch;
        }
        token.lexeme[i] = '\0';
        ungetc(ch, source);
        token.code = TOKEN_NB;
        return token;
    }

    
    switch (ch) {
        case ';': token.code = TOKEN_SEMICOLON; break;
        case ':': {
            char nextCh = fgetc(source);
            if (nextCh == '=') {
                token.code = TOKEN_ASSIGN;
                token.lexeme[i++] = ch;
                token.lexeme[i++] = nextCh;
            } else {
                ungetc(nextCh, source);
                token.code = TOKEN_COLON;
                token.lexeme[i++] = ch;
            }
            token.lexeme[i] = '\0';
            return token;
        }
        case ',': token.code = TOKEN_COMMA; break;
        case '.': token.code = TOKEN_DOT; break;
        case '(': token.code = TOKEN_LPAREN; break;
        case ')': token.code = TOKEN_RPAREN; break;
        case '+': case '*': token.code = TOKEN_OPARITH; break;
        case '<': case '>': {
            token.code = TOKEN_OPREL;
            char nextCh = fgetc(source);
            if ((ch == '<' && nextCh == '>') || (ch == '<' && nextCh == '=') || (ch == '>' && nextCh == '=')) {
                token.lexeme[i++] = ch;
                token.lexeme[i++] = nextCh;
            } else {
                ungetc(nextCh, source);
                token.lexeme[i++] = ch;
            }
            token.lexeme[i] = '\0';
            return token;
        }
        default: token.code = TOKEN_ERROR; break;
    }

    token.lexeme[0] = ch;
    token.lexeme[1] = '\0';
    return token;
}

int isKeyword(char *str) {
    char *keywords[] = {"program", "var", "int", "begin", "end", "writeln", "readln", "if", "then", "endif"};
    for (int i = 0; i < 10; i++) {
        if (strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}
