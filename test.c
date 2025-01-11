#include "codex.h"
#include "scanix.h"
#include "interprex.h"
#include <stdio.h>
#include <assert.h>



void testcodex() {
    printf("Running codex Tests...\n");

    
    FILE *source = fopen("test_input.txt", "w");
    fprintf(source, "program test; var x, y: int; begin x := 10; end.");
    fclose(source);

    source = fopen("test_input.txt", "r");
    Token token;

    
    token = getNextToken(source);
    assert(token.code == TOKEN_PROGRAM);
    assert(strcmp(token.lexeme, "program") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID);
    assert(strcmp(token.lexeme, "test") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_SEMICOLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_VAR);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID);
    assert(strcmp(token.lexeme, "x") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_COMMA);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID);
    assert(strcmp(token.lexeme, "y") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_COLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_INT);

    token = getNextToken(source);
    assert(token.code == TOKEN_SEMICOLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_BEGIN);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID);
    assert(strcmp(token.lexeme, "x") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_ASSIGN);

    token = getNextToken(source);
    assert(token.code == TOKEN_NB);
    assert(strcmp(token.lexeme, "10") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_SEMICOLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_END);

    token = getNextToken(source);
    assert(token.code == TOKEN_DOT);

    token = getNextToken(source);
    assert(token.code == TOKEN_EOF);

    fclose(source);
    printf("codex Tests Passed!\n");
}


void testscanix() {
    printf("Running scanix Tests...\n");

    
    FILE *source = fopen("test_input.txt", "w");
    fprintf(source, "program test; var x, y: int; begin x := 10; end.");
    fclose(source);

    source = fopen("test_input.txt", "r");
    lookahead = getNextToken(source);

    
    parseProgram(source);

    
    assert(lookahead.code == TOKEN_EOF);

    fclose(source);
    printf("scanix Tests Passed!\n");
}


void testinterprex() {
    printf("Running interprex Tests...\n");

   
    FILE *source = fopen("test_input.txt", "w");
    fprintf(source, "program test; var x, y: int; begin x := 10; y := x + 5; end.");
    fclose(source);

    source = fopen("test_input.txt", "r");
    lookahead = getNextToken(source);

  
    parseProgram(source);

   
    assert(lookahead.code == TOKEN_EOF);

    fclose(source);
    printf("interprex Tests Passed!\n");
}

int main() {
    testcodex();
    testscanix();
    testinterprex();
    printf("All tests passed!\n");
    return 0;
}
