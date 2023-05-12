#ifndef SIMOS
#define SIMOS
#include "FileReadRequest.h"
#include "MemoryItem.h"
#include "Process.cpp"
#include "HardDisk.cpp"
#include <iostream>
#include <queue>
#include <vector>


class SimOS{
public:
    SimOS(int numberOfDisks = 0, unsigned long long amountOfRam = 0);
    bool NewProcess(int priority, unsigned long long size);
    bool SimFork();
    void SimExit();
    void SimWait();
    void DiskReadRequest(int diskNumber, std::string fileName);
    void DiskJobCompleted(int diskNumber);
    int GetCPU();
    std::vector<int> GetReadyQueue();
    MemoryUsage GetMemory();
    FileReadRequest GetDisk(int diskNumber);
    std::queue<FileReadRequest> GetDiskQueue(int diskNumber);
    void PrintVector();
    Process FindProcess(int pid);
    void NextProcessUp();

private:
    int pid = 0;
    Process currentlyRunningProcess{0,0,0};
    int currentlyRunningProcessPID = 0;
    struct less_than_priority{
        inline bool operator() (const Process& process1, const Process& process2){
            return (process1.processPriority > process2.processPriority);
        }
    };
    std::vector<Process> test;
    std::vector<HardDisk> HardDisks;
};

#include "SimOs.cpp"
#endif