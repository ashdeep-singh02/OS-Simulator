#ifndef PROCESS
#define PROCESS
#include <vector>

class Process{
public:
    int processPriority;
    int processSize;
    int processPid;
    Process(int priority, unsigned long long size, int pid);;
    Process();
    void setChildProcess(int childPID);
    void setParentProcess(int childPID);
    std::vector<int> getChildren();
    int getParent();
    std::vector<Process> getChildrenProcesses();
    void setChildrenProcesses(Process child);
private:
    std::vector<int> childPIDs;
    std::vector<Process> childrenProcesses;
    int parentPIDs = -1;
};

#endif
