#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function


std::string Format::Pad(std::string s, char c) {
  s.insert(s.begin(), 2 - s.size(), c);
  return s;
}

string Format::ElapsedTime(long time) { 
    int hours = time / (60 * 60);
  int minutes = (time / 60) % 60;
  long seconds = time % 60;
  return std::string(Format::Pad(std::to_string(hours), '0') + ":" +
                     Format::Pad(std::to_string(minutes), '0') + ":" +
                     Format::Pad(std::to_string(seconds), '0'));
}