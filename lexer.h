#ifndef lexer_h
#define lexer_h
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector.h>
typedef enum{
    //type
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    VOID,
    UNSIGNED,
    SIGNED,
    SHORT,
    LONG,
    //keywords
    WHILE,
    DO,
    FOR,
    IF,
    ELSE, 
    IDENTIFIER,
    STRUCT,
    TYPEDEF,
    ENUM,
    NUM_LITERAL,
    //Brackets
    OPEN_PARENTHESIS,   // (
    CLOSE_PARENTHESIS,  // )
    OPEN_BRACE,         // {
    CLOSE_BRACE,        // }
    OPEN_BRACKET,       // [
    CLOSE_BRACKET,      // ]
    SEMICOLON,          // ;
    COMMA,              // ,
    STRING_LITERAL,     // string
    //arithmetic
    ADD,    // +
    SUB,    // -
    MUL,    // *
    DIV,    // /
    ASSIGN, // =
    MOD,    // %

    // unary
    INCREMENT,  // ++
    DECREMENT,  // --

    // relations
    LESS,       // <
    GREATER,    // >
    LESS_EQ,    // <=
    GREATER_EQ, // >=
    EQUAL,      // ==
    NOT_EQUAL,  // !=

    // logical
    AND,    // &&
    OR,     // ||
    NOT,    // !

    // bitwise
    BIT_AND,    // &
    BIT_OR,     // |
    LEFT_SHIFT, // <<
    RIGHT_SHIFT,// >>
    BIT_NOT,    // ~
    BIT_XOR,    // ^

    // assignment
    ASSIGN_EQ,  // ==
    ADD_EQ,     // +=
    SUB_EQ,     // -=
    DIV_EQ,     // /=
    MUL_EQ,     // *=
    MOD_EQ,     // %=

    // bitwise assignment
    BIT_AND_EQ, // &=
    BIT_OR_EQ,  // |=
    BIT_XOR_EQ, // ^=

    // struct member access
    DOT,        // .
    ARROW,      // ->

    // special
    CONDITIONAL // ?:
}Token_type;
typedef struct Token{
    char* word;
    int line;
    Token_type type;
}Token;

extern Vector* tokens;

void load_file(char* name);//this function opens the file and puts all the contents in the buffer
void format_data(char* text);//converts all text from the buffer into tokens
void check_data_type(char* buffer,Token_type type,int line);
void tokens_print(void);
#endif