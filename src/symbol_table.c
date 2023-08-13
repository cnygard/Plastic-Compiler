#include "../include/symbol_table.h"

void symbol_table_init(Symbol* table)
{
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
    {
        table[i].name = NULL;
        table[i].next = NULL;
    }
}

int symbol_table_hash(const char* name)
{
    int sum = 0;
    while (*name) { sum += *name++; }
    return sum % SYMBOL_TABLE_SIZE;
}

void symbol_table_add_symbol(Symbol* table, char* name)
{
    // Testing
    printf("name: %s\n", name);
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++)
    {
        printf("index: %d, name: %s\n", i, table[i].name);
        if (table[i].next != NULL)
            printf("next: %s\n", table[i].next->name);
    }
    // Testing
    int index = symbol_table_hash(name);
    Symbol* curr = &table[index];
    while (curr)
    {
        if (curr->name == NULL)
            break;
        if (strcmp(curr->name, name) == 0)
            return;
        curr = curr->next;
    }
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->name = name;
    symbol->next = &table[index];
    table[index] = *symbol;
}

Symbol* symbol_table_get_symbol(Symbol** table, const char* name)
{
    int index = symbol_table_hash(name);
    Symbol* curr = table[index];
    while (curr)
    {
        if (strcmp(curr->name, name) == 0) { return curr; }
        curr = curr->next;
    }
    return NULL;
}