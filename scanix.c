#include <stdlib.h> 
#include "scanix.h"
#include "codex.h"

Token lookahead;

void match(TokenCode expected, FILE *source) {
    if (lookahead.code == expected) {
        lookahead = getNextToken(source);
    } else {
        printf("Syntax error: unexpected token %s\n", lookahead.lexeme);
        exit(1);
        
    }
}

void parseProgram(FILE *source) {
    match(TOKEN_PROGRAM, source);
    match(TOKEN_ID, source);
    match(TOKEN_SEMICOLON, source);
    parseDel(source);
    match(TOKEN_BEGIN, source);
    parseListe_inst(source);
    match(TOKEN_END, source);
    match(TOKEN_DOT, source);
}

void parseDel(FILE *source) {
    match(TOKEN_VAR, source);
    parseListe_id(source);
    match(TOKEN_COLON, source);
    match(TOKEN_INT, source);
    match(TOKEN_SEMICOLON, source);
}

void parseListe_id(FILE *source) {
    match(TOKEN_ID, source);
    if (lookahead.code == TOKEN_COMMA) {
        match(TOKEN_COMMA, source);
        parseListe_id(source);
    }
}

void parseListe_inst(FILE *source) {
    parseI(source);
    if (lookahead.code == TOKEN_ID || lookahead.code == TOKEN_IF || lookahead.code == TOKEN_WRITELN || lookahead.code == TOKEN_READLN) {
        parseListe_inst(source);
    }
}

void parseI(FILE *source) {
    if (lookahead.code == TOKEN_ID) {
        match(TOKEN_ID, source);
        match(TOKEN_ASSIGN, source);
        parseExp(source);
        match(TOKEN_SEMICOLON, source);
    } else if (lookahead.code == TOKEN_WRITELN) {
        match(TOKEN_WRITELN, source);
        match(TOKEN_LPAREN, source);
        match(TOKEN_ID, source);
        match(TOKEN_RPAREN, source);
        match(TOKEN_SEMICOLON, source);
    } else if (lookahead.code == TOKEN_READLN) {
        match(TOKEN_READLN, source);
        match(TOKEN_LPAREN, source);
        match(TOKEN_ID, source);
        match(TOKEN_RPAREN, source);
        match(TOKEN_SEMICOLON, source);
    } else if (lookahead.code == TOKEN_IF) {
        match(TOKEN_IF, source);
        parseC(source);
        match(TOKEN_THEN, source);
        parseListe_inst(source);
        match(TOKEN_ENDIF, source);
    } else {
        printf("Syntax error: unexpected token %s\n", lookahead.lexeme);
        exit(1);
    }
}

void parseC(FILE *source) {
    parseExp(source);
    match(TOKEN_OPREL, source);
    parseExp(source);
}

void parseExp(FILE *source) {
    if (lookahead.code == TOKEN_ID || lookahead.code == TOKEN_NB) {
        match(lookahead.code, source);
    } else if (lookahead.code == TOKEN_LPAREN) {
        match(TOKEN_LPAREN, source);
        parseExp(source);
        match(TOKEN_RPAREN, source);
    } else {
        printf("Syntax error: unexpected token %s\n", lookahead.lexeme);
        exit(1);
    }
    if (lookahead.code == TOKEN_OPARITH) {
        match(TOKEN_OPARITH, source);
        parseExp(source);
    }
}
