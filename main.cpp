#include "FileReadRequest.h"
#include "MemoryItem.h"
#include "SimOs.h"
#include "Process.cpp"
#include <iostream>
#include <queue>

int main(){
    // SimOS sim(2,900);
    // sim.NewProcess(5,90);
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    // sim.NewProcess(3,90);
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    // sim.NewProcess(8,90);
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;

    // sim.DiskReadRequest(0, "abc.cpp");
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    // std::cout << "PROC Reading Disk #0: " << sim.GetDisk(0).PID << std::endl;
    // std::cout << "PROC Reading Disk #1: " << sim.GetDisk(1).PID << std::endl;

    // sim.DiskReadRequest(1, "bye.cpp");
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;

    // sim.DiskReadRequest(1, "bye.cpp");
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    // std::cout << "PROC Reading Disk #1: " << sim.GetDisk(1).PID << std::endl;
    // auto q1{ sim.GetDiskQueue(1) };
    // std::cout << (q1.size() == 1) << std::endl;
    // std::cout << (q1.front().PID == 2) << std::endl;

    // sim.DiskJobCompleted(1);
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    // std::cout << "PROC Reading Disk #1: " << sim.GetDisk(1).PID << std::endl;
    // auto q2{ sim.GetDiskQueue(1) };
    // std::cout << (q2.size() == 0) << std::endl;

    // sim.DiskJobCompleted(1);
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    // std::cout << "PROC Reading Disk #1: " << sim.GetDisk(1).PID << std::endl;
    // std::cout << "PROC in Ready Queue: " << sim.GetReadyQueue()[0] << std::endl;

    // sim.DiskJobCompleted(0);
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    // std::cout << "PROC Reading Disk #0: " << sim.GetDisk(0).PID << std::endl;
    // auto rq{ sim.GetReadyQueue() };
    // std::cout << (rq.size() == 2) << std::endl;
    // std::cout << ((rq[0] == 1 && rq[1] == 2) || (rq[0] == 2 && rq[1] == 1)) << std::endl;

    // sim.SimExit();
    // sim.PrintVector();
    // std::vector<int> ans = sim.GetReadyQueue();
    // for(int i = 0; i < ans.size(); i++){
    //     std::cout << ans[i] << std::endl;
    // }
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    // sim.SimExit();
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    
    // sim.DiskReadRequest(2, "hello.cpp");
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    // std::cout << "PROC Reading the Disk: " << sim.GetDisk(2).PID << std::endl;
    // std::queue<FileReadRequest> DQ = sim.GetDiskQueue(2);
    // std::cout << "First Process in Disk Queue: "<< DQ.front().PID << std::endl;
    // sim.DiskJobCompleted(2);
    // std::cout << "JOB DONE" << std::endl;
    // std::cout << "PROC IN CPU: " << sim.GetCPU() << std::endl;
    // std::cout << "PROC Reading the Disk: " << sim.GetDisk(2).PID << std::endl;
    // DQ = sim.GetDiskQueue(2);
    // std::cout << "First Process in Disk Queue: "<< DQ.front().PID << std::endl;

    // std::cout << found.processPriority << std::endl;
    // std::cout << sim.GetCPU() << std::endl;
}

// #include<iostream>
// #include<vector>
// #include<queue>

// #include"SimOS.h"

// #define TEST_PASS 1
// #define TEST_FAIL 0

// #define CHECK(x) if(!(x)) return TEST_FAIL;

// bool ContMemoryItem(const MemoryItem & item, unsigned long long cAddress, unsigned long long cSize, int cPID)
// {
// 	return item.itemAddress == cAddress && item.itemSize == cSize && item.PID == cPID;
// }

// // Process management and CPU scheduling
// int Test_1()
// {
// 	SimOS sim{ 2, 20000 };

// 	sim.NewProcess(5, 1000);
// 	CHECK(sim.GetCPU() == 1);

// 	sim.NewProcess(3, 1000);
// 	CHECK(sim.GetCPU() == 1);

// 	sim.NewProcess(8, 1000);
// 	CHECK(sim.GetCPU() == 3);

// 	sim.DiskReadRequest(0, "abc");
// 	CHECK(sim.GetCPU() == 1);
// 	CHECK(sim.GetDisk(0).PID == 3);
// 	CHECK(sim.GetDisk(1).PID == 0);

// 	sim.DiskReadRequest(1, "abc");
// 	CHECK(sim.GetCPU() == 2);

// 	sim.DiskReadRequest(1, "abc");
// 	CHECK(sim.GetCPU() == 0);
// 	CHECK(sim.GetDisk(1).PID == 1);
// 	auto q1{ sim.GetDiskQueue(1) };
// 	CHECK(q1.size() == 1);
// 	CHECK(q1.front().PID == 2);

// 	sim.DiskJobCompleted(1);
// 	CHECK(sim.GetCPU() == 1);
// 	CHECK(sim.GetDisk(1).PID == 2);
// 	auto q2{ sim.GetDiskQueue(1) };
// 	CHECK(q2.size() == 0);

// 	sim.DiskJobCompleted(1);
// 	CHECK(sim.GetCPU() == 1);
// 	CHECK(sim.GetDisk(1).PID == 0);
// 	CHECK(sim.GetReadyQueue()[0] == 2);

// 	sim.DiskJobCompleted(0);
// 	CHECK(sim.GetCPU() == 3);
// 	CHECK(sim.GetDisk(0).PID == 0);
// 	auto rq{ sim.GetReadyQueue() };
// 	CHECK(rq.size() == 2);
// 	CHECK((rq[0] == 1 && rq[1] == 2) || (rq[0] == 2 && rq[1] == 1));

// 	return TEST_PASS;
// }

// // Memory management
// int Test_2()
// {
// 	SimOS sim{ 100,200 };
// 	auto mem{ sim.GetMemory() };
// 	CHECK(mem.size() == 0);

// 	sim.NewProcess(10, 10);
// 	mem = sim.GetMemory();
// 	CHECK(mem.size() == 1);
// 	CHECK(ContMemoryItem(mem[0], 0, 10, 1 ));

// 	sim.NewProcess(1, 10);
// 	sim.NewProcess(9, 5);
// 	sim.NewProcess(2, 15);

// 	sim.SimExit();
// 	sim.SimExit();
// 	mem = sim.GetMemory();
// 	CHECK(mem.size() == 2);
// 	CHECK(ContMemoryItem(mem[0], 10, 10, 2));
// 	CHECK(ContMemoryItem(mem[1], 25, 15, 4));

// 	sim.NewProcess(3, 4);
// 	mem = sim.GetMemory();
// 	CHECK(ContMemoryItem(mem[1], 20, 4, 5));

// 	sim.NewProcess(4, 5);
// 	mem = sim.GetMemory();
// 	CHECK(ContMemoryItem(mem[0], 0, 5, 6));

// 	sim.NewProcess(5, 10);
// 	mem = sim.GetMemory();
// 	CHECK(ContMemoryItem(mem[4], 40, 10, 7));

// 	return TEST_PASS;
// }

// // Cascading termination
// int Test_3()
// {
// 	SimOS sim{ 3, 10'000'000'000 };

// 	sim.NewProcess(4, 10);
// 	sim.SimFork();
// 	sim.SimFork();
// 	sim.SimFork();
// 	sim.NewProcess(1, 10);

// 	sim.DiskReadRequest(0, "abc");
// 	sim.DiskReadRequest(0, "abc");
// 	sim.DiskReadRequest(0, "abc");
// 	sim.SimFork();
// 	sim.DiskReadRequest(1, "abc");
// 	sim.DiskReadRequest(0, "abc");

// 	CHECK(sim.GetCPU() == 5);
// 	sim.DiskReadRequest(1, "abc");

// 	sim.DiskJobCompleted(0);
// 	sim.SimExit();

// 	CHECK(sim.GetCPU() == 0);
// 	auto q1{ sim.GetDiskQueue(1) };
// 	CHECK(q1.size() == 0);

// 	CHECK(sim.GetDisk(0).PID == 0);
// 	CHECK(sim.GetDisk(1).PID == 5);
// 	CHECK(sim.GetDiskQueue(0).size() == 0);
// 	CHECK(sim.GetDiskQueue(1).size() == 0);

// 	auto mem{ sim.GetMemory() };
// 	CHECK(mem.size() == 1);
// 	CHECK(ContMemoryItem(mem[0], 40, 10, 5));

// 	return TEST_PASS;
// }

// // Wait and exit interactions
// int Test_4()
// {
// 	SimOS sim{ 2, 2000 };

// 	sim.NewProcess(4, 10);
// 	sim.SimFork();

// 	CHECK(sim.GetCPU() == 1);

// 	sim.SimWait();
// 	CHECK(sim.GetCPU() == 2);

// 	sim.SimExit();
// 	CHECK(sim.GetCPU() == 1);

// 	sim.SimFork();
// 	sim.SimFork();
// 	sim.SimFork();
// 	sim.DiskReadRequest(0, "hbhb");
// 	sim.DiskReadRequest(1, "hbhb");
// 	sim.SimExit();
// 	sim.SimExit();
// 	sim.DiskJobCompleted(0);

// 	sim.NewProcess(2, 10);
// 	CHECK(sim.GetCPU() == 1);

// 	sim.SimWait();
// 	CHECK(sim.GetCPU() == 1);
// 	sim.SimWait();
// 	CHECK(sim.GetCPU() == 1);
// 	sim.SimWait();
// 	CHECK(sim.GetCPU() == 6);

// 	return TEST_PASS;
// }

// // Large memory sizes and fragmentation
// int Test_5()
// {
// 	SimOS sim{ 2, 32'000'000'000 };

// 	sim.NewProcess(5, 1'000'000'000);
// 	sim.NewProcess(4, 30'000'000'000);
// 	sim.SimExit();
// 	CHECK(sim.NewProcess(7, 1'500'000'000) == false);
// 	CHECK(sim.GetCPU() == 2);
// 	CHECK(sim.GetReadyQueue().size() == 0);

// 	return TEST_PASS;
// }

// int main(int argc, char* argv[])
// {
// 	if (Test_1()==TEST_PASS)
// 		std::cout << "Test 1 passed successfully" << std::endl;
// 	else
// 		std::cout << "ERROR!!! TEST 1 FAILS!!!" << std::endl;

// 	if (Test_2()==TEST_PASS)
// 		std::cout << "Test 2 passed successfully" << std::endl;
// 	else
// 		std::cout << "ERROR!!! TEST 2 FAILS!!!" << std::endl;

// 	if (Test_3()==TEST_PASS)
// 		std::cout << "Test 3 passed successfully" << std::endl;
// 	else
// 		std::cout << "ERROR!!! TEST 3 FAILS!!!" << std::endl;

// 	if (Test_4()==TEST_PASS)
// 		std::cout << "Test 4 passed successfully" << std::endl;
// 	else
// 		std::cout << "ERROR!!! TEST 4 FAILS!!!" << std::endl;

// 	if (Test_5()==TEST_PASS)
// 		std::cout << "Test 5 passed successfully" << std::endl;
// 	else
// 		std::cout << "ERROR!!! TEST 5 FAILS!!!" << std::endl;

// 	return 0;
// }


