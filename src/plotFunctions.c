
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "periodic_table.h"
#include "plotFunctions.h"

// Function to get property name
const char* get_property_name_plot(int property_index) {
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

// Function to get property value
double get_property_value(Element* element, int property_index) {
    switch (property_index) {
        case 0: return element->electronegativity;
        case 1: return element->electronAffinity;
        case 2: return element->atomicRadius;
        case 3: return element->meltingPoint;
        case 4: return element->boilingPoint;
        case 5: return element->ionizationEnergy;
        default: return 100000; // Invalid property
    }
}

// Function to get property unit
const char* get_property_unit(int property_index) {
    switch (property_index) {
        case 0: return "Pauling scale";
        case 1: return "kJ/mol";
        case 2: return "pm";
        case 3: return "K";
        case 4: return "K";
        case 5: return "kJ/mol";
        default: return "";
    }
}

// Function to generate data file for gnuplot
void generate_data_file(Element** elements, int count, const char* filename, int property_index) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Error opening file for writing\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        double value = get_property_value(elements[i], property_index);
        if (value != 100000) {
            fprintf(fp, "%d %f 0\n", elements[i]->atomic_number, value);
        } else {
            fprintf(fp, "%d 0 1\n", elements[i]->atomic_number);
        }
    }
    
    fclose(fp);
}
// Function to generate gnuplot script
void generate_gnuplot_script(const char* data_filename, const char* script_filename, const char* output_filename, int display_option, int property_index) {
    FILE* fp = fopen(script_filename, "w");
    if (!fp) {
        fprintf(stderr, "Error opening gnuplot script file for writing\n");
        return;
    }
    
    if (display_option == 1) {
        // For pop-up window
        fprintf(fp, "set terminal wxt persist\n");
    } else {
        // For PNG output
        fprintf(fp, "set terminal png\n");
        fprintf(fp, "set output '%s'\n", output_filename);
    }
    
    fprintf(fp, "set title '%s vs Atomic Number'\n", get_property_name_plot(property_index));
    fprintf(fp, "set xlabel 'Atomic Number'\n");
    fprintf(fp, "set ylabel '%s (%s)'\n", get_property_name_plot(property_index), get_property_unit(property_index));
    fprintf(fp, "set key outside\n");
    fprintf(fp, "plot '%s' using 1:2:3 with points pt 7 ps 1.5 lc variable notitle, \\\n", data_filename);
    fprintf(fp, "     '' using 1:2:3 with points pt 7 ps 1.5 lc variable title 'Available Data' if ($3==0), \\\n");
    fprintf(fp, "     '' using 1:2:3 with points pt 7 ps 1.5 lc rgb 'red' title 'Unavailable Data' if ($3==1)\n");
    
    fclose(fp);
}

// Function to execute gnuplot
void execute_gnuplot(const char* script_filename) {
    char command[100];
    snprintf(command, sizeof(command), "gnuplot %s", script_filename);
    system(command);
}

// Main plotting function for any property
void plot_property(Element** elements, int count, int display_option, int property_index) {
    char data_filename[50], script_filename[50], output_filename[50];
    snprintf(data_filename, sizeof(data_filename), "%s_data.txt", get_property_unit(property_index));
    snprintf(script_filename, sizeof(script_filename), "%s_script.gp", get_property_unit(property_index));
    snprintf(output_filename, sizeof(output_filename), "%s_plot.png", get_property_unit(property_index));
    
    generate_data_file(elements, count, data_filename, property_index);
    generate_gnuplot_script(data_filename, script_filename, output_filename, display_option, property_index);
    execute_gnuplot(script_filename);
    
    if (display_option == 1) {
        printf("Plot displayed in a pop-up window.\n");
    } else {
        printf("Plot generated: %s\n", output_filename);
    }
}

// Function to plot ionization energy (kept for backward compatibility)
void plot_ionization_energy(Element** elements, int count, int display_option) {
    plot_property(elements, count, display_option, 5);  // 5 is the index for ionization energy
}

// Function to plot all properties
void plot_all_properties(Element** elements, int count, int display_option) {
    for (int i = 0; i <= 5; i++) {
        plot_property(elements, count, display_option, i);
    }
}