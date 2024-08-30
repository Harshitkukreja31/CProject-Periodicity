#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "periodic_table.h"
#include "hashtable.h"

// Function to convert a string to lowercase
char* to_lowercase(const char* str) {
    char* lower_str = strdup(str);
    for (int i = 0; lower_str[i]; i++) {
        lower_str[i] = tolower((unsigned char)lower_str[i]);
    }
    return lower_str;
}

PeriodicTable* create_periodic_table() {
    PeriodicTable* pt = (PeriodicTable*)malloc(sizeof(PeriodicTable));
    pt->symbolTable = ht_create(128);
    pt->nameTable = ht_create(128);
    pt->atomicTable = ht_create(128);
    return pt;
}

void free_periodic_table(PeriodicTable* pt) {
    if (!pt) return;
    ht_free(pt->symbolTable);
    ht_free(pt->nameTable);
    ht_free(pt->atomicTable);
    free(pt);
}

Element* pt_get_by_symbol(PeriodicTable* pt, const char* symbol) {
    char* lower_symbol = to_lowercase(symbol);
    Element* element = (Element*)ht_get(pt->symbolTable, lower_symbol);
    free(lower_symbol);
    return element;
}

Element* pt_get_by_name(PeriodicTable* pt, const char* name) {
    char* lower_name = to_lowercase(name);
    Element* element = (Element*)ht_get(pt->nameTable, lower_name);
    free(lower_name);
    return element;
}

Element* pt_get_by_atomic_number(PeriodicTable* pt, int atomic_number) {
    return (Element*)ht_get_by_atomic_number(pt->atomicTable, atomic_number);
}

// New function to insert an element into the periodic table
void pt_insert_element(PeriodicTable* pt, Element* element) {
    char* lower_symbol = to_lowercase(element->symbol);
    char* lower_name = to_lowercase(element->name);
    
    ht_insert(pt->symbolTable, lower_symbol, element);
    ht_insert(pt->nameTable, lower_name, element);
    ht_insert_by_atomic_number(pt->atomicTable, element->atomic_number, element);
    
    free(lower_symbol);
    free(lower_name);
}

