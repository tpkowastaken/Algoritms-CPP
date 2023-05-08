#include <iostream>
#include "heap.h"
int main(){
    int h[20] = {1578, 45, 12, 45 ,654, 1, 7};
    for(int i = 0;i<20;i++){
        h[i] = rand();
    }
    heap hello(h, 20);
    int *newArray = hello.extractAsHeapArray();
    hello.print();
    std::cout << "[";
    for(int i = 0;i<hello.size();i++){
        std::cout << newArray[i] << ", ";
    }
    std::cout << "]\n";

    /*
    hello.print();
    for(int i = 16;i;i--){
        hello.insert(i);
    }
    std::cout << "\n";
    hello.print();
    hello.changevalue(5, 100);
    hello.changevalue(4, -1);
    hello.print();
    std::cout << "\n\n\n";
    for(int i = 16;i;i--){
        hello.extractMin();
        hello.print();
        std::cout << "\n\n\n";
    }
    std::cout << "\n\n\n";
    hello.print();
    */
}