#pragma once

#include <stdbool.h>
#include <memory.h>

#include "util.h"
#include "token.h"

#define LEXER_LEX_SIZE 256
#define LEXER_IDENTIFIER_BUF_SIZE 4096

struct _Lexer
{
    int insert_point;
    char identifier_buf[LEXER_IDENTIFIER_BUF_SIZE];
};
typedef struct _Lexer Lexer;

enum _LexerStatus
{
    LEXER_SUCCESS,
    LEXER_LEXICAL_ERROR
};
typedef enum _LexerStatus LexerStatus;

LexerStatus lexer_start(Lexer* lexer, TokenList* list, const char* source);

enum _LexerMode
{
    LMODE_NONE,
    LMODE_STRING,
    LMODE_NUMBER
};
typedef enum _LexerMode LexerMode;

TokenKeyword lexer_get_keyword(const char* buf);
int lexer_get_identifier(Lexer* lexer, const char* buf);
bool lexer_char_fits_mode(LexerMode mode, char target);