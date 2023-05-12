#include "SimOs.h"
#include "Process.cpp"
#include <iostream>


SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRam){
    for(int i = 0; i < numberOfDisks; i++){
        HardDisk newHD = HardDisk();
        HardDisks.push_back(newHD);
    }
    // std::cout << "SIZE "<< HardDisks.size() << " " << HardDisks[0].GetPidOfRunningProcess() << std::endl;
}

bool SimOS::NewProcess(int priority, unsigned long long size){
    // std::cout << "NP CALLED " << currentlyRunningProcessPID << std::endl;
    pid++;
    Process P1{priority, size, pid}; //new Process created
    if(currentlyRunningProcessPID != 0){ //process in CPU currently 
        // std::cout << currentlyRunningProcess.processPriority << std::endl;
        // std::cout << "LINE 21 " << P1.processPriority << std::endl;
        if(currentlyRunningProcess.processPriority < P1.processPriority){ //priority of new proc > currProc in CPU
            test.push_back(currentlyRunningProcess); //remove currProc from CPU; add to Priority Queue
            currentlyRunningProcess = P1; //new proc now running
            currentlyRunningProcessPID = P1.processPid;
        }
        else{
            test.push_back(P1);
        }
    }
    else if(currentlyRunningProcessPID == 0){ //CPU is idle 
        // std::cout << "LINE 29 " << P1.processPid << std::endl;
        currentlyRunningProcess = P1; //new process now running
        currentlyRunningProcessPID = P1.processPid;
        // std::cout << currentlyRunningProcessPID << std::endl;
    }
    std::sort(test.begin(), test.end(), less_than_priority()); //sort RQ
}

bool SimOS::SimFork(){

}

void SimOS::SimExit(){
    // test.erase(test.begin());
    NextProcessUp();
}

void SimOS::SimWait(){

}

void SimOS::DiskReadRequest(int diskNumber, std::string fileName){
    HardDisks[diskNumber].NewProcessRequestingDiskRead(currentlyRunningProcess, fileName);
    NextProcessUp();
}

void SimOS::DiskJobCompleted(int diskNumber)
{
    Process ReturningProcess = HardDisks[diskNumber].GetProcessReadingDisk();
    HardDisks[diskNumber].LeaveDisk();
    if(currentlyRunningProcessPID != 0){ //process in CPU currently 
        // std::cout << currentlyRunningProcess.processPriority << std::endl;
        // std::cout << "LINE 21 " << P1.processPriority << std::endl;
        if(currentlyRunningProcess.processPriority < ReturningProcess.processPriority){ //priority of new proc > currProc in CPU
            test.push_back(currentlyRunningProcess); //remove currProc from CPU; add to Priority Queue
            currentlyRunningProcess = ReturningProcess; //new proc now running
            currentlyRunningProcessPID = ReturningProcess.processPid;
        }
        else{
            test.push_back(ReturningProcess);
        }
    }
    else if(currentlyRunningProcessPID == 0){ //CPU is idle 
        // std::cout << "LINE 29 " << ReturningProcess.processPid << std::endl;
        currentlyRunningProcess = ReturningProcess; //new process now running
        currentlyRunningProcessPID = ReturningProcess.processPid;
        // std::cout << currentlyRunningProcessPID << std::endl;
    }
    std::sort(test.begin(), test.end(), less_than_priority()); //sort RQ

}

int SimOS::GetCPU(){
    return currentlyRunningProcessPID;
}

void SimOS::PrintVector(){
    // std::sort(test.begin(), test.end(), less_than_priority());
    // std::cout << test[0].processPid << std::endl;
    std::cout << test.size() <<std::endl;
    
}

std::vector<int> SimOS::GetReadyQueue(){
    std::vector<int> vectorOfPIDs;
    for(int i = 0; i < test.size(); i++){
        // std::cout << test[i].processPid << ", " << test[i].processPriority << std::endl;
        vectorOfPIDs.push_back(test[i].processPid);
    }
    return vectorOfPIDs;
}

MemoryUsage SimOS::GetMemory(){

}

FileReadRequest SimOS::GetDisk(int diskNumber){
    return HardDisks[diskNumber].ProcessReadingDisk();
}

std::queue<FileReadRequest> SimOS::GetDiskQueue(int diskNumber){
    std::vector<FileReadRequest> returnValue = HardDisks[diskNumber].ProcessInsideDiskQueue();
    std::queue<FileReadRequest> ans;
    // if(returnValue.size() == 0){
    //     std::cout << "EMPTY DISK QUEUE" << std::endl;
    //     FileReadRequest Empty;
    // }
    // else{
        // for(int i = 0; i < returnValue.size(); i++){
        //     ans.push(returnValue[i]);
        // }
    // }
    for(int i = 0; i < returnValue.size(); i++){
            ans.push(returnValue[i]);
    }
    return ans;
}

Process SimOS::FindProcess(int pid){
    for(int i = 0; i < test.size(); i++){
        if(test[i].processPid == pid){
            return test[i];
        }
    }
    Process notFound {0, 0, -1};
    return (notFound);
}

void SimOS::NextProcessUp(){
    if(test.size() == 0){
        Process NoRunningProcess{0,0,0};
        currentlyRunningProcess = NoRunningProcess;
        currentlyRunningProcessPID = 0;
    }
    else{
        currentlyRunningProcess = test[0];
        currentlyRunningProcessPID = test[0].processPid;
        test.erase(test.begin()); //remove from RQ
    }
}
