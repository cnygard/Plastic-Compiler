#include "../include/token.h"

void token_create(Token* token, int type, int data, int line)
{
    token->type = type;
    token->data = data;
    token->line = line;
}

void token_list_create(TokenList* list, int size)
{
    list->data = (Token*) calloc(size, sizeof(Token));
    list->ptr = 0;
    list->size = size;
}

void token_list_add(TokenList* list, Token token)
{
    if (list->ptr >= list->size)
    {
        list->size *= 2;
        list->data = (Token*) realloc(list->data, sizeof(Token) * list->size);
    }

    Token* t = &list->data[list->ptr++];
    token_create(t, token.type, token.data, token.line);
}

Token* token_list_get(TokenList* list, const int index)
{
    if (index < list->size)
        return &list->data[index];
    printf("Token list out of bounds for index: %d\n", index);
    return NULL;
}

TokenPunc token_get_punc(const char val)
{
    switch (val)
    {
        case ';':
            return TPUNC_SEMICOLON;
        case '(':
            return TPUNC_OPEN_PAREN;
        case ')':
            return TPUNC_CLOSED_PAREN;
        case '{':
            return TPUNC_OPEN_BRACE;
        case '}':
            return TPUNC_CLOSED_BRACE;
        default:
            return -1;
    };
}