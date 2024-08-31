#include "csv_reader.h"
#include "periodic_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to trim leading and trailing spaces from a string
char* trim_whitespace(char* str) {
    char* end;
    // Trim leading space
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0)  // All spaces?
        return str;
    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    // Write new null terminator character
    end[1] = '\0';
    return str;
}

PeriodicTable* read_elements_from_csv(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    PeriodicTable* pt = create_periodic_table();
    if (!pt) {
        printf("Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    char line[1024];
    // Skip header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        Element* element = malloc(sizeof(Element));
        if (!element) {
            printf("Memory allocation error\n");
            fclose(file);
            free_periodic_table(pt);
            return NULL;
        }

        // Parse the CSV line
        char* token = strtok(line, ",");
        element->atomic_number = atoi(trim_whitespace(token));

        token = strtok(NULL, ",");
        strncpy(element->symbol, trim_whitespace(token), sizeof(element->symbol));
        element->symbol[sizeof(element->symbol) - 1] = '\0';  // Ensure null termination

        token = strtok(NULL, ",");
        strncpy(element->name, trim_whitespace(token), sizeof(element->name));
        element->name[sizeof(element->name) - 1] = '\0';  // Ensure null termination

        token = strtok(NULL, ",");
        element->atomic_weight = atof(trim_whitespace(token));

        

        
        // Debugging line
        printf("Adding element: %s, %s, %d, %.4f\n", element->symbol, element->name, element->atomic_number, element->atomic_weight);

        // Use the new pt_insert_element function to add the element to the periodic table
        pt_insert_element(pt, element);
    }

    fclose(file);
    return pt;
}