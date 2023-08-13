#pragma once

#include <stdio.h>

#include "ast.h"
#include "lexer.h"
#include "symbol_table.h"
#include "token.h"

struct _Parser
{

};
typedef struct _Parser Parser;

enum _ParserStatus
{
    PARSER_SUCCESS,
    PARSER_SYNTAX_ERROR,
    PARSER_SYMANTIC_ERROR
};
typedef enum _ParserStatus ParserStatus;

ParserStatus parser_start(Lexer lexer, Parser* parser, AST* ast, Symbol* table, TokenList list);

// AST_Node parser_parser_function(int index, Lexer lexer, Symbol* table, TokenList list);
int parser_parse_function(int index, Lexer lexer, Symbol* table, TokenList list);

ParserStatus parser_fail();