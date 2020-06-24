#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "process.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: See src/system.cpp
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel();               // TODO: See src/system.cpp
  std::string OperatingSystem();      // TODO: See src/system.cpp

  // TODO: Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  const std::string proc_version_{"/proc/version"};
  const std::string proc_meminfo_{"/proc/meminfo"};
  const std::string proc_uptime_{"/proc/uptime"};
  const std::string proc_stat_{"/proc/stat"};
  const std::string os_release_{"/etc/os-release"};
};

#endif