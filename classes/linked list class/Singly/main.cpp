#include <iostream>
#include <fstream>
#include "linked_list.h"
using namespace std;
int main(){
    linked_list<int> hello;
    hello.append(1);
    hello.append(2);
    hello.append(3);
    hello.append(4);
    hello.append(5);
    hello.append(6);
    hello.append(7);
    hello.append(8);
    hello.append(9);
    int *coolArray = hello.exportAsAnArray();
    int size = hello.size();
    for(int i = 0;i<size;i++){
        cout << coolArray[i] << "\n";
    }
}