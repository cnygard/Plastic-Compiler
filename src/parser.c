#include "../include/parser.h"

ParserStatus parser_start(Lexer lexer, Parser* parser, AST* ast, Symbol* table, TokenList list)
{
    int i = 0;
    while (i <= list.ptr)
    {
        i = parser_parse_function(i, lexer, table, list);
    }
    return PARSER_SUCCESS;
}

// AST_Node parser_parser_function(int* index, Lexer lexer, Symbol* table, TokenList list)
int parser_parse_function(int index, Lexer lexer, Symbol* table, TokenList list)
{
    Token* t = token_list_get(&list, index++);
    while (t->type != TTYPE_PUNC && t->data != TPUNC_CLOSED_BRACE)
    {
        if (t->type != TTYPE_KEYWORD)
            parser_fail();
        
        t = token_list_get(&list, index++);
        if (t->type != TTYPE_IDENTIFIER)
            parser_fail();
        
        char* name = &lexer.identifier_buf[t->data];
        symbol_table_add_symbol(table, &lexer.identifier_buf[t->data]);

        AST_Node* function = ast_function_node_create(name);
        // int i = function->data.keyword;
        // return *function;
    }
    return index;
}

ParserStatus parser_fail()
{
    printf("bad\n");
    return PARSER_SYNTAX_ERROR;
}