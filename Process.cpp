#include <iostream>
#include "Process.h"
 

Process::Process(int priority, unsigned long long size, int pid){
    processPriority = priority;
    processSize = size;
    processPid = pid;
};

Process::Process() : processPid(0), processPriority(0), processSize(0){}

void Process::setChildProcess(int childPID){
    childPIDs.push_back(childPID);
}
void Process::setParentProcess(int parentPID){
    parentPIDs = parentPID;
}

std::vector<int> Process::getChildren(){
    return childPIDs;
}
int Process::getParent(){
    return parentPIDs;
}
void Process::setChildrenProcesses(Process child){
    childrenProcesses.push_back(child);
}
std::vector<Process> Process::getChildrenProcesses(){
    return childrenProcesses;
}