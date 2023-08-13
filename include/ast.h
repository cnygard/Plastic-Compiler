#pragma once

#include <stdlib.h>
#include "token.h"
#include "symbol_table.h"

enum _AST_Type
{
    ASTT_BRANCH,
    ASTT_KEYWORD,
    ASTT_FUNCTION,
    ASTT_IVARIABLE,
    ASTT_INTEGER
};
typedef enum _AST_Type AST_Type;

struct _AST_Node
{
    AST_Type type;
    union
    {
        int integer_val;
        TokenKeyword keyword;
        char* identifier;
    } data;
    struct _AST_Node* children;
    int child_count;
    int child_ptr;
};
typedef struct _AST_Node AST_Node;

struct _AST
{
    AST_Node start_node;
};
typedef struct _AST AST;

AST_Node* ast_keyword_node_create();
AST_Node* ast_function_node_create(char* name);
AST_Node* ast_ivariable_node_create(char* name, int val);
AST_Node* ast_integer_node_create(int val);

void ast_node_list_create(AST_Node* list, int size);
void ast_node_list_add(AST_Node* nodes, AST_Node node);
AST_Node* ast_node_list_get(AST_Node* list, int index);