#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
std::string ElapsedTime(long times);  // TODO: See src/format.cpp
std::string Pad(std::string s, char c);
};                                    // namespace Format

#endif