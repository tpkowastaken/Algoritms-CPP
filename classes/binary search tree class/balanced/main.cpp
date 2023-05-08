#include <iostream>
#include "binary_search_tree.h"
void control(binary_search_tree *t, binary_node *ptr = nullptr){
    if(!ptr){
        ptr = t->accessHead();
    }
    std::string s;
    while(true){
        std::cin >> s;
        if(s == "cl"){
            std::cout << ptr->childSmallerNode();
            if(!ptr->childSmallerNode()){
            }
            else{
                ptr = ptr->childSmallerNode();
            }
        }
        if(s == "print"){
            t->print();
        }
        else if(s == "cr"){
            std::cout << ptr->childBiggerNode();
            if(!ptr->childBiggerNode()){
            }
            else{
                ptr = ptr->childBiggerNode();
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
    }

}
int main(){

    binary_search_tree hello;
    unsigned int heay = time(0);

    std::cout << "seed: " << heay << "\n";

    srand(heay);
    for(int k = 0;k<5000;k++){
        for(int i = 0;i<25;i++){
            hello.insert(rand());
        }
        std::cout << "\n\n i: " << k << "\n\n\n";
        hello.print();
        for(int i = 0;i<25;i++){
            hello.remove(hello.accessHead());
            hello.verify();
            hello.markverify();
        }
    }
}