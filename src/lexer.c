#include "../include/lexer.h"

LexerStatus lexer_start(Lexer* lexer, TokenList* list, const char* source)
{
    bool isRunning = true;
    lexer->insert_point = 0;
    char lex[LEXER_LEX_SIZE];
    int lexIx = 0;
    int sourceIx = 0;
    int line = 1;
    char delim = ' ';
    LexerMode mode = LMODE_NONE;

    while (isRunning)
    {
        // Reset lex
        memset(&lex, '\0', 256);
        lexIx = 0;

        // Set mode
        if (isCharacter(source[sourceIx]) || source[sourceIx] == '_')
            mode = LMODE_STRING;
        else if (isDigit(source[sourceIx]))
            mode = LMODE_NUMBER;
        else
            mode = LMODE_NONE;

        while (source[sourceIx] != delim)
        {
            if (!lexer_char_fits_mode(mode, source[sourceIx + 1]) || isPunctuation(source[sourceIx])) {
                lex[lexIx++] = source[sourceIx++];
                break;
            }

            // End of something
            if (source[sourceIx] == '\n' || source[sourceIx] == '\0')
                break;
            
            // Lines and tabs
            if (lexIx != 0 && (source[sourceIx] == '\n' || source[sourceIx] == '\t'))
            {
                sourceIx++;
                if (source[sourceIx] == '\n') { line++; }
                continue;
            }

            // Comments
            else if (source[sourceIx] == '/' && source[sourceIx + 1] == '/')
            {
                while (source[sourceIx] != '\n' && source[sourceIx] != '\0')
                    sourceIx++;
                break;
            }

            // Strings
            else if (source[sourceIx] == '"')
                delim = '"';

            lex[lexIx++] = source[sourceIx++];
        }

        // Strings
        if (delim == '"')
        {
            delim = ' ';
            lex[lexIx++] = '"';
            sourceIx++;
        }
        
        Token token;
        if (isCharacter(lex[0]) || lex[0] == '_')
        {
            int data = lexer_get_keyword(lex);
            if (data != -1)
            {
                token_create(&token, TTYPE_KEYWORD, data, line);
            } else {
                data = lexer_get_identifier(lexer, lex);
                token_create(&token, TTYPE_IDENTIFIER, data, line);
            }
            token_list_add(list, token);

            // TESTING
            // printf("Added token with type: %d\n", token.type);
            // TESTING




        }

        if (isDigit(lex[0]))
        {
            int data = atoi(lex);
            token_create(&token, TTYPE_LITERAL, data, line);
            token_list_add(list, token);


            // TESTING
            // printf("Added token with type: %d\n", token.type);
            // TESTING

            

        }

        if (isPunctuation(lex[0]))
        {
            int data = token_get_punc(lex[0]);
            token_create(&token, TTYPE_PUNC, data, line);
            token_list_add(list, token);


            // TESTING
            // printf("Added token with type: %d\n", token.type);
            // TESTING

            

        }
        
        // TESTING
        // for(int i = 0; i < LEXER_LEX_SIZE; i++) {
        //     if (lex[i] == '\0')
        //         break;
        //     printf("%c", lex[i]);
        // }
        // printf("\n");
        // TESTING




        if (source[sourceIx] == ' ')
            sourceIx++;
        else if (source[sourceIx] == '\n')
        {
            sourceIx++;
            line++;
            mode = LMODE_NONE;
        }
        else if (source[sourceIx] == '\0')
        {

            // TESTING
            // for (int i = 0; i < list->size; i++) {
            //     printf("%d", list->data[i].type);
            // }
            // printf("\n");
            // TESTING



            isRunning = false;
            return LEXER_SUCCESS;
        }
    }
    return LEXER_LEXICAL_ERROR;
}

TokenKeyword lexer_get_keyword(const char* buf)
{
    if (strcmp(buf, "int") == 0) { return TKEYWORD_INT; }
    if (strcmp(buf, "return") == 0) { return TKEYWORD_RETURN; }
    return -1;
}

int lexer_get_identifier(Lexer* lexer, const char* buf)
{
    int original_insert_point = lexer->insert_point;
    int i = 0;
    while (buf[i] != '\0')
    {
        lexer->identifier_buf[lexer->insert_point] = buf[i];
        lexer->insert_point++;
        i++;
    }
    lexer->identifier_buf[lexer->insert_point] = '\0';
    lexer->insert_point++;
    return original_insert_point;
}

bool lexer_char_fits_mode(LexerMode mode, char target)
{
    if (mode == LMODE_NONE)
        return true;
    if (mode == LMODE_STRING && (isCharacter(target) || isDigit(target) || target == '_'))
        return true;
    if (mode == LMODE_NUMBER && isDigit(target))
        return true;
    return false;
}