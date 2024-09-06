#define TESTING
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "../include/periodic_table.h"
#include "../include/csv_reader.h"
#include "../include/trends.h"
#include "../include/plotFunctions.h"

PeriodicTable* pt;

void setup() {
    pt = read_elements_from_csv("test_data.csv");
    assert(pt != NULL);  // Ensure periodic table is successfully loaded
}

void teardown() {
    free_periodic_table(pt);
}

void test_periodic_table_creation() {
    assert(pt != NULL);
    assert(pt->symbolTable != NULL);
    assert(pt->nameTable != NULL);
    assert(pt->atomicTable != NULL);
}

void test_element_insertion_and_retrieval() {
    Element test_element = {
        .atomic_number = 1,
        .symbol = "H",
        .name = "Hydrogen",
        .atomic_weight = 1.008,
        .periodNo = 1,
        .groupNo = 1,
        .electronegativity = 2.20,
        .electronAffinity = 72,
        .ionizationEnergy = 1312,
        .atomicRadius = 53,
        .meltingPoint = 14,
        .boilingPoint = 20,
    };
    
    pt_insert_element(pt, &test_element);
    
    Element* retrieved = pt_get_by_symbol(pt, "H");
    assert(retrieved != NULL);
    assert(strcmp(retrieved->name, "Hydrogen") == 0);
    assert(retrieved->atomic_number == 1);
    
    // printf("Expected atomic_weight: %f, Got: %f\n", 1.008, retrieved->atomic_weight);
    // printf("Expected electronegativity: %f, Got: %f\n", 2.20, retrieved->electronegativity);
    // printf("Expected electronAffinity: %d, Got: %d\n", 72, retrieved->electronAffinity);
    // printf("Expected ionizationEnergy: %d, Got: %d\n", 1312, retrieved->ionizationEnergy);
    // printf("Expected atomicRadius: %d, Got: %d\n", 53, retrieved->atomicRadius);
    // printf("Expected meltingPoint: %d, Got: %d\n", 14, retrieved->meltingPoint);
    // printf("Expected boilingPoint: %d, Got: %d\n", 20, retrieved->boilingPoint);
    
    assert(fabs(retrieved->atomic_weight - 1.008) < 0.0001);
    assert(retrieved->periodNo == 1);
    assert(retrieved->groupNo == 1);
    assert(fabs(retrieved->electronegativity - 2.20) < 0.01);
    assert(retrieved->electronAffinity == 72);
    assert(retrieved->ionizationEnergy == 1312);
    assert(retrieved->atomicRadius == 53);
    assert(retrieved->meltingPoint == 14);
    assert(retrieved->boilingPoint == 20);
    
    retrieved = pt_get_by_name(pt, "Hydrogen");
    assert(retrieved != NULL);
    assert(strcmp(retrieved->symbol, "H") == 0);
    
    retrieved = pt_get_by_atomic_number(pt, 1);
    assert(retrieved != NULL);
    assert(fabs(retrieved->atomic_weight - 1.008) < 0.0001);
}
void test_case_insensitive_retrieval() {
    
    
    Element* retrieved = pt_get_by_name(pt, "hYdRoGeN");
    assert(retrieved != NULL);
    assert(strcmp(retrieved->symbol, "H") == 0);
}

void test_non_existent_element() {
    assert(pt_get_by_symbol(pt, "Zz") == NULL);
    assert(pt_get_by_name(pt, "Nonexistium") == NULL);
    assert(pt_get_by_atomic_number(pt, 1000) == NULL);
}

void test_trend_analysis() {
    int count;
    Element** elements = pt_get_elements_sorted_by_property(pt, 1, 10, &count, 0);  // Electronegativity
    assert(elements != NULL);
    assert(count == 10);
    
    // Check if sorted correctly (ascending order)
    for (int i = 1; i < count; i++) {
        assert(elements[i]->electronegativity >= elements[i-1]->electronegativity);
    }
    
    free(elements);
}

void test_trend_analysis_empty_range() {
    int count;
    Element** elements = pt_get_elements_sorted_by_property(pt, 1000, 1001, &count, 0);
    assert(elements == NULL);
    
}

void test_plot_generation() {
    int count;
    Element** elements = pt_get_elements_sorted_by_property(pt, 1, 10, &count, 0);
    assert(elements != NULL);
    
    plot_property(elements, count, 2, 0);  // Save as PNG
    
    // Check if the file was created
    FILE* file = fopen("Paulingscale_plot.png", "r");
    if (file == NULL) {
        perror("Error opening Paulingscale_plot.png");
        
    } else {
        fclose(file);
    }
    
    free(elements);
}
void test_csv_reader_invalid_file() {
    PeriodicTable* result = read_elements_from_csv("non_existent_file.csv");
    assert(result == NULL);  // Invalid file should return NULL
}

void test_to_lowercase() {
    char* result = to_lowercase("HeLiUm");
    assert(strcmp(result, "helium") == 0);
    free(result);
    
    result = to_lowercase("12345");
    assert(strcmp(result, "12345") == 0);
    free(result);
    
    result = to_lowercase("");
    assert(strcmp(result, "") == 0);
    free(result);
}

void run_all_tests() {
    setup();
    
    test_periodic_table_creation();
    test_element_insertion_and_retrieval();
    test_case_insensitive_retrieval();
    test_non_existent_element();
    test_trend_analysis();
    test_trend_analysis_empty_range();
    test_plot_generation();
    test_csv_reader_invalid_file();
    test_to_lowercase();
    
    teardown();
    printf("All tests passed successfully!\n");
}

int main() {
    run_all_tests();
    
    return 0;
}
