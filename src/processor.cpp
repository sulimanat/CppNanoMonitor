#include "processor.h"
#include <vector>
#include "linux_parser.h"
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<std::string> cpuUt=LinuxParser::CpuUtilization();

    float total=0,midTot;
    
    for(auto x:cpuUt){
        total+=atol(x.c_str());
    }
    midTot=atol(cpuUt[3].c_str())+atol(cpuUt[4].c_str());

    midTot=total-midTot;
    float result =midTot/total;
    return result;
     }