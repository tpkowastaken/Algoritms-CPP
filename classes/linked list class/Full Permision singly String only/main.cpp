#include <iostream>
#include <fstream>
#include "linked_list.h"
using namespace std;
int main(){
    linked_list hello;
    hello.append("yeey");
    hello.append("yeey1");
    hello.append("yeey2");
    hello.append("yeey3");
    hello.append("yeey4");
    hello.append("yeey5");
    hello.append("yeey6");
    hello.append("yeey7");
    hello.appendToStart("yeey8");
    std::string *coolArray = hello.exportAsAnArray();
    int size = hello.size();
    for(int i = 0;i<size;i++){
        cout << coolArray[i] << "\n";
    }
}