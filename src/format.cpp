#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
   

int minutes = seconds / 60;
seconds = seconds % 60;
int hours = minutes / 60;
minutes = minutes % 60;

string result;
result +=std::to_string(hours)+":"+std::to_string(minutes)+":"+std::to_string(seconds);
    return result; }