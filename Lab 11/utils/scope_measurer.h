#ifndef __SCOPE_MEASURER_H__
#define __SCOPE_MEASURER_H__

#include <ctime>

class ScopeMeasurer {
public:
    ScopeMeasurer(void);
    void startMeasure(void);
    void finishMeasure(void);

    double getTotalTime(void) const;
    double getAverageTime(void) const;
    size_t getCallCount(void) const;

private:
    bool is_measuring;
    clock_t timepoint;
    double total_time_elapsed;
    size_t measurements_count;
};


#endif
