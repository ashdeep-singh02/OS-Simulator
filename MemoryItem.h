#ifndef MEMORY_ITEM_
#define MEMORY_ITEM_

#include <iostream>
#include <vector>


struct MemoryItem{
    unsigned long long itemAddress;
    unsigned long long itemSize;
    int PID;
};
using MemoryUsage = std::vector<MemoryItem>;

#endif