#pragma once

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#define SYMBOL_TABLE_SIZE 6

struct _Symbol
{
    char* name;
    // int type;
    // int data;
    struct _Symbol* next;
};
typedef struct _Symbol Symbol;

void symbol_table_init(Symbol* table);
int symbol_table_hash(const char* name);
void symbol_table_add_symbol(Symbol* table, char* name);
Symbol* symbol_table_get_symbol(Symbol** table, const char* name);