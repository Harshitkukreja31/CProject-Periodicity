#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "periodic_table.h"
#include "csv_reader.h"

#include <unistd.h>


#define MAX_INPUT_LENGTH 100





int main() {
    PeriodicTable* pt = read_elements_from_csv("data.csv");
   
    char cwd[1024];
   
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    }
    
    if (!pt) {
        fprintf(stderr, "Failed to load periodic table data.\n");
        return 1;
    }
    
    while (1) {
        printf("Search by:\n1. Symbol\n2. Full Name\n3. Atomic Number\n4. Quit\n");
        int choice;
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        if (choice == 4) {
            break;
        }
        
        if (choice == 1) {
            char symbol[3];
            printf("Enter element symbol: ");
            scanf("%2s", symbol);
            to_lowercase(symbol);  // Convert to lowercase
            Element* element = pt_get_by_symbol(pt, symbol);
            if (element) {
                printf("Element: %s\n", element->name);
                printf("Symbol: %s\n", element->symbol);
                printf("Atomic Number: %d\n", element->atomic_number);
                printf("Atomic Weight: %.4f\n", element->atomic_weight);

            } else {
                printf("Element not found.\n");
            }
        } else if (choice == 2) {
            char name[50];
            printf("Enter element name: ");
            scanf(" %[^\n]", name); // Read full line including spaces
            to_lowercase(name);  // Convert to lowercase
            Element* element = pt_get_by_name(pt, name);
            if (element) {
                printf("Element: %s\n", element->name);
                printf("Symbol: %s\n", element->symbol);
                printf("Atomic Number: %d\n", element->atomic_number);
                printf("Atomic Weight: %.4f\n", element->atomic_weight);

            } else {
                printf("Element not found.\n");
            }
        } else if (choice == 3) {
            int atomic_number;
            printf("Enter atomic number: ");
            if (scanf("%d", &atomic_number) != 1) {
                // If the input is not an integer, handle the error
                printf("Invalid input. Please enter a valid number.\n");
                while (getchar() != '\n'); // Clear the input buffer
                continue;
            }
            Element* element = pt_get_by_atomic_number(pt, atomic_number);
            if (element) {
                printf("Element: %s\n", element->name);
                printf("Symbol: %s\n", element->symbol);
                printf("Atomic Number: %d\n", element->atomic_number);
                printf("Atomic Weight: %.4f\n", element->atomic_weight);

            } else {
                printf("Element not found.\n");
            }
        }
        if (choice == 4) {
        else {
            printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    }
    
    free_periodic_table(pt);
    return 0;
}