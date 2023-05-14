#ifndef HARDDISK
#define HARDDISK
#include <iostream>
#include <vector>
#include "Process.h"
#include "FileReadRequest.h"

class HardDisk{
public:
    HardDisk();
    void NewProcessRequestingDiskRead(Process ProcessReq, std::string fileToRead);
    bool DiskIsNotRunning();
    int GetPidOfRunningProcess();
    std::string GetFileBeingRead();
    std::vector<FileReadRequest> ProcessInsideDiskQueue();
    FileReadRequest ProcessReadingDisk();
    void LeaveDisk();
    Process GetProcessReadingDisk();

// private:
    Process runningProccess;
    std::string currentFile;
    // std::queue<FileReadRequest> diskQueue;
    std::vector<std::pair<Process, std::string>> diskQueue;
};

#endif