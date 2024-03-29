#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include<iostream>

#include <unistd.h>


#include "linux_parser.h"
#include "process.h"
#include "format.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { 
  return this->pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  float x=LinuxParser::ActiveJiffies(this->pid);
  float y=LinuxParser::UpTime(this->pid);
  float total=x/y;
  return total; }

// TODO: Return the command that generated this process
string Process::Command() { 
     return LinuxParser::Command(this->pid);}

// TODO: Return this process's memory utilization
string Process::Ram() { return  LinuxParser::Ram(pid); }

// TODO: Return the user (name) that generated this process
string Process::User() {
  return LinuxParser::User(this->pid); }

// TODO: Return the age of this process (in seconds)
float  Process::UpTime() { 
  return LinuxParser::UpTime(this->pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  return this->pid<a.pid; }