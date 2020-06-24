#include <unistd.h>
#include <cstddef>
#include <set>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// Done, define several strings, input file stream from proc/version. I'm lazy so I didn't make proc directory + version directory
std::string System::Kernel() {   
    string os, kernel;
    string line;
    string version;
    std::ifstream stream(proc_version_);
    
    if(stream.is_open()) {
        
        while(std::getline(stream, line)){ 
            
            std::istringstream linestream(line);
            
            while (linestream >> os >> version >>kernel) {
                
                if (os == "Linux") {
                    
                    return kernel;
                    stream.close();
                }
            }
        } 
    }
    stream.close();
    
    return kernel;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return 0.0; }

// Done, I need to figure out a way to delete the first space in the double space 
std::string System::OperatingSystem() { 
    
    string key, value;
    string line;

    const char space = ' ';
    const char quote = '"';
    const char uscore = '_';
    const char equals = '=';

    std::ifstream stream(os_release_);
    
    if(stream.is_open()){
        
        while(std::getline(stream, line)){
            
            std::replace(line.begin(), line.end(), space, uscore);
            std::replace(line.begin(), line.end(), equals, space);
            std::replace(line.begin(), line.end(), quote, uscore);
            std::istringstream linestream(line);
            
            while(linestream >> key >> value){
                
                if(key == "PRETTY_NAME"){
                    
                    std::replace(value.begin(), value.end(), uscore, space);

                    value.erase(value.begin());
                    return value;
                }
            }    
        }
    }
    return value;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    string line;
    string key;
    int processes;
    std::ifstream stream(proc_stat_);
    
    if(stream.is_open()){

        while(std::getline(stream, line)){

            std::istringstream linestream(line);
            
            while(linestream >> key){
                
                if(key == "procs_running"){
                    
                    linestream >> processes;
                    
                    return processes;
                }
            }
        }
    }
    return 0; 
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    string line;
    string key;
    int processes;
    std::ifstream stream(proc_stat_);
    
    if(stream.is_open()){

        while(std::getline(stream, line)){

            std::istringstream linestream(line);
            
            while(linestream >> key){
                
                if(key == "processes"){
                
                    linestream >> processes;
                    
                    return processes;
                }
            }
        }
    }
    return 0; 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    string line;
    string uptime_s, uptime_dec;
    long int uptime_cs;

    const char space = ' ';
    const char decimal = '.';
    std::ifstream stream(proc_uptime_);
    
    if(stream.is_open()){

        while(std::getline(stream, line)){
            
            std::replace(line.begin(), line.end(), decimal, space);
            std::istringstream linestream(line);
            
            while(linestream >> uptime_s >> uptime_dec){
                
                std::istringstream uptime_centiseconds(uptime_s + uptime_dec);
        
                uptime_centiseconds >> uptime_cs;
                return uptime_cs ;
            }  
        }
    }
    return uptime_cs; 
}