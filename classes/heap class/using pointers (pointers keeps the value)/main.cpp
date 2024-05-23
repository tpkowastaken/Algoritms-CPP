#include <iostream>
#include <string.h>
#include "heap.h"
int main(){
    heap hello;
    for(int i = 19;i;i--){
        hello.insert(i);
    }
    hello.print();
    hello.changeValue(hello.searchFor(15), 4);
    hello.print();
    while(!hello.isEmpty()){
        std::cout << hello.extractMin() << "\n";
    }
}