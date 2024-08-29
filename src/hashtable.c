#include <stdlib.h>
#include <string.h>
#include <stdio.h>  // For snprintf
#include "hashtable.h"
#include <ctype.h>



// Hash function to convert a string key into an index within the table size
unsigned int hash(const char* key, size_t table_size) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    // Convert the string to an integer
    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    // Make sure the value is within the range of the table size
    value = value % table_size;

    return value;
}

// Hash function to convert an integer key (like atomic number) into an index within the table size
unsigned int hash_int(int key, size_t table_size) {
    return key % table_size;
}

// Creates a new hash table with a specified size
HashTable* ht_create(size_t size) {
    HashTable* table = malloc(sizeof(HashTable));
    if (!table) return NULL;

    table->size = size;
    table->entries = malloc(sizeof(HashTableEntry*) * size);
    if (!table->entries) {
        free(table);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        table->entries[i] = NULL;
    }

    return table;
}

// Frees the memory allocated for the hash table, including all its entries
void ht_free(HashTable* table) {
    for (size_t i = 0; i < table->size; i++) {
        HashTableEntry* entry = table->entries[i];
        while (entry) {
            HashTableEntry* temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->entries);
    free(table);
}

// Inserts a key-value pair into the hash table
void ht_insert(HashTable* table, const char* key, void* value) {
    unsigned int index = hash(key, table->size);
    HashTableEntry* new_entry = malloc(sizeof(HashTableEntry));
    if (!new_entry) return;

    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = table->entries[index];
    table->entries[index] = new_entry;
}




// Retrieves a value from the hash table using a string key
void* ht_get(HashTable* table, const char* key) {
    unsigned int index = hash(key, table->size);
    HashTableEntry* entry = table->entries[index];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}





// Inserts a value into the hash table using an integer key (for atomic numbers)
void ht_insert_by_atomic_number(HashTable* table, int atomic_number, void* value) {
    unsigned int index = hash_int(atomic_number, table->size);
    HashTableEntry* new_entry = malloc(sizeof(HashTableEntry));
    if (!new_entry) return;

    // Create a key based on the atomic number
    char key[16];
    snprintf(key, sizeof(key), "%d", atomic_number);

    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = table->entries[index];
    table->entries[index] = new_entry;
}

// Retrieves a value from the hash table using an integer key (for atomic numbers)
void* ht_get_by_atomic_number(HashTable* table, int atomic_number) {
    unsigned int index = hash_int(atomic_number, table->size);
    HashTableEntry* entry = table->entries[index];

    // Create a key based on the atomic number
    char key[16];
    snprintf(key, sizeof(key), "%d", atomic_number);

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

