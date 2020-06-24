#include "processor.h"

using std::string;

Processor::Processor(){
    cpu_fields last = init_cpu();
    user_prev_ = last.user;
    nice_prev_ = last.nice;
    system_prev_ = last.system;
    idle_prev_ = last.idle;
    iowait_prev_ = last.iowait;
    irq_prev_ = last.irq;
    softirq_prev_ = last.softirq;
    steal_prev_ = last.steal;
};

Processor::cpu_fields Processor::init_cpu(void){

    string line, key;
    
    cpu_fields cpu_out;


    std::ifstream stream(proc_stat_);

    if(stream.is_open()){

        while(std::getline(stream, line)){

            std::istringstream sstream(line);

            while(sstream >> key){
                
                if(key == "cpu"){
                    sstream >> cpu_out.user;
                    sstream >> cpu_out.nice;
                    sstream >> cpu_out.system;
                    sstream >> cpu_out.idle;
                    sstream >> cpu_out.iowait;
                    sstream >> cpu_out.irq;
                    sstream >> cpu_out.softirq;
                    sstream >> cpu_out.steal;

                    return cpu_out; 
                    break;
                }
            }
        }
    }
    return cpu_out;
}
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 

    string line, key;
    
    float user, nice, system, idle, iowait, irq, softirq, steal;

    float prev_Idle, curr_Idle, prev_non_idle, curr_non_idle, prev_total, curr_total, total, idle_total;

    std::ifstream stream(proc_stat_);

    if(stream.is_open()){

        while(std::getline(stream, line)){

            std::istringstream sstream(line);
            
            while(sstream >> key){
                
                if(key == "cpu"){
                    sstream >> user;
                    sstream >> nice;
                    sstream >> system;
                    sstream >> idle;
                    sstream >> iowait;
                    sstream >> irq;
                    sstream >> softirq;
                    sstream >> steal;
                    
                    //CPU usage calc
                    prev_Idle = idle_prev_ + iowait_prev_;
                    curr_Idle = idle + iowait;
                    
                    prev_non_idle = user_prev_ + nice_prev_ + system_prev_ + irq_prev_ + softirq_prev_ + steal_prev_;
                    curr_non_idle = user + nice + system + irq + softirq + steal;
                    
                    prev_total = prev_Idle + prev_non_idle;
                    curr_total = curr_Idle + curr_non_idle;
                    
                    total = curr_total - prev_total;
                    idle_total = curr_Idle - prev_Idle;
                    
                    //set current values to prev
                    user_prev_ = user;
                    nice_prev_ = nice;
                    system_prev_ = system;
                    idle_prev_ = idle;
                    iowait_prev_ = iowait;
                    irq_prev_ = irq;
                    softirq_prev_ = softirq;
                    steal_prev_ = steal;

                    break;    
                }
            }   
        }
    }
    float ret = (total - idle_total) / total;
    if(total <= 0){
        return 0.0f;
    }
    return ret; 
}