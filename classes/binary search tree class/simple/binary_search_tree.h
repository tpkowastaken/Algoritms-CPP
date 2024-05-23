#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include "myException.h"
class binary_search_tree;
class binary_node{
    friend class binary_search_tree;
    public:
        int value;
        binary_search_tree *currentTree(){
            return tree;
        }
        binary_node *parentNode(){
            return parent;
        }
        binary_node *childBiggerNode(){
            return childBigger;
        }
        binary_node *childSmallerNode(){
            return childSmaller;
        }
    private:
        binary_node(int value,binary_search_tree *tree){
            this->value = value;
            this->tree = tree;
        }
        ~binary_node(){}
        binary_search_tree *tree = nullptr;
        binary_node *parent = nullptr;
        binary_node *childSmaller = nullptr;
        binary_node *childBigger = nullptr;
};
class binary_search_tree{
    private:
        binary_node *head = nullptr;
        binary_node *lowest = nullptr;
        binary_node *highest = nullptr;
        int count = 0; // number of nodes in the tree
        /*
        removes everything under the node - it's private because it doesn't restore any pointer bonds
        */
        void forceRemove(binary_node *forceRemovedTree){
            if(forceRemovedTree->childBigger){
                forceRemove(forceRemovedTree->childBigger);
            }
            if(forceRemovedTree->childSmaller){
                forceRemove(forceRemovedTree->childSmaller);
            }
            delete forceRemovedTree;
        }
        /*
            operation is either insert - 1 or remove - 0
            Fromleft is if the signal is sent from the left or right (from smaller or bigger child)
        */
        void swap(binary_node *firstNode, binary_node *secondNode){//we could also transform just the value but that wont keep the same value to a pointer
            if(!firstNode){
                throw myException("passed pointer firstNode == nullptr -- heap::swap");
            }
            if(!secondNode){
                throw myException("passed pointer secondNode == nullptr -- heap::swap");
            }
            if(firstNode->tree != this){
                throw myException("passed pointer firstNode is from a different heap -- heap::swap");
            }
            if(secondNode->tree != this){
                throw myException("passed pointer secondNode is from a different heap -- heap::swap");
            }
            bool connectedCall = false;
            if(secondNode->parent == firstNode){
                binary_node *tmp = firstNode;
                firstNode = secondNode;
                secondNode = tmp;
            }
            if(firstNode->parent == secondNode){
                connectedCall = true;
            }
            if(firstNode == head){
                head = secondNode;
            }
            else if(secondNode == head){
                head = firstNode;
            }

            //telling parent about the new relation
            if(secondNode->parent){
                if(secondNode->parent->childSmaller == secondNode){
                    secondNode->parent->childSmaller = firstNode;
                }
                else if(secondNode->parent->childBigger == secondNode){
                    secondNode->parent->childBigger = firstNode;
                }
            }
            if(!connectedCall && firstNode->parent){
                if(firstNode->parent->childSmaller == firstNode){
                    firstNode->parent->childSmaller = secondNode;
                }
                else if(firstNode->parent->childBigger == firstNode){
                    firstNode->parent->childBigger = secondNode;
                }
            }

            //assigning to the nodes themselves
            if(firstNode->parent == secondNode && firstNode == secondNode->childSmaller){
                binary_node *firstNodeRightChild = firstNode->childBigger;
                binary_node *secondNodeParent = secondNode->parent;

                firstNode->childBigger = secondNode->childBigger;
                secondNode->childSmaller = firstNode->childSmaller;

                secondNode->parent = firstNode;//custom for every if
                firstNode->childSmaller = secondNode;//custom for every if

                firstNode->parent = secondNodeParent;
                secondNode->childBigger = firstNodeRightChild;
            }
            else if(firstNode->parent == secondNode && firstNode == secondNode->childBigger){//
                binary_node *firstNodeLeftChild = firstNode->childSmaller;
                binary_node *secondNodeParent = secondNode->parent;

                firstNode->childSmaller = secondNode->childSmaller;
                secondNode->childBigger = firstNode->childBigger;

                secondNode->parent = firstNode;//custom for every if
                firstNode->childBigger = secondNode;//custom for every if

                firstNode->parent = secondNodeParent;
                secondNode->childSmaller = firstNodeLeftChild;

            }
            else if(!connectedCall){
                binary_node *firstNodeChildLeft = firstNode->childSmaller;
                binary_node *firstNodeChildRight = firstNode->childBigger;
                binary_node *firstNodeParent = firstNode->parent;

                firstNode->childSmaller = secondNode->childSmaller;
                firstNode->childBigger = secondNode->childBigger;
                firstNode->parent = secondNode->parent;

                secondNode->childSmaller = firstNodeChildLeft;
                secondNode->childBigger = firstNodeChildRight;
                secondNode->parent = firstNodeParent;

            }
            //telling childs about the new relations
            if(firstNode->childSmaller){
                firstNode->childSmaller->parent = firstNode;
            }
            if(firstNode->childBigger){
                firstNode->childBigger->parent = firstNode;
            }
            if(secondNode->childSmaller){
                secondNode->childSmaller->parent = secondNode;
            }
            if(secondNode->childBigger){
                secondNode->childBigger->parent = secondNode;
            }
        }
    public:
        ~binary_search_tree(){
            clear();
        }
        void verify(binary_node *StartingPoint = NULL, binary_node *parent = nullptr){
            if(StartingPoint == NULL){
                StartingPoint = head;
            }
            else if(StartingPoint == nullptr){
                throw myException("error while verifying binary search tree - startingpoint == nullptr -- binary_search_tree::verify");
            }
            if(parent){
                if(StartingPoint->parent != parent){
                    throw myException("corrupted parent -- binary_search_tree::verify");
                }
            }
            if(StartingPoint->childBigger && StartingPoint->childSmaller){
                if(StartingPoint->childBigger->value <= StartingPoint->childSmaller->value){
                    throw myException("bigger child smaller or equal to smaller child -- binary_search_tree::verify");
                }
            }
            if(StartingPoint->childBigger){
                verify(StartingPoint->childBigger, StartingPoint);
            }
            if(StartingPoint->childSmaller){
                verify(StartingPoint->childSmaller, StartingPoint);
            }
        }
        binary_node *accessHead(){
            return head;
        }
        /*
        clears the whole binary search tree and restores it to its state before inserting anything
        */
        void clear(){
            if(!head)return;
            forceRemove(head);
            head = nullptr;
            lowest = nullptr;
            highest = nullptr;
            count = 0;
        }
        /*
        searches for a value in the whole binary search tree and returns a pointer to that value.
        If it doesn't find anything it returns a nullptr
        */
        binary_node *searchFor(int value){
            if(!head){
                throw myException("there is nothing to searchFor in this binary search tree - it's empty -- binary_search_tree::searchFor");
            }
            return searchFor(value, head);
        }
        /*
        searches for a value in the binary search tree starting from the StartingPoint and returns a pointer to that value.
        If it doesn't find anything it returns a nullptr
        make sure to pass the poniter to a node which is included in the same binary tree that you're calling it from, otherwise it throws an exception
        */
        binary_node *searchFor(int value, binary_node *StartingPoint){
            if(!StartingPoint){
                throw myException("the passed !pointer -- binary_search_tree::searchFor");
            }
            if(StartingPoint->currentTree() != this){
                throw myException("the passed pointer is included in a different binary search tree. Please call this function from that tree -- binary_search_tree::searchFor");
            }
            if(StartingPoint->value == value){
                return StartingPoint;
            }
            if(StartingPoint->value > value){
                if(!StartingPoint->childSmaller)return nullptr;
                return searchFor(value, StartingPoint->childSmaller);
            }
            if(StartingPoint->value < value){
                if(!StartingPoint->childBigger)return nullptr;
                return searchFor(value, StartingPoint->childBigger);
            }
            return nullptr;
        }
        /*
        prints the whole binary tree from first to last
        */
        void print(){
            if(!head){
                throw myException("there is nothing to print because the tree is empty! -- binary_search_tree::printfrom");
            }
            printfrom(head,1);
        }
        /*
        prints the whole binary tree
        fromStartToFinish sets the direction
        true = From start to finish: 1,2,3,4,5
        false = From finish to start: 5,4,3,2,1
        */
        void print(bool fromStartToFinish){
            if(!head){
                throw myException("there is nothing to print because the tree is empty! -- binary_search_tree::printfrom");
            }
            printfrom(head,fromStartToFinish);
        }
        /*
        prints the binary tree from the passed pointer
        fromStartToFinish sets the direction
        true = From start to finish: 1,2,3,4,5
        false = From finish to start: 5,4,3,2,1
        */
        void printfrom(binary_node *ptr, bool fromStartToFinish){
            if(!ptr){
                throw myException("passed !pointer -- binary_search_tree::printfrom");
            }
            if(ptr->currentTree() != this){
                throw myException("the passed pointer is included in a different binary search tree. Please call this function from that tree -- binary_search_tree::printfrom");
            }
            if(!ptr->childBigger && !ptr->childSmaller){
                std::cout << ptr->value << ", ";
                return;
            }
            if(fromStartToFinish){

                if(ptr->childSmaller){
                    printfrom(ptr->childSmaller, fromStartToFinish);
                }

                std::cout << ptr->value << ", ";

                if(ptr->childBigger){
                    printfrom(ptr->childBigger, fromStartToFinish);
                }

            }
            else{

                if(ptr->childBigger){
                    printfrom(ptr->childBigger, fromStartToFinish);
                }

                std::cout << ptr->value << ", ";

                if(ptr->childSmaller){
                    printfrom(ptr->childSmaller, fromStartToFinish);
                }
            }
        }
        int size(){
            return count;
        }
        binary_node *accessFirstNode(){
            return head;
        }
        /*
        searching for the lowest element manually (slower that lowestNode) from a specific place
        and returns a pointer to it
        */
        binary_node *low(binary_node *startingNode){
            if(!startingNode){
                throw myException("the passed pointer !startingNode -- binary_search_tree::low");
            }
            if(startingNode->currentTree() != this){
                throw myException("the passed pointer is included in a different binary search tree. Please call this function from that tree -- binary_search_tree::low");
            }
            while(startingNode->childSmallerNode()){
                startingNode = startingNode->childSmallerNode();
            }
            return startingNode;
        }
        /*
        searching for the highest element manually (slower that highestNode) from a specific place
        and returns a pointer to it
        */
        binary_node *max(binary_node *startingNode){
            if(!startingNode){
                throw myException("the passed pointer !startingNode -- binary_search_tree::max");
            }
            if(startingNode->currentTree() != this){
                throw myException("the passed pointer is included in a different binary search tree. Please call this function from that tree -- binary_search_tree::max");
            }
            while(startingNode->childBiggerNode()){
                startingNode = startingNode->childBiggerNode();
            }
            return startingNode;
        }
        /*
        returns a pointer to a preindexed highest node
        */
        binary_node *highestNode(){
            return highest;
        }
        /*
        returns a pointer to a preindexed lowest node
        */
        binary_node *lowestNode(){
            return lowest;
        }
        /*
        removes the Node that is passed in and replaces it with a different Node or nullptr
        be careful to not pass nullptr as the pointer because it will throw an exception
        */
        void remove(binary_node *nodeToBeRemoved){
            if(!nodeToBeRemoved){
                throw myException("the passed !pointer -- binary_search_tree::remove");
            }
            if(nodeToBeRemoved->currentTree() != this){
                throw myException("the passed pointer is included in a different binary search tree. Please call this function from that tree -- binary_search_tree::remove");
            }
            remove(nodeToBeRemoved, 1);
        }
        /*
        removes the Node that is passed in and replaces it with a different Node or nullptr
        be careful to not pass nullptr as the pointer because it will throw an exception
        scanSmaller scans the smaller child of the nodeToBeRemoved if set to true - good for cases where you know that there is less nodes on one side
        (you want to call the one with less nodes because it's faster)
        */
        void remove(binary_node *nodeToBeRemoved, bool scanSmaller){
            if(!nodeToBeRemoved){
                throw myException("the passed !pointer -- binary_search_tree::remove");
            }
            if(nodeToBeRemoved->currentTree() != this){
                throw myException("the passed pointer is included in a different binary search tree. Please call this function from that tree -- binary_search_tree::remove");
            }

            binary_node *target = nullptr;
            const bool BOTH_CHILD_NULLPTR = (!nodeToBeRemoved->childBigger && !nodeToBeRemoved->childSmaller)? 1 : 0;

            if(!nodeToBeRemoved->childBigger && nodeToBeRemoved->childSmaller){
                target = nodeToBeRemoved->childSmaller;
                target->parent = nodeToBeRemoved->parent;
                if(nodeToBeRemoved->parentNode()){
                    nodeToBeRemoved->parent->childBigger = nodeToBeRemoved == nodeToBeRemoved->parent->childBigger? target : nodeToBeRemoved->parent->childBigger;//here!**(creating bonds at new place)
                    nodeToBeRemoved->parent->childSmaller = nodeToBeRemoved == nodeToBeRemoved->parent->childSmaller? target : nodeToBeRemoved->parent->childSmaller;
                }
                else{
                    head = target;
                }
            }

            else if(!nodeToBeRemoved->childSmaller && nodeToBeRemoved->childBigger){
                target = nodeToBeRemoved->childBigger;
                target->parent = nodeToBeRemoved->parent;
                if(nodeToBeRemoved->parentNode()){
                    nodeToBeRemoved->parent->childBigger = nodeToBeRemoved == nodeToBeRemoved->parent->childBigger? target : nodeToBeRemoved->parent->childBigger;//here!**(creating bonds at new place)
                    nodeToBeRemoved->parent->childSmaller = nodeToBeRemoved == nodeToBeRemoved->parent->childSmaller? target : nodeToBeRemoved->parent->childSmaller;
                }
                else{
                    head = target;
                }
            }
            else if(scanSmaller && !BOTH_CHILD_NULLPTR){
                target = max(nodeToBeRemoved->childSmaller);
                swap(nodeToBeRemoved, target);
                if(nodeToBeRemoved->parent){
                    nodeToBeRemoved->parent->childBigger = nodeToBeRemoved->parent->childBigger == nodeToBeRemoved? nodeToBeRemoved->childSmaller : nodeToBeRemoved->parent->childBigger;
                    nodeToBeRemoved->parent->childSmaller = nodeToBeRemoved->parent->childSmaller == nodeToBeRemoved? nodeToBeRemoved->childSmaller : nodeToBeRemoved->parent->childSmaller;
                }
                if(nodeToBeRemoved->childSmaller){
                    nodeToBeRemoved->childSmaller->parent = nodeToBeRemoved->parent;
                }
            }

            else if(!BOTH_CHILD_NULLPTR){
                target = low(nodeToBeRemoved->childBigger);
                swap(nodeToBeRemoved, target);
                if(nodeToBeRemoved->parent){
                    nodeToBeRemoved->parent->childBigger = nodeToBeRemoved->parent->childBigger == nodeToBeRemoved? nodeToBeRemoved->childBigger : nodeToBeRemoved->parent->childBigger;
                    nodeToBeRemoved->parent->childSmaller = nodeToBeRemoved->parent->childSmaller == nodeToBeRemoved? nodeToBeRemoved->childBigger : nodeToBeRemoved->parent->childSmaller;
                }
                if(nodeToBeRemoved->childBigger){
                    nodeToBeRemoved->childBigger->parent = nodeToBeRemoved->parent;
                }
            }
            if(BOTH_CHILD_NULLPTR && nodeToBeRemoved->parent){
                nodeToBeRemoved->parent->childBigger = nodeToBeRemoved->parent->childBigger == nodeToBeRemoved? nullptr : nodeToBeRemoved->parent->childBigger;
                nodeToBeRemoved->parent->childSmaller = nodeToBeRemoved->parent->childSmaller == nodeToBeRemoved? nullptr : nodeToBeRemoved->parent->childSmaller;
            }
            if(nodeToBeRemoved == head && target){
                head = target;
            }
            else if(nodeToBeRemoved == head){
                head = nullptr;
            }
            if(nodeToBeRemoved == highest){
                highest = nodeToBeRemoved->parent;
            }
            if(nodeToBeRemoved == lowest){
                lowest = nodeToBeRemoved->parent;
            }

            delete nodeToBeRemoved;
            count--;
        }

        binary_node *insert(int value){
            binary_node *newNode = new binary_node(value, this);
            if(!head){
                head = newNode;
                lowest = newNode;
                highest = newNode;
                count++;
                return newNode;
            }
            binary_node *ptr = head;
            int i = 1;
            while(true){
                if(ptr->value == value){
                    throw myException("the value is already in the binary_search_tree -- binary_search_tree::insert");
                }
                if(ptr->value > value && ptr->childSmaller){
                    ptr = ptr->childSmaller;
                    i++;
                    continue;
                }
                if(ptr->value > value && !ptr->childSmaller){
                    ptr->childSmaller = newNode;
                    newNode->parent = ptr;
                    lowest = lowest->value > value ? newNode : lowest;
                    count++;
                    return newNode;
                }
                if(ptr->value < value && ptr->childBigger){
                    ptr = ptr->childBigger;
                    i++;
                    continue;
                }
                if(ptr->value < value && !ptr->childBigger){
                    ptr->childBigger = newNode;
                    newNode->parent = ptr;
                    highest = highest->value < value ? newNode : highest;
                    count++;
                    return newNode;
                }
            }

        }

};
#endif //BINARY_SEARCH_TREE_H