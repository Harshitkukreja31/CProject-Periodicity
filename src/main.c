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

void printProp(Element *element)
{
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


#ifndef TESTING
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
        printf("2. Search by Full Symbol\n");
        printf("3. Search by Full Name\n");
        printf("4. Search by Atomic Number\n");
        printf("5. Analyze Specific Trend\n");
        printf("6. Analyze All Trends\n");
        printf("7. Plot Specific Trend\n");
        printf("8. Quit\n");
        
        int choice;
        do {
            printf("Enter choice: ");
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n'); // Clear input buffer
            }
        } while (choice < 1 || choice > 8);
        
        if (choice == 8) {
            break;
        }
        
        if (choice == 1) {
            print_periodic_table(pt);
        } else if (choice == 2) {
            char symbol[3];
            printf("Enter element symbol: ");
            scanf("%2s", symbol);
            while (getchar() != '\n'); // Clear input buffer
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
            while (getchar() != '\n'); // Clear input buffer
            to_lowercase(name);  // Convert to lowercase
            Element* element = pt_get_by_name(pt, name);
            if (element) {
                printProp(element);
            } else {
                printf("Element not found.\n");
            }
        } else if (choice == 4) {
            int atomic_number;
            do {
                printf("Enter atomic number: ");
                if (scanf("%d", &atomic_number) != 1) {
                    
                    while (getchar() != '\n'); // Clear the input buffer
                }
                if(atomic_number>118 || atomic_number<1){
                    printf("Invalid input. Please enter a valid number.\n");
                }
            } while (atomic_number < 1 || atomic_number > 118);
            
            Element* element = pt_get_by_atomic_number(pt, atomic_number);
            if (element) {
                printProp(element);
            } else {
                printf("Element not found.\n");
            }
        } else if (choice == 5) {
            int start, end, property_choice;
            do {
                printf("Enter range of atomic numbers (start end): ");
                if (scanf("%d %d", &start, &end) != 2) {
                    
                    while (getchar() != '\n'); // Clear the input buffer
                }
                if(start < 1 || start > 118 || end < 1 || end > 118 || start > end){
                    printf("Invalid input. Please enter a valid number.\n");
                }
            } while (start < 1 || start > 118 || end < 1 || end > 118 || start > end);
            
            do {
                printf("Choose property to analyze:\n");
                printf("1. Electronegativity\n2. Electron Affinity\n3. Atomic Radius\n");
                printf("4. Melting Point\n5. Boiling Point\n6. Ionization Energy\n");
                printf("Enter choice: ");
                if (scanf("%d", &property_choice) != 1) {
                    
                    while (getchar() != '\n'); // Clear the input buffer
                }
                if(property_choice < 1 || property_choice > 6){
                    printf("Invalid choice.\n");
                }
            } while (property_choice < 1 || property_choice > 6);
            
            int property_index = property_choice - 1;
            
            int count;
            Element** elements = pt_get_elements_sorted_by_property(pt, start, end, &count, property_index);
            
            if (elements) {
                pt_analyze_trend(elements, count, property_index);
                free(elements);
            } else {
                printf("Failed to analyze trend.\n");
            }
        } else if (choice == 6) {
            int start, end;
            int valid_input;
            do {
                printf("Enter range of atomic numbers (start end): ");
                valid_input = scanf("%d %d", &start, &end);
                if (valid_input != 2) {
                    printf("Invalid input. Please enter two valid numbers.\n");
                    // Clear the input buffer
                    while (getchar() != '\n');
                    // Reset start and end to ensure the loop continues
                    start = end = 0;
                    } 
                    else if (start < 1 || start > 118 || end < 1 || end > 118 || start > end) {
                        printf("Invalid range. Please enter valid numbers between 1 and 118, with start <= end.\n");
                    }
            } while (valid_input != 2 || start < 1 || start > 118 || end < 1 || end > 118 || start > end);
            
            pt_analyze_all_trends(pt, start, end);
        } else if (choice == 7) {
            int start, end, property_choice, display_option;
            do {
                printf("Enter range of atomic numbers (start end): ");
                if (scanf("%d %d", &start, &end) != 2) {
                    
                    while (getchar() != '\n'); // Clear the input buffer
                }
                if(start < 1 || start > 118 || end < 1 || end > 118 || start > end){
                    printf("Invalid input. Please enter valid numbers.\n");
                }
            } while (start < 1 || start > 118 || end < 1 || end > 118 || start > end);

            do {
                printf("Choose property to plot:\n");
                printf("1. Electronegativity\n2. Electron Affinity\n3. Atomic Radius\n");
                printf("4. Melting Point\n5. Boiling Point\n6. Ionization Energy\n");
                printf("Enter choice: ");
                if (scanf("%d", &property_choice) != 1) {
                   
                    while (getchar() != '\n'); // Clear the input buffer
                }
                if(property_choice < 1 || property_choice > 6){
                    printf("Invalid choice.\n");
                }
            } while (property_choice < 1 || property_choice > 6);
            
            do {
                printf("Choose display option:\n");
                printf("1. Display in pop-up window\n");
                printf("2. Save as PNG file\n");
                printf("Enter your choice (1 or 2): ");
                if (scanf("%d", &display_option) != 1) {
                
                    while (getchar() != '\n'); // Clear the input buffer
                }
                if(display_option < 1 || display_option > 2){
                    printf("Invalid choice.\n");
                }
            } while (display_option < 1 || display_option > 2);
            
            int property_index = property_choice - 1;
            int count;
            Element** elements = pt_get_elements_sorted_by_property(pt, start, end, &count, property_index);
            
            if (elements) {
               plot_property(elements, count, display_option, property_index);
               free(elements);
            } else {
                printf("Failed to plot trend.\n");
            }
        }
        printf("\n");
    }
    
    free_periodic_table(pt);
    return 0;
}
#endif
