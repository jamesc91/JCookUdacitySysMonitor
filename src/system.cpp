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

// TODO: Return the system's kernel identifier (string)
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

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    
    string key, value;
    string line;

    const char space = ' ';
    const char quote = '"';
    const char uscore = '_';
    const char equals = '=';
    const char dbl_space = '  ';
    //const char nothing = '\0';

    std::ifstream stream(os_release_);
    
    if(stream.is_open()){
        
        while(std::getline(stream, line)){
            
            std::replace(line.begin(), line.end(), space, uscore);
            std::replace(line.begin(), line.end(), equals, space);
            std::replace(line.begin(), line.end(), quote, uscore);
            std::istringstream linestream(line);
            //std::cout<<"line: "<<line<<std::endl;
            while(linestream >> key >> value){
                if(key == "PRETTY_NAME"){
                    
                    std::replace(value.begin(), value.end(), uscore, space);
                    std::replace(value.begin(),value.end(), dbl_space, space);
                    return value;
                }
            }
            
        }
    }
    return value;
    
  
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return 0; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return 0; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return 0; }