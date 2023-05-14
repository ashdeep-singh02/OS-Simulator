#ifndef SIMOS
#define SIMOS
#include "FileReadRequest.h"
#include "MemoryItem.h"
#include "Process.h"
#include "HardDisk.h"
#include <iostream>
#include <queue>
#include <vector>

class SimOS{
public:
    SimOS(int numberOfDisks, unsigned long long amountOfRam);
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
    void NextProcessUp();
    bool NewChildProcess(int priority, unsigned long long size);
    void TerminateChildren(Process parentProcess);
    bool AllocateNewProcessInRam(int priority, unsigned long long size);

private:
    int pid = 0;
    Process currentlyRunningProcess{0,0,0};
    unsigned long long amountOfRamAvailable = 0;
    unsigned long long maxRam = 0;
    int currentlyRunningProcessPID = 0;
    struct less_than_priority{
        inline bool operator() (const Process& process1, const Process& process2){
            return (process1.processPriority > process2.processPriority);
        }
    };
    std::vector<Process> readyQueue;
    std::vector<HardDisk> HardDisks;
    std::vector<MemoryItem> RAM;
    std::vector<Process> waitingProcesses;
    std::vector<Process> zombieProcesses;
};

#endif