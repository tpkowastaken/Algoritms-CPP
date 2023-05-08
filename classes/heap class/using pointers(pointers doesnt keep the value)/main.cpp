#include <iostream>
#include "heap.h"
#include <math.h>
int main(){
    heap hello;
    for(int i = 16;i;i--){
        hello.insert(i);
    }
    hello.print();
    hello.changeValue(hello.searchFor(3), 15);
    hello.print();
    for(int i = 16;i;i--){
        std::cout << hello.extractMin() << "\n";
    }

    /*
    heap hello;
    std::string s;
    int i = 10;
    hello.insert(11);
    heap_node *ptr = hello.min();
    while(true){
        std::cin >> s;
        if(s == "cl"){
            std::cout << ptr->leftChild();
            if(!ptr->leftChild()){
            }
            else{
                ptr = ptr->leftChild();
            }
        }
        else if(s == "n"){
            hello.insert(i);
            i--;
        }
        else if(s == "cr"){
            std::cout << ptr->rightChild();
            if(!ptr->rightChild()){
            }
            else{
                ptr = ptr->rightChild();
            }
        }
        else if(s == "p"){
            std::cout << ptr->parentNode();
            if(!ptr->parentNode()){
            }
            else{
                ptr = ptr->parentNode();
            }
        }
        else if(s == "v"){
            std::cout << ptr->value;
        }
        else if(s == "x"){
            break;
        }
        std::cout << "\n";
    }*/
}