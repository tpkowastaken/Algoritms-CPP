#include <iostream>
#include "./Doubly linked list/linked_list.h"
#include "./heap/heap.h"
struct graph_node 
{
    int index;
    int length;
};
int main(){
    int n,m;
    std::cin >> n >> m;
    linked_list<graph_node> *graph = new linked_list<graph_node>[n];
    {
        int index, index2, length;
        for(int i = 0;i<m;i++){
            std::cin >> index >> index2 >> length;
            graph[index].append({index2, length});
        }
    }
    {
        Node<graph_node>* pointer;
        for(int i = 0;i<n;i++){
            std::cout << i << ": {";
            pointer = graph[i].firstNode();
            while(pointer){
                std::cout << "[" << pointer->value.index << ", " << pointer->value.length << "], ";
                pointer = pointer->nextNode();
            }
            std::cout << "}\n";
        }
    }
    linked_list<graph_node> *finalgraph = new linked_list<graph_node>[n];
    heap queue;
    queue.insert();
    while(!queue.isEmpty()){

    }

    delete [] finalgraph;
    delete [] graph;
}