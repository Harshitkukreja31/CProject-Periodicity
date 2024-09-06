#include <stdio.h>
#include <stdlib.h>
#include "trends.h"

// Move current_property_index to file scope
static int current_property_index = 0;

// Comparison function for qsort
static int compare_elements(const void* a, const void* b, int property_index) {
    Element* elem1 = *(Element**)a;
    Element* elem2 = *(Element**)b;
    double value1, value2;

    switch (property_index) {
        case 0: value1 = elem1->electronegativity; value2 = elem2->electronegativity; break;
        case 1: value1 = elem1->electronAffinity; value2 = elem2->electronAffinity; break;
        case 2: value1 = elem1->atomicRadius; value2 = elem2->atomicRadius; break;
        case 3: value1 = elem1->meltingPoint; value2 = elem2->meltingPoint; break;
        case 4: value1 = elem1->boilingPoint; value2 = elem2->boilingPoint; break;
        case 5: value1 = elem1->ionizationEnergy; value2 = elem2->ionizationEnergy; break;
        default: return 0;
    }

    if (value1 == 100000 && value2 == 100000) return 0;
    if (value1 == 100000) return 1;
    if (value2 == 100000) return -1;
    return (value1 < value2) ? -1 : (value1 > value2 ? 1 : 0);
}

static int compare_wrapper(const void* a, const void* b) {
    return compare_elements(a, b, current_property_index);
}



static Element** pt_get_elements_in_range(PeriodicTable* pt, int start, int end, int* count) {
    if(start<0 || start>118 || end<0 || end>118){
        return NULL;
    }
    *count = 0;
    Element** elements = malloc(sizeof(Element*) * (end - start + 1));
    if (!elements) return NULL;

    for (int i = start; i <= end; i++) {
        Element* element = pt_get_by_atomic_number(pt, i);
        if (element) {
            elements[*count] = element;
            (*count)++;
        }
    }

    return elements;
}



Element** pt_get_elements_sorted_by_property(PeriodicTable* pt, int start, int end, int* count, int property_index) {
    Element** elements = pt_get_elements_in_range(pt, start, end, count);
    if (!elements) return NULL;
    current_property_index = property_index;
    qsort(elements, *count, sizeof(Element*), compare_wrapper);
    return elements;
}

void pt_analyze_trend(Element** elements, int count, int property_index) {
    if (count == 0) {
        printf("No elements to analyze.\n");
        return;
    }
    
    printf("Elements sorted by %s:\n", get_property_name(property_index));
    for (int i = 0; i < count; i++) {
        printf("%s (Atomic number: %d, %s: ", 
               elements[i]->name, 
               elements[i]->atomic_number,
               get_property_name(property_index));
        
        double value;
        switch (property_index) {
            case 0: value = elements[i]->electronegativity; break;
            case 1: value = elements[i]->electronAffinity; break;
            case 2: value = elements[i]->atomicRadius; break;
            case 3: value = elements[i]->meltingPoint; break;
            case 4: value = elements[i]->boilingPoint; break;
            case 5: value = elements[i]->ionizationEnergy; break;
            default: value = 100000; // This should never happen
        }
        
        if (value == 100000) { //assigned 100000 to null in csv file
            printf("Data unavailable");
        } else {
            if (property_index == 0) {
                printf("%.2f", value); // Electronegativity is typically shown with decimal places
            } else {
                printf("%.0f", value); // Other properties are typically whole numbers
            }
        }
        
        printf(")\n");
    }
}

void pt_analyze_all_trends(PeriodicTable* pt, int start, int end) {
    int count;
    Element** elements;
    for (int property_index = 0; property_index <= 5; property_index++) {
        elements = pt_get_elements_sorted_by_property(pt, start, end, &count, property_index);
        if (elements) {
            pt_analyze_trend(elements, count, property_index);
            free(elements);
            printf("\n");
        } else {
            printf("Failed to analyze trend for %s\n\n", get_property_name(property_index));
        }
    }
}

//switch case to decode property to analyze

const char* get_property_name(int property_index) {
    switch (property_index) {
        case 0: return "Electronegativity";
        case 1: return "Electron Affinity";
        case 2: return "Atomic Radius";
        case 3: return "Melting Point";
        case 4: return "Boiling Point";
        case 5: return "Ionization Energy";
        default: return "Unknown Property";
    }
}