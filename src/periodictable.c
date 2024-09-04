#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "periodic_table.h"
#include "hashtable.h"

#define MAX_ROWS 10
#define MAX_COLS 32 

// Function to convert a string to lowercase
char* to_lowercase(const char* str) {
    char* lower_str = strdup(str);
    if (!lower_str) return NULL; // Check for memory allocation failure
    for (int i = 0; lower_str[i]; i++) {
        lower_str[i] = tolower((unsigned char)lower_str[i]);
    }
    return lower_str;
}

PeriodicTable* create_periodic_table() {
    PeriodicTable* pt = (PeriodicTable*)malloc(sizeof(PeriodicTable));
    if (!pt) return NULL;
    pt->symbolTable = ht_create(128);
    pt->nameTable = ht_create(128);
    pt->atomicTable = ht_create(128);
    if (!pt->symbolTable || !pt->nameTable || !pt->atomicTable) {
        free_periodic_table(pt);  // Free everything if any allocation failed
        return NULL;
    }
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
    if (!lower_symbol) return NULL;
    Element* element = (Element*)ht_get(pt->symbolTable, lower_symbol);
    free(lower_symbol);
    return element;
}

Element* pt_get_by_name(PeriodicTable* pt, const char* name) {
    char* lower_name = to_lowercase(name);
    if (!lower_name) return NULL; 
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
    
    if (lower_symbol && lower_name) {
        ht_insert(pt->symbolTable, lower_symbol, element);
        ht_insert(pt->nameTable, lower_name, element);
        ht_insert_by_atomic_number(pt->atomicTable, element->atomic_number, element);
    }
    
    free(lower_symbol);
    free(lower_name);
}

char table[MAX_ROWS][MAX_COLS][3] = {0};  // 2 chars for symbol + null terminator
void print_periodic_table(PeriodicTable* pt) {
    
    
    // Fill the table with element symbols
    for (int i = 1; i <= 118; i++) {
        Element* elem = pt_get_by_atomic_number(pt, i);
        if (elem) {
            int row = elem->periodNo - 1;
            int col;
            
            if (elem->groupNo == 0) {  // Lanthanides
                row = 7;
                col = (elem->atomic_number - 57) + 2;
            } else if (elem->groupNo == 19) {  // Actinides
                row = 8;
                col = (elem->atomic_number - 89) + 2;
            } else if (elem->periodNo <= 7) {
                col = elem->groupNo - 1;
            } else {
                continue;  // Skip any unexpected elements
            }
            
            if (row < MAX_ROWS && col < MAX_COLS) {
                strncpy(table[row][col], elem->symbol, 2);
                table[row][col][2] = '\0';  // Ensure null-termination
            }
        }
    }
    
    // Print the table
    printf("Periodic Table\n\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (table[i][j][0] != '\0') {
                printf("%-2s ", table[i][j]);
            } else {
                printf("   ");  // 3 spaces for empty cells
            }
            if (j == 1 || j == 16) printf(" ");  // Extra space after He andZ group 2
        }
        printf("\n");
        if (i == 6) printf("\n");  // Extra line before lanthanides
    }
}


