#pragma once

#include <stdlib.h>
#include <stdio.h>

struct _Token
{
    int type;
    int data;
    int line;
};
typedef struct _Token Token;

void token_create(Token* token, int type, int data, int line);

enum _TokenType
{
    TTYPE_NONE,
    TTYPE_PUNC,
    TTYPE_KEYWORD,
    TTYPE_IDENTIFIER,
    TTYPE_LITERAL
};
typedef enum _TokenType TokenType;

enum _TokenPunc
{
    TPUNC_SEMICOLON,
    TPUNC_OPEN_PAREN,
    TPUNC_CLOSED_PAREN,
    TPUNC_OPEN_BRACE,
    TPUNC_CLOSED_BRACE
};
typedef enum _TokenPunc TokenPunc;

enum _TokenKeyword
{
    TKEYWORD_INT,
    TKEYWORD_RETURN
};
typedef enum _TokenKeyword TokenKeyword;

struct _TokenList
{
    Token* data;
    int ptr;
    int size;
};
typedef struct _TokenList TokenList;

void token_list_create(TokenList* list, int size);
void token_list_add(TokenList* list, Token token);
Token* token_list_get(TokenList* list, const int index);

TokenPunc token_get_punc(const char val);