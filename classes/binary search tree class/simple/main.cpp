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
    binary_node *hey[25];
    unsigned int heay = 1666458456;

    std::cout << "seed: " << heay << "\n";

    srand(heay);

    for(int i = 0;i<25;i++){
        hey[i] = hello.insert(rand());
    }
    int g = rand()%25;
    int y = rand()%25;
    std::cout << g << " " << y;

    hello.remove(hey[g], 1);
    hello.verify();
    hello.print();
    std::cout << "\n\n";
    hello.remove(hey[y], 1);
    hello.verify();
    hello.print();
}