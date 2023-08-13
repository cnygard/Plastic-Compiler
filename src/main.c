#include <string.h>
#include <stdio.h>

#include "../include/util.h"
#include "../include/token.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/symbol_table.h"
#include "../include/ast.h"

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("Too few arguments\n");
        printf("Expected input: ./Plastic -[operator] [file]\n");
        printf("e.g. ./Plastic -c code.c\n");
        return 1;
    }

    // Compile
    if (strcmp(argv[1], "-c") == 0)
    {
        char* source = read_ascii_file(argv[2]);
        TokenList tokens;
        token_list_create(&tokens, 1);

        Lexer lexer;
        LexerStatus lstat = lexer_start(&lexer, &tokens, source);
        if (lstat != LEXER_SUCCESS) {
            printf("Lexer error\n");
            return 1;
        }

        
        // // TESTING
        Token* token;
        int count = 0;
        printf("Token list (size:%d):\n", tokens.size);
        for (int i = 0; i < tokens.size; i++)
        {
            token = token_list_get(&tokens, i);
            printf("\tType: %d, Data: %d, Line: %d\n", token->type, token->data, token->line);
        }
        printf("Identifiers:\n");
        for (int i = 0; i < LEXER_IDENTIFIER_BUF_SIZE; i++)
            printf("%c", lexer.identifier_buf[i]);
        printf("\n");
        // // TESTING

        AST ast;
        Symbol symbolTable[SYMBOL_TABLE_SIZE];
        symbol_table_init(symbolTable);
        Parser parser;
        ParserStatus pstat = parser_start(lexer, &parser, &ast, symbolTable, tokens);
        if (pstat != PARSER_SUCCESS) {
            printf("Parser error\n");
            return 1;
        }
    }
}