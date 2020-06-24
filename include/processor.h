#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Processor {
 public:
    Processor();

    struct cpu_fields{
        float user;
        float nice;
        float system;
        float idle;
        float iowait;
        float irq;
        float softirq;
        float steal;
    };

    float Utilization();  // TODO: See src/processor.cpp
    cpu_fields init_cpu(void);
    

  // TODO: Declare any necessary private members
 private:
    float user_prev_;
    float nice_prev_;
    float system_prev_;
    float idle_prev_;
    float iowait_prev_;
    float irq_prev_;
    float softirq_prev_;
    float steal_prev_;
    const std::string proc_stat_{"/proc/stat"};
};

#endif