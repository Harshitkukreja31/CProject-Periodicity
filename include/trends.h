#ifndef TRENDS_H
#define TRENDS_H

#include "periodic_table.h"

// Function prototypes
Element** pt_get_elements_sorted_by_property(PeriodicTable* pt, int start, int end, int* count, int property_index);

void pt_analyze_trend(Element** elements, int count, int property_index);
void pt_analyze_all_trends(PeriodicTable* pt, int start, int end);
const char* get_property_name(int property_index);

#endif // TRENDS_H