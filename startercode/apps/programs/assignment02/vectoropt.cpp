#include <iostream>
#include <chrono>
#include "vectoropt.hpp"

int main() {
    std::cout << "Testing VectorOpt Class (starts at 128, grows by 4x)\n";
    std::cout << "===================================================\n\n";
    
    for (int size : {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192}) {
        VectorOpt<int> v;
        
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < size; i++) {
            v.push_back(i);
        }
        auto end = std::chrono::steady_clock::now();
        
        std::chrono::duration<double, std::milli> elapsed = end - start;
        
        std::cout << "Size: " << size 
                  << " | Time: " << elapsed.count() << " ms"
                  << " | Capacity: " << v.capacity() << "\n";
    }
    
    return 0;
}