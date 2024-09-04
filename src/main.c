#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "periodic_table.h"
#include "csv_reader.h"
#include "plotFunctions.h"
#include "trends.h"


#define MAX_INPUT_LENGTH 100


void printProp(Element* element){
    printf("Element: %s\n", element->name);
    printf("Symbol: %s\n", element->symbol);
    printf("Atomic Number: %d\n", element->atomic_number);
    printf("Atomic Weight: %.4f\n", element->atomic_weight);
    printf("Period Number: %d\n", element->periodNo);
    printf("Group Number: %d\n", element->groupNo);
    printf("Ionization Energy: %d\n", element->ionizationEnergy);
    printf("Electronegativity: %.2f\n", element->electronegativity);
    printf("ElectroAffinity: %d\n", element->electronAffinity);
    printf("Atomic Radius: %d\n", element->atomicRadius);
    printf("Melting Point: %d\n", element->meltingPoint);
    printf("Boiling Point: %d\n", element->boilingPoint);
}


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
        printf("\nMenu Options:\n");
        printf("1. Print Entire periodic table\n");
        printf("2. Search by Full Symbole\n");
        printf("3. Search by Full Name\n");
        printf("4. Search by Atomic Number\n");
        printf("5. Analyze Specific Trend\n");
        printf("6. Analyze All Trends\n");
        printf("7. Quit\n");
        int choice;
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        if (choice == 7) {
            break;
        }
        if(choice==1){
            print_periodic_table(pt);
        }
        else if (choice == 2) {
            char symbol[3];
            printf("Enter element symbol: ");
            scanf("%2s", symbol);
            to_lowercase(symbol);  // Convert to lowercase
            Element* element = pt_get_by_symbol(pt, symbol);
            if (element) {
                printProp(element);
            } else {
                printf("Element not found.\n");
            }
        } else if (choice == 3) {
            char name[50];
            printf("Enter element name: ");
            scanf(" %[^\n]", name); // Read full line including spaces
            to_lowercase(name);  // Convert to lowercase
            Element* element = pt_get_by_name(pt, name);
            if (element) {
                printProp(element);
            } else {
                printf("Element not found.\n");
            }
        } else if (choice == 4) {
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
                printProp(element);
            } else {
                printf("Element not found.\n");
            }
        }

        else if (choice == 5) {
            int start, end, property_choice;
            printf("Enter range of atomic numbers (start end): ");
            scanf("%d %d", &start, &end);
            
            printf("Choose property to analyze:\n");
            printf("1. Electronegativity\n2. Electron Affinity\n3. Atomic Radius\n");
            printf("4. Melting Point\n5. Boiling Point\n6. Ionization Energy\n");
            printf("Enter choice: ");
            scanf("%d", &property_choice);
            
            int property_index = property_choice - 1;
            
            int count;
            Element** elements = pt_get_elements_sorted_by_property(pt, start, end, &count, property_index);
            
            if (elements) {
                pt_analyze_trend(elements, count, property_index);
                free(elements);
            } else {
                printf("Failed to analyze trend.\n");
            }
        }
        else if (choice == 6) {
            int start, end;
            printf("Enter range of atomic numbers (start end): ");
            scanf("%d %d", &start, &end);
            
            pt_analyze_all_trends(pt, start, end);
        }
        


        else {
            printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    }
    
    free_periodic_table(pt);
    return 0;
}