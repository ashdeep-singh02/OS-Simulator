// #ifndef HARDDISK
// #define HARDDISK
// #include "SimOS.h"
// #include "Process.cpp"
// #include "FileReadRequest.h"
// #include <iostream>
// #include <vector>

#include "HardDisk.h"

HardDisk::HardDisk(){
    currentFile = "";
}

void HardDisk::NewProcessRequestingDiskRead(Process ProcessReq, std::string fileToRead){
    if(DiskIsNotRunning()){
        runningProccess = ProcessReq;
        currentFile = fileToRead;
    }
    else{
        // std::cout << ProcessReq.processPid << " "<< fileToRead << std::endl;
        diskQueue.push_back(std::pair<Process, std::string>(ProcessReq, fileToRead));
        // std::cout << diskQueue.size() << std::endl;
        // std::cout << diskQueue[0].second << std::endl;
    }
}

bool HardDisk::DiskIsNotRunning(){
    return (runningProccess.processPid == 0);
}

int HardDisk::GetPidOfRunningProcess(){
    return runningProccess.processPid;
}

std::string HardDisk::GetFileBeingRead(){
    return currentFile;
}

std::vector<FileReadRequest> HardDisk::ProcessInsideDiskQueue(){
    std::vector<FileReadRequest> ans;
    // what if queue is empty? 
    for(int i = 0; i < diskQueue.size(); i++){
        FileReadRequest ProcessInQueue{};
        ProcessInQueue.PID = diskQueue[i].first.processPid;
        ProcessInQueue.fileName = diskQueue[i].second;
        ans.push_back(ProcessInQueue);
    }
    return ans;
}

FileReadRequest HardDisk::ProcessReadingDisk(){
    FileReadRequest ReadingProcess{};
    ReadingProcess.PID = GetPidOfRunningProcess();
    ReadingProcess.fileName = GetFileBeingRead();
    return ReadingProcess;
}

void HardDisk::LeaveDisk(){
    if(diskQueue.size() == 0){
        Process EmptyProcess;
        runningProccess = EmptyProcess;
        currentFile = "";
    }
    else{
        runningProccess = diskQueue[0].first;
        currentFile = diskQueue[0].second;
        diskQueue.erase(diskQueue.begin());
    }
}

Process HardDisk::GetProcessReadingDisk(){
    return runningProccess;
}


// class HardDisk{
// public:
    // HardDisk(){
    //     currentFile = "";
    // };

    // void NewProcessRequestingDiskRead(Process ProcessReq, std::string fileToRead){
    //     if(DiskIsNotRunning()){
    //         runningProccess = ProcessReq;
    //         currentFile = fileToRead;
    //     }
    //     else{
    //         // std::cout << ProcessReq.processPid << " "<< fileToRead << std::endl;
    //         diskQueue.push_back(std::pair<Process, std::string>(ProcessReq, fileToRead));
    //         // std::cout << diskQueue.size() << std::endl;
    //         // std::cout << diskQueue[0].second << std::endl;
    //     }
    // }

    // bool DiskIsNotRunning(){
    //     return (runningProccess.processPid == 0);
    // }
    // int GetPidOfRunningProcess(){
    //     return runningProccess.processPid;
    // }
    // std::string GetFileBeingRead(){
    //     return currentFile;
    // }

    // std::vector<FileReadRequest> ProcessInsideDiskQueue(){
    //     std::vector<FileReadRequest> ans;
    //     // what if queue is empty? 
    //     for(int i = 0; i < diskQueue.size(); i++){
    //         FileReadRequest ProcessInQueue{};
    //         ProcessInQueue.PID = diskQueue[i].first.processPid;
    //         ProcessInQueue.fileName = diskQueue[i].second;
    //         ans.push_back(ProcessInQueue);
    //     }
    //     return ans;
    // }

    // FileReadRequest ProcessReadingDisk(){
    //     FileReadRequest ReadingProcess{};
    //     ReadingProcess.PID = GetPidOfRunningProcess();
    //     ReadingProcess.fileName = GetFileBeingRead();
    //     return ReadingProcess;
    // }

    // void LeaveDisk(){
    //     if(diskQueue.size() == 0){
    //         Process EmptyProcess;
    //         runningProccess = EmptyProcess;
    //         currentFile = "";
    //     }
    //     else{
    //         runningProccess = diskQueue[0].first;
    //         currentFile = diskQueue[0].second;
    //         diskQueue.erase(diskQueue.begin());
    //     }
    // }

    // Process GetProcessReadingDisk(){
    //     return runningProccess;
    // }

// private:
//     Process runningProccess;
//     std::string currentFile;
//     std::vector<std::pair<Process, std::string>> diskQueue;
// };

// #endifs