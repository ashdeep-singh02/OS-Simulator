#ifndef PROCESS
#define PROCESS
#include "SimOs.h"
#include <iostream>

class Process{
public:
    int processPriority;
    int processSize;
    int processPid;
    Process(int priority, unsigned long long size, int pid){
        processPriority = priority;
        processSize = size;
        processPid = pid;
    };
    Process() : processPid(0), processPriority(0), processSize(0){}
};

#endif