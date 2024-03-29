#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os,version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.emplace_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  
  string memTotal,kb,memFree;
  float memTot,memFr;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >>memTotal >>memTot>>kb;
    std::getline(stream, line);
    std::istringstream linestream1(line);
    linestream1 >> memFree >> memFr >>kb;
  }
  // std::cout<<memFr/memTot << std::endl;
  float result=(memTot-memFr)/memTot;
  return result;
  // return MemoryUtilization; }
}

long LinuxParser::UpTime() {
  
  long upTim1,upTim2;
  string line,DOT;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >>upTim1>>upTim2;
  }
  
  return long(upTim1+upTim2); }

// TODO: Read and return the number of jiffies for the system
float LinuxParser::Jiffies() { 
   
                                   return ActiveJiffies()+IdleJiffies(); }


// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 

    std::string pidS=std::to_string(pid);
int index=0;
  vector<int> myVector;
  long space;
  string line;
    std::ifstream stream(kProcDirectory+pidS+kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
   std::istringstream linestream(line);
    while (linestream >> space ) {

      if(index ==22){
        break;}

     
        index++;
      }
  }

  return space;}



// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  int index=0;
  vector<int> myVector;
  string space;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
   std::istringstream linestream(line);
    while (linestream >> space ) {
      if(index ==10){
        break;}
      if(index>0){
        myVector.push_back(atol(space.c_str()));
      }
        index++;
      }
    }
    
  
  long total =myVector[0]+myVector[1]+myVector[2]+myVector[5]+myVector[6]+myVector[7];
  return total;}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {   
  long user,nice,system1,idle,iowait,irq,softirq,steal;
  string CPU,line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
   std::istringstream linestream(line);
          linestream >>CPU>>user>>nice>>system1>>idle>>iowait>>irq>>softirq>>steal;
    
  }
        return idle+iowait; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  
  string line,CPU;
  string user,nice,system1,idle,iowait,irq,softirq,steal;
  
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
   std::istringstream linestream(line);
          linestream >>CPU>>user>>nice>>system1>>idle>>iowait>>irq>>softirq>>steal;
    
  }
  vector<string> myVector{user ,nice ,system1 ,idle,iowait,irq,softirq,steal};

  return myVector;
  }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
 
string line,process;
int total;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
        while (std::getline(stream, line)) {
      std::istringstream linestream(line);
          linestream >>process;
      if(process=="processes")
        linestream>>total;
    }
  }
  
  return total;
 }

// TODO: Read and return the number of running processes

int LinuxParser::RunningProcesses() { 

string line,process;
int total;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
        while (std::getline(stream, line)) {
      std::istringstream linestream(line);
          linestream >>process;
      if(process=="procs_running")
        linestream>>total;
    }
  }
  
  return total;
 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::string pidS=std::to_string(pid),line;
   std::ifstream stream(LinuxParser::kProcDirectory+pidS+LinuxParser::kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
     }
     return line;}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {  
  double size;
  std::string process;
  std::string pidS=std::to_string(pid),line;
    std::ifstream stream(kProcDirectory+pidS+kStatusFilename);
 if (stream.is_open()) {
        while (std::getline(stream, line)) {
      std::istringstream linestream(line);
          linestream >>process;
      if(process=="VmData:"){ //VmData  instead of Vmsize as Udacity greader said it's better
        linestream>>size;
      break;
      }
    }
  }
  size/=1000.0;
string size1=std::to_string(size);
  
size1=size1.substr(0,size1.find(".")+3);  
return	size1; }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {  
  	
  std::string uid,process;
  std::string pidS=std::to_string(pid),line;
    std::ifstream stream(kProcDirectory+pidS+kStatusFilename);
 if (stream.is_open()) {
        while (std::getline(stream, line)) {
      std::istringstream linestream(line);
          linestream >>process;
      if(process=="Uid")
        linestream>>uid;
    }
  }

return uid;}
// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  	std::string name,line,fileuid;
  std::string uid=Uid(pid);
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
        while (std::getline(stream, line)) {
      std::istringstream linestream(line);
          linestream >>name >>fileuid;
      if(fileuid==uid)
       break;
    }}
  name=name.substr(0,name.find(':'));
  return name; }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::UpTime(int pid) {  
  string space;
  int index=1;
    // long one,two,three,four,five;
    std::string pidS=std::to_string(pid),line;
    std::ifstream stream(LinuxParser::kProcDirectory+pidS+LinuxParser::kStatFilename);
  if (stream.is_open()) {
      std::getline(stream,line);
      std::istringstream linestream(line);
      while (linestream >> space ) {
        if(index==22){
        break;
        }
        index++;
      }
    }
      // std
      
      float res=atol(space.c_str())/(sysconf(_SC_CLK_TCK)*1.0);

     return float(res); } 