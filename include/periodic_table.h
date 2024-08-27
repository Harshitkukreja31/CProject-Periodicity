//
// Created by harsh on 25-08-2024.
//



#ifndef PERIODIC_TABLE_H
#define PERIODIC_TABLE_H

#include "hashtable.h"

// Define the Element structure
typedef struct {
    char symbol[3];
    char name[50];
    int atomic_number;
    float atomic_weight;
} Element;

// Define the PeriodicTable structure
typedef struct {
    HashTable* symbolTable;  // For searching by symbol
    HashTable* nameTable;    // For searching by full name
    HashTable* atomicTable;  // For searching by atomic number
} PeriodicTable;

// Function prototypes
PeriodicTable* create_periodic_table();
void free_periodic_table(PeriodicTable* pt);
Element* pt_get_by_symbol(PeriodicTable* pt, const char* symbol);
Element* pt_get_by_name(PeriodicTable* pt, const char* name);
Element* pt_get_by_atomic_number(PeriodicTable* pt, int atomic_number);

#endif // PERIODIC_TABLE_H


