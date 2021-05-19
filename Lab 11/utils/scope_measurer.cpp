#include <stdio.h>
#include "scope_measurer.h"

ScopeMeasurer::ScopeMeasurer(void) {
    is_measuring = false;
    timepoint = 0;
    total_time_elapsed = 0.0;
    measurements_count = 0;
}

void ScopeMeasurer::startMeasure(void) {
    if (is_measuring) {
        printf("[warning] is already measuring\n");
        return;
    }
    is_measuring = true;
    timepoint = clock();
}

void ScopeMeasurer::finishMeasure(void) {
    if (!is_measuring) {
        printf("[warning] is not already measuring\n");
        return;
    }
    double elapsed_time = double(clock() - timepoint) / CLOCKS_PER_SEC;
    total_time_elapsed += elapsed_time;
    measurements_count += 1;
    is_measuring = false;
}

size_t ScopeMeasurer::getCallCount() const {
    return measurements_count;
}

double ScopeMeasurer::getTotalTime(void) const {
    return total_time_elapsed;
}

double ScopeMeasurer::getAverageTime(void) const {
    return getTotalTime() / getCallCount();
}
