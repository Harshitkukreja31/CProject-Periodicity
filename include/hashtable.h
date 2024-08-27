//
// Created by harsh on 25-08-2024.
//


#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>

// Define the structure for a single hash table entry
typedef struct HashTableEntry {
    char* key;
    void* value;
    struct HashTableEntry* next; // For handling collisions using chaining
} HashTableEntry;

// Define the hash table structure
typedef struct {
    HashTableEntry** entries;
    size_t size;
} HashTable;

// Function prototypes

// Creates a new hash table
HashTable* ht_create(size_t size);

// Frees the memory allocated for the hash table
void ht_free(HashTable* table);

// Inserts a key-value pair into the hash table
void ht_insert(HashTable* table, const char* key, void* value);

// Retrieves a value from the hash table using a key
void* ht_get(HashTable* table, const char* key);

// Inserts an entry into the hash table using an integer key (for atomic number)
void ht_insert_by_atomic_number(HashTable* table, int atomic_number, void* value);

// Retrieves a value from the hash table using an integer key (for atomic number)
void* ht_get_by_atomic_number(HashTable* table, int atomic_number);

// Hash function to convert a string key into an index
unsigned int hash(const char* key, size_t table_size);

// Hash function to convert an integer key into an index
unsigned int hash_int(int key, size_t table_size);

#endif // HASHTABLE_H


