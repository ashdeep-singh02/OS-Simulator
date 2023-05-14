#include "SimOS.h"
#include <algorithm>


SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRam){
    amountOfRamAvailable = amountOfRam;
    maxRam = amountOfRam;
    for(int i = 0; i < numberOfDisks; i++){
        HardDisk newHD = HardDisk();
        HardDisks.push_back(newHD);
    }
}

bool SimOS::AllocateNewProcessInRam(int priority, unsigned long long size){
        if(size > amountOfRamAvailable){
        return false;
    }
    if(RAM.size() == 0){
        //empty RAM
        MemoryItem newProcessInRAM;
        newProcessInRAM.itemAddress = 0;
        newProcessInRAM.itemSize = size;
        newProcessInRAM.PID = pid + 1;
        RAM.push_back(newProcessInRAM);
        amountOfRamAvailable -= size;
    }
    else{
        int holeLargeEnoughAfterIndex = -1;
        bool holeFound = false;
        bool holeAtBeginning = false;
        int index = 0;
        int emptyHoleSpace = 0;
        int spaceBeingUsed = 0;
        if(RAM[0].itemAddress != 0 && (RAM[0].itemAddress > size)){
            holeAtBeginning = true;
        }
        while(index < RAM.size() - 1 && !holeFound){
            emptyHoleSpace += (RAM[index+1].itemAddress) - (RAM[index].itemAddress + RAM[index].itemSize);
            spaceBeingUsed += RAM[index].itemSize;
            if((RAM[index+1].itemAddress) - (RAM[index].itemAddress + RAM[index].itemSize) >= size){
                holeLargeEnoughAfterIndex = index;
                holeFound = true;
                if ((RAM[index+1].itemAddress) - (RAM[index].itemAddress + RAM[index].itemSize) < RAM[0].itemAddress){
                    holeAtBeginning = false;
                }
            }
            index++;
        }
        spaceBeingUsed += RAM[RAM.size() - 1].itemSize;
        bool isLastProcInRAM = false;
        if(!holeFound){
            MemoryItem lastItemInRam = RAM[RAM.size()-1];
            if((lastItemInRam.itemAddress + lastItemInRam.itemSize) + size <= maxRam){
                holeLargeEnoughAfterIndex = RAM.size() - 1;
                holeFound = true;
                isLastProcInRAM = true;
            }
            else{
                return false;
            }
        }
        if(holeAtBeginning){
            MemoryItem newProcessInRAM;
            newProcessInRAM.itemAddress = 0;
            newProcessInRAM.itemSize = size;
            newProcessInRAM.PID = pid + 1;
            RAM.insert(RAM.begin(), newProcessInRAM);
            amountOfRamAvailable -= size;
        }
        else{
            std::vector<MemoryItem> updateRAM;
            for(int i = 0; i <= holeLargeEnoughAfterIndex; i++){
                updateRAM.push_back(RAM[i]);
            }
            if(isLastProcInRAM){
                MemoryItem newProcessInRAM;
                newProcessInRAM.itemAddress = RAM[holeLargeEnoughAfterIndex].itemAddress+RAM[holeLargeEnoughAfterIndex].itemSize;
                newProcessInRAM.itemSize = size;
                newProcessInRAM.PID = pid+1;
                RAM.push_back(newProcessInRAM);
            }
            MemoryItem newProcessInRAM;
            newProcessInRAM.itemAddress =(RAM[holeLargeEnoughAfterIndex].itemAddress+RAM[holeLargeEnoughAfterIndex].itemSize);
            newProcessInRAM.itemSize = size;
            newProcessInRAM.PID = pid+1;
            updateRAM.push_back(newProcessInRAM);
            if(!isLastProcInRAM){
                for(int i = holeLargeEnoughAfterIndex+1; i < RAM.size(); i++){
                    updateRAM.push_back(RAM[i]);
                }
            }
            amountOfRamAvailable -= size;
            RAM = updateRAM;
        }
    }
    return true;
}

bool SimOS::NewProcess(int priority, unsigned long long size){
    bool allocatedInRam = AllocateNewProcessInRam(priority, size);
    if(!allocatedInRam){
        return false;
    }

    pid++;
    Process P1{priority, size, pid}; //new Process created
    if(currentlyRunningProcessPID != 0){ //process in CPU currently 
        if(currentlyRunningProcess.processPriority < P1.processPriority){ //priority of new proc > currProc in CPU
            readyQueue.push_back(currentlyRunningProcess); //remove currProc from CPU; add to Priority Queue
            currentlyRunningProcess = P1; //new proc now running
            currentlyRunningProcessPID = P1.processPid;
        }
        else{
            readyQueue.push_back(P1);
        }
    }
    else if(currentlyRunningProcessPID == 0){ //CPU is idle 
        currentlyRunningProcess = P1; //new process now running
        currentlyRunningProcessPID = P1.processPid;
    }
    std::sort(readyQueue.begin(), readyQueue.end(), less_than_priority()); //sort RQ
    return true;
}

bool SimOS::NewChildProcess(int priority, unsigned long long size){
    bool allocatedInRam = AllocateNewProcessInRam(priority, size);
    if(!allocatedInRam){
        return false;
    }

    pid++;
    Process P1{priority, size, pid}; //new Process created
    P1.setParentProcess(currentlyRunningProcessPID);
    currentlyRunningProcess.setChildProcess(pid);
    currentlyRunningProcess.setChildrenProcesses(P1);
    if(currentlyRunningProcessPID != 0){ //process in CPU currently 
        if(currentlyRunningProcess.processPriority < P1.processPriority){ //priority of new proc > currProc in CPU
            readyQueue.push_back(currentlyRunningProcess); //remove currProc from CPU; add to Priority Queue
            currentlyRunningProcess = P1; //new proc now running
            currentlyRunningProcessPID = P1.processPid;
        }
        else{
            readyQueue.push_back(P1);
        }
    }
    else if(currentlyRunningProcessPID == 0){ //CPU is idle 
        currentlyRunningProcess = P1; //new process now running
        currentlyRunningProcessPID = P1.processPid;
    }
    std::sort(readyQueue.begin(), readyQueue.end(), less_than_priority()); //sort RQ
    return true;
}

bool SimOS::SimFork(){
    return  NewChildProcess(currentlyRunningProcess.processPriority, currentlyRunningProcess.processSize);
}

void SimOS::TerminateChildren(Process parentProcess){
    std::vector<Process> children;
    children = parentProcess.getChildrenProcesses();
    for(int i = 0; i < children.size(); i++){
        int childPID = children[i].processPid;
        for(int i = 0; i < readyQueue.size(); i++){
            if(readyQueue[i].processPid == childPID){
                TerminateChildren(readyQueue[i]);
                readyQueue.erase(readyQueue.begin() + i);
            }
        }
        for(int i = 0; i < HardDisks.size(); i++){
            for(int j = 0; j < HardDisks[i].diskQueue.size(); j++){
                if(HardDisks[i].diskQueue[j].first.processPid == childPID){
                    TerminateChildren(HardDisks[i].diskQueue[j].first);
                    HardDisks[i].diskQueue.erase(HardDisks[i].diskQueue.begin() + j);
                }
            }
        }
        for(int i = 0; i < HardDisks.size(); i++){
            if(HardDisks[i].GetPidOfRunningProcess() == childPID){
                TerminateChildren(HardDisks[i].GetProcessReadingDisk());
                HardDisks[i].LeaveDisk();
            }
        }
        for(int i = 0; i < RAM.size(); i++){
            if(RAM[i].PID == childPID){
                RAM.erase(RAM.begin() + i);
            }
        }
        // for(int i = 0; i < zombieProcesses.size(); i++){
        //     if(zombieProcesses[i].processPid == childPID){
        //         zombieProcesses.erase(zombieProcesses.begin() + i);
        //     }
        // }
        // TerminateChildren(children[i]);
    }
}

void SimOS::SimExit(){
    // readyQueue.erase(readyQueue.begin());
    if(currentlyRunningProcess.getParent()!=-1){
        bool parentWaiting = false;
        int index = 0;
        while(index < waitingProcesses.size() && !parentWaiting){
            int currentProcessParentPID = currentlyRunningProcess.getParent();
            if(waitingProcesses[index].processPid == currentProcessParentPID){
                Process currentProcessParent = waitingProcesses[index];
                readyQueue.push_back(currentProcessParent);
                std::sort(readyQueue.begin(), readyQueue.end(), less_than_priority()); //sort RQ
                parentWaiting = true;
            }
            index++;
        }
        if(!parentWaiting){
            //parent is not waiting => turn into zombie :O
            zombieProcesses.push_back(currentlyRunningProcess);
        }
    }
    TerminateChildren(currentlyRunningProcess);
    DeleteRunningProcess();
    return;
}

void SimOS::SimWait(){
    waitingProcesses.push_back(currentlyRunningProcess);
    NextProcessUp();
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
        if(currentlyRunningProcess.processPriority < ReturningProcess.processPriority){ //priority of new proc > currProc in CPU
            readyQueue.push_back(currentlyRunningProcess); //remove currProc from CPU; add to Priority Queue
            currentlyRunningProcess = ReturningProcess; //new proc now running
            currentlyRunningProcessPID = ReturningProcess.processPid;
        }
        else{
            readyQueue.push_back(ReturningProcess);
        }
    }
    else if(currentlyRunningProcessPID == 0){ //CPU is idle 
        currentlyRunningProcess = ReturningProcess; //new process now running
        currentlyRunningProcessPID = ReturningProcess.processPid;
    }
    std::sort(readyQueue.begin(), readyQueue.end(), less_than_priority()); //sort RQ

}

int SimOS::GetCPU(){
    return currentlyRunningProcessPID;
}

std::vector<int> SimOS::GetReadyQueue(){
    std::vector<int> vectorOfPIDs;
    for(int i = 0; i < readyQueue.size(); i++){
        vectorOfPIDs.push_back(readyQueue[i].processPid);
    }
    return vectorOfPIDs;
}

MemoryUsage SimOS::GetMemory(){
    std::vector<MemoryItem> ans;
    for(int i = 0; i< RAM.size(); i++){
        ans.push_back(RAM[i]);
    }
    return ans;
}

FileReadRequest SimOS::GetDisk(int diskNumber){
    return HardDisks[diskNumber].ProcessReadingDisk();
}

std::queue<FileReadRequest> SimOS::GetDiskQueue(int diskNumber){
    std::vector<FileReadRequest> returnValue = HardDisks[diskNumber].ProcessInsideDiskQueue();
    std::queue<FileReadRequest> ans;
    for(int i = 0; i < returnValue.size(); i++){
            ans.push(returnValue[i]);
    }
    return ans;
}

void SimOS::DeleteRunningProcess(){
    int index = 0;
    bool processToBeDeletedFound = false;
    while((index < RAM.size()) && (!processToBeDeletedFound)){
        if(RAM[index].PID == currentlyRunningProcessPID){
            amountOfRamAvailable += RAM[index].itemSize;
            RAM.erase(RAM.begin() + index);
            processToBeDeletedFound = true;
        }
        index++;
    }
    NextProcessUp();
}

void SimOS::NextProcessUp(){
    if(readyQueue.size() == 0){
        Process NoRunningProcess{0,0,0};
        currentlyRunningProcess = NoRunningProcess;
        currentlyRunningProcessPID = 0;
    }
    else{
        currentlyRunningProcess = readyQueue[0];
        currentlyRunningProcessPID = readyQueue[0].processPid;
        readyQueue.erase(readyQueue.begin()); //remove from RQ
    }
}