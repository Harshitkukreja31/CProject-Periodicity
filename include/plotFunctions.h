// #ifndef PLOT_FUNCTIONS_H
// #define PLOT_FUNCTIONS_H

// #include "periodic_table.h"

// void plot_ionization_energy(Element** elements, int count,int display_option);



// #endif

#ifndef PLOT_FUNCTIONS_H
#define PLOT_FUNCTIONS_H

#include "periodic_table.h"

// Function to get property name
const char* get_property_name_plot(int property_index);

// Function to get property value
double get_property_value(Element* element, int property_index);

// Function to get property unit
const char* get_property_unit(int property_index);

// Function to generate data file for gnuplot
void generate_data_file(Element** elements, int count, const char* filename, int property_index);

// Function to generate gnuplot script
void generate_gnuplot_script(const char* data_filename, const char* script_filename, const char* output_filename, int display_option, int property_index);

// Function to execute gnuplot
void execute_gnuplot(const char* script_filename);

// Main plotting function for any property
void plot_property(Element** elements, int count, int display_option, int property_index);

// Function to plot ionization energy (kept for backward compatibility)
void plot_ionization_energy(Element** elements, int count, int display_option);

// Function to plot all properties
void plot_all_properties(Element** elements, int count, int display_option);



#endif // PLOT_FUNCTIONS_H