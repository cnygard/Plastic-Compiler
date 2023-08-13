#include "../include/ast.h"

AST_Node* ast_keyword_node_create(TokenKeyword keyword)
{
    AST_Node* node = (AST_Node*) malloc(sizeof(AST_Node));
    node->type = ASTT_KEYWORD;
    node->data.keyword = keyword;
    return node;
}

AST_Node* ast_function_node_create(char* name)
{
    AST_Node* node = (AST_Node*) malloc(sizeof(AST_Node));
    node->type = ASTT_FUNCTION;
    node->data.identifier = name;
    return node;
}

AST_Node* ast_ivariable_node_create(char* name, int val)
{
    AST_Node* node = (AST_Node*) malloc(sizeof(AST_Node));
    node->type = ASTT_IVARIABLE;
    node->data.identifier = name;
    return node;
}

AST_Node* ast_integer_node_create(int val)
{
    AST_Node* node = (AST_Node*) malloc(sizeof(AST_Node));
    node->type = ASTT_IVARIABLE;
    node->data.integer_val = val;

    return node;
}

void ast_node_list_create(AST_Node* list, int size)
{
    list->children = (AST_Node*) calloc(size, sizeof(AST_Node));
    list->child_ptr = 0;
    list->child_count = size;
}

void ast_node_list_add(AST_Node* list, AST_Node node)
{
    if (list->child_ptr >= list->child_count)
    {
        list->child_count = list->child_count * 2;
        list->children = (AST_Node*) realloc(list->children, sizeof(AST_Node) * list->child_count);
    }
    // &list->children[list->child_ptr++];
}

AST_Node* ast_node_list_get(AST_Node* list, int index)
{
    if (index < list->child_count)
        return &list->children[index];
    printf("AST node list out of bounds for index: %d\n", index);
    return NULL;
}