#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long times) { 
    int hours_int;
    int minutes_int;
    int seconds_int;
    int centiseconds;

    const int cs_per_hr = 360000;
    const int cs_per_min = 6000;
    const int cs_per_sec = 100;

    hours_int = times / cs_per_hr;
    minutes_int = (times % cs_per_hr) / cs_per_min;
    seconds_int = (times % cs_per_min) / cs_per_sec;
    centiseconds = (times % cs_per_sec);

    if(centiseconds >= 50){
        seconds_int +=1;
    }

    std::string hours = std::to_string(hours_int);
    std::string minutes = std::to_string(minutes_int);
    std::string seconds = std::to_string(seconds_int);
    
    std::string uptime = hours + ":" + minutes + ":" + seconds;

    return uptime; 
}