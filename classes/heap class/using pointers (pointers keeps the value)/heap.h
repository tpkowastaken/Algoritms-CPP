#ifndef HEAP_H
#define HEAP_H
#include <math.h>
#include "myException.h"
class heap;
class heap_node{
    friend class heap;
    public:
        int nodeValue(){
            return value;
        }
        heap_node *parentNode(){
            return parent;
        }
        heap_node *leftChild(){
            return childLeft;
        }
        heap_node *rightChild(){
            return childRight;
        }
        heap *insideHeap(){
            return currentHeap;
        }
    private:
        int value;
        heap_node(int value, heap *currentHeap){
            this->value = value;
            this->currentHeap = currentHeap;
        }
        ~heap_node(){}
        heap *currentHeap = nullptr;
        heap_node *parent = nullptr;
        heap_node *childLeft = nullptr;
        heap_node *childRight = nullptr;

};
class heap{
    private:
        /*
        swaps two nodes in the heap so that it doesn't break pointer connections
        */
        void swap(heap_node *firstNode, heap_node *secondNode){//we could also transform just the value but that wont keep the same value to a pointer
            if(!firstNode){
                throw myException("passed pointer firstNode == nullptr -- heap::swap");
            }
            if(!secondNode){
                throw myException("passed pointer secondNode == nullptr -- heap::swap");
            }
            if(firstNode->currentHeap != this){
                throw myException("passed pointer firstNode is from a different heap -- heap::swap");
            }
            if(secondNode->currentHeap != this){
                throw myException("passed pointer secondNode is from a different heap -- heap::swap");
            }
            bool connectedCall = false;
            if(secondNode->parent == firstNode){
                heap_node *tmp = firstNode;
                firstNode = secondNode;
                secondNode = tmp;
            }
            if(firstNode->parent == secondNode){
                connectedCall = true;
            }
            if(firstNode == lastLine[currentLastNode]){
                lastLine[currentLastNode] = secondNode;
            }
            else if(secondNode == lastLine[currentLastNode]){
                lastLine[currentLastNode] = firstNode;
            }
            else {
                for(int i = 0;i<lastLineSize;i++){
                    if(firstNode == lastLine[i]){
                        lastLine[i] = secondNode;
                        break;
                    }
                    else if(secondNode == lastLine[i]){
                        lastLine[i] = firstNode;
                        break;
                    }
                }
            }
            if(firstNode == head){
                head = secondNode;
            }
            else if(secondNode == head){
                head = firstNode;
            }

            //telling parent about the new relation
            if(secondNode->parent){
                if(secondNode->parent->childLeft == secondNode){
                    secondNode->parent->childLeft = firstNode;
                }
                else if(secondNode->parent->childRight == secondNode){
                    secondNode->parent->childRight = firstNode;
                }
            }
            if(!connectedCall && firstNode->parent){
                if(firstNode->parent->childLeft == firstNode){
                    firstNode->parent->childLeft = secondNode;
                }
                else if(firstNode->parent->childRight == firstNode){
                    firstNode->parent->childRight = secondNode;
                }
            }

            //assigning to the nodes themselves
            if(firstNode->parent == secondNode && firstNode == secondNode->childLeft){
                heap_node *firstNodeRightChild = firstNode->childRight;
                heap_node *secondNodeParent = secondNode->parent;

                firstNode->childRight = secondNode->childRight;//verified
                secondNode->childLeft = firstNode->childLeft;//verified

                secondNode->parent = firstNode;//custom for every if
                firstNode->childLeft = secondNode;//custom for every if

                firstNode->parent = secondNodeParent;
                secondNode->childRight = firstNodeRightChild;
            }
            else if(firstNode->parent == secondNode && firstNode == secondNode->childRight){//
                heap_node *firstNodeLeftChild = firstNode->childLeft;
                heap_node *secondNodeParent = secondNode->parent;
                firstNode->childLeft = secondNode->childLeft;
                secondNode->childRight = firstNode->childRight;

                secondNode->parent = firstNode;//custom for every if
                firstNode->childRight = secondNode;//custom for every if

                firstNode->parent = secondNodeParent;
                secondNode->childLeft = firstNodeLeftChild;

            }
            else if(!connectedCall){
                heap_node *firstNodeChildLeft = firstNode->childLeft;
                heap_node *firstNodeChildRight = firstNode->childRight;
                heap_node *firstNodeParent = firstNode->parent;

                firstNode->childLeft = secondNode->childLeft;
                firstNode->childRight = secondNode->childRight;
                firstNode->parent = secondNode->parent;

                secondNode->childLeft = firstNodeChildLeft;
                secondNode->childRight = firstNodeChildRight;
                secondNode->parent = firstNodeParent;

            }
            //telling childs about the new relations
            if(firstNode->childLeft){
                firstNode->childLeft->parent = firstNode;
            }
            if(firstNode->childRight){
                firstNode->childRight->parent = firstNode;
            }
            if(secondNode->childLeft){
                secondNode->childLeft->parent = secondNode;
            }
            if(secondNode->childRight){
                secondNode->childRight->parent = secondNode;
            }
        }
        /*
        bubbles Down a node that is passed in
        */
        void bubbleDown(heap_node *nodeToBeBubbledDown){
            if(!nodeToBeBubbledDown){
                throw myException("passed pointer == nullptr -- heap::bubbleDown");
            }
            if(nodeToBeBubbledDown->currentHeap != this){
                throw myException("passed pointer is from a different heap -- heap::bubbleDown");
            }
            while(nodeToBeBubbledDown->childLeft || nodeToBeBubbledDown->childRight){
                if(nodeToBeBubbledDown->childRight
                && (nodeToBeBubbledDown->childLeft->value < nodeToBeBubbledDown->value
                || nodeToBeBubbledDown->childRight->value < nodeToBeBubbledDown->value)){
                    swap(nodeToBeBubbledDown, nodeToBeBubbledDown->childLeft->value < nodeToBeBubbledDown->childRight->value ? nodeToBeBubbledDown->childLeft : nodeToBeBubbledDown->childRight);
                }
                else if(nodeToBeBubbledDown->value > nodeToBeBubbledDown->childLeft->value){
                    swap(nodeToBeBubbledDown, nodeToBeBubbledDown->childLeft);
                }
                else {
                    break;
                }
            }
        }
        /*
        bubbles Down a node that is passed in
        */
        void bubbleUp(heap_node *nodeToBeBubbledUp){
            if(!nodeToBeBubbledUp){
                throw myException("passed !pointer -- heap::bubbleUp");
            }
            if(nodeToBeBubbledUp->currentHeap != this){
                throw myException("passed pointer is from a different heap -- heap::bubbleUp");
            }
            while(nodeToBeBubbledUp->parent && nodeToBeBubbledUp->parent->value > nodeToBeBubbledUp->value){
                swap(nodeToBeBubbledUp, nodeToBeBubbledUp->parent);
            }
        }
        /*
        puts the current passed node in its spot in the printedResult array and calls it again for its childs.
        */
        void printfrom(heap_node *ptr, int i, int **printedResult){
            if(ptr && ptr->currentHeap != this){
                throw myException("passed pointer is from a different heap -- heap::printfrom");
            }
            int k = (lastLineSize*2)/pow(2,height() -1 - i);
            if(!ptr && i < height()){//if we're in scope of the arrays but the element is non-existant put a zero there
                printedResult[i][printedResult[i][k]] = 0;
                printedResult[i][k]++;
                return;
            }
            else if(!ptr){
                return;
            }
            printedResult[i][printedResult[i][k]] = ptr->value;
            printedResult[i][k]++;
            printfrom(ptr->childLeft, i+1, printedResult);
            printfrom(ptr->childRight, i+1, printedResult);
        }
        heap_node *head = nullptr;//root of the heap
        heap_node **lastLine = nullptr;//last full line
        int currentLastNode = 0;
        int lastLineSize = 0;
    public:
        heap(){}
        ~heap(){
            while(!isEmpty()){
                extractMin();
            }
        }
        /*
        imports heap from an array of integer values
        */
        void importFromArray(int *array, int n){
            for(int i = 0;i<n;i++){
                insert(array[i]);
            }
        }
        /*
        changes a value of a set pointer
        */
        void changeValue(heap_node *nodeToBeEdited, int value){
            if(!nodeToBeEdited){
                throw myException("passed pointer == nullptr -- heap::changeValue");
            }
            if(nodeToBeEdited->currentHeap != this){
                throw myException("passed pointer is from a different heap -- heap::changeValue");
            }
            if(nodeToBeEdited->value < value){
                nodeToBeEdited->value = value;
                bubbleDown(nodeToBeEdited);
            }
            else if(nodeToBeEdited->value > value){
                nodeToBeEdited->value = value;
                bubbleUp(nodeToBeEdited);
            }

        }
        /*
        searches for a set value in the heap
        */
        heap_node *searchFor(int value){
            return searchFor(value, head);
        }
        /*
        searches for a set value in the heap starting from the starting point going down
        */
        heap_node *searchFor(int value, heap_node *startingPoint){
            if(startingPoint && startingPoint->currentHeap != this){
                throw myException("passed pointer is from a different heap -- heap::searchFor");
            }
            if(!startingPoint)return nullptr;
            if(startingPoint->value == value)return startingPoint;
            heap_node *firstPossible = searchFor(value, startingPoint->childLeft);
            if(firstPossible)return firstPossible;
            return searchFor(value, startingPoint->childRight);
        }
        /*
        prints the last line
        */
        void printLastLine(){
            if(!head){
                throw myException("there is nothing to be printed - the heap is empty -- heap::printLastLine");
            }
            std::cout << "[";
            for(int i = 0; i<lastLineSize;i++){
                std::cout << lastLine[i]->value << " ";
            }
            std::cout << "]\n";
        }
        /*
        prints the whole heap in an arraylike style
        */
        void print(){
            if(!head){
                throw myException("there is nothing to be printed - the heap is empty -- heap::printLastLine");
            }
            int n = height();
            int **printedResult = new int*[n];
            for(int i = 1;i<=n; i++){
                int k = (lastLineSize*2)/pow(2,i-1);//gets the length of the current line (as can be vizualized in the print result)
                printedResult[n-i] = new int[k+1];//the last element is the index for the printfrom function
                printedResult[n-i][k] = 0;//here the index is assigned to zero
            }
            printfrom(head, 0, printedResult);
            for(int i = 0;i<n;i++){//printing everything apart from the index
                std::cout << "[";
                int size = (lastLineSize*2)/pow(2,height() -1 - i);
                for(int k = 0; k<size;k++){
                    std::cout << printedResult[i][k] << ", ";
                }
                std::cout << "]\n";
            }
            for(int i = 0;i<n;i++){
                delete [] printedResult[i];
            }
            delete [] printedResult;
        }
        /* 
        returns the number of rows (height) of the heap
        */
        int height(){//solves the equation x = 2^k with x being the lastlinesize
            return log10(lastLineSize)/log10(2)+2;//plus two so it can count the first one with just one element and the last one (because lastlineSize is the last filled last line)
        }
        bool isEmpty(){
            if(!head){
                return true;
            }
            return false;
        }
        heap_node *min(){
            if(!head){
                throw myException("the heap doesn't have any values inside! -- heap::min");
            }
            return head;
        }
        /*
        removes the root/head and replaces it = deleting the smallest value
        */
        int extractMin(){
            if(!head){
                throw myException("the heap doesn't have any values inside, so there is nothing to remove -- heap::extractMin");
            }
            int value = head->value;
            if(!head->childLeft && !head->childRight){
                delete [] lastLine;
                delete head;
                head = nullptr;
                return value;
            }
            heap_node *ptr = head;
            heap_node *last = lastLine[currentLastNode]->childRight ? lastLine[currentLastNode]->childRight : lastLine[currentLastNode]->childLeft;
            swap(ptr, last);
            if(lastLineSize == 1 && !head->childRight){
                delete ptr;
                last->childLeft = nullptr;
                last->childRight = nullptr;
                last->parent = nullptr;
                head = last;
                return value;
            }
            if(lastLine[currentLastNode]->childLeft == ptr){
                lastLine[currentLastNode]->childLeft = nullptr;
                currentLastNode--;
            }
            else if(lastLine[currentLastNode]->childRight == ptr){
                lastLine[currentLastNode]->childRight = nullptr;
            }
            else {
                throw myException("no parent link has been removed -- heap::extractMin");
            }
            if(currentLastNode == -1){
                heap_node **newLastLine = new heap_node*[lastLineSize/2];
                for(int i = 0;i<lastLineSize/2;i++){
                    newLastLine[i] = lastLine[i*2]->parent;
                }
                delete [] lastLine;
                lastLine = newLastLine;
                currentLastNode = lastLineSize/2 - 1;
                lastLineSize /= 2;
            }

            bubbleDown(last);
            delete ptr;
            return value;
        }
        /*
        adding an element to the heap
        */
        heap_node *insert(int value){
            heap_node *newNode = new heap_node(value, this);

            if(!head){ //if we import first element
                lastLine = new heap_node*[1];
                lastLine[0] = newNode;
                lastLineSize = 1;
                head = newNode;
                return newNode;
            }

            if(currentLastNode == lastLineSize-1 //if its the last one we gotta create a new array
            && lastLine[currentLastNode]->childLeft 
            && lastLine[currentLastNode]->childRight){
                heap_node **newLastLine = new heap_node*[lastLineSize*2];
                for(int i = 0;i<lastLineSize;i++){
                    newLastLine[i*2] = lastLine[i]->childLeft;
                    newLastLine[i*2+1] = lastLine[i]->childRight;
                }
                delete [] lastLine;
                lastLine = newLastLine;
                currentLastNode = 0;
                lastLineSize *= 2;
            }

            else if(lastLine[currentLastNode]->childLeft
            && lastLine[currentLastNode]->childRight){
                currentLastNode++;
            }

            newNode->parent = lastLine[currentLastNode];
            if(!lastLine[currentLastNode]->childLeft){
                if(lastLine[currentLastNode]->childRight){
                    throw myException("corrupted heap - the child left is nullptr but not the child right -- heap::insert");
                }
                newNode->parent->childLeft = newNode;
            }

            else if(lastLine[currentLastNode]->childLeft){
                newNode->parent->childRight = newNode;
            }
            bubbleUp(newNode);
            return newNode;
        }
};
#endif // HEAP_H