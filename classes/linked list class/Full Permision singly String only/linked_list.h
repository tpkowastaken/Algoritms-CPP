#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "myException.h"
class Node {
    public:
        std::string value;
        Node *next;
};
class linked_list {//Singly linked list
    private:
        Node *head = nullptr;
        Node *last = nullptr;
        int l = 0; //length of the list
    public:
        ~linked_list(){
            clear();
        }
        /*
        clears the linked_list's elements
        */
        void clear(){
            Node *pointer = head;
            Node *tmp;
            while(pointer){
                tmp = pointer->next;
                delete pointer;
                pointer = tmp;
            }
            l = 0;
            head = nullptr;
            last = nullptr;
        }
        /*
        returns a pointer to a newly created array with the size of linked_list::size
        make sure that there is at least 1 element in the linked_list - otherwise it will throw myException(an exception
        */
        std::string *exportAsAnArray(){
            if(!l){
                throw myException("cannot export an array with size of 0 -- linked_list::exportAsAnArray");
            }
            std::string *arrayToBeReturned = new std::string[l];
            Node *pointer = head;
            int i = 0;
            while(pointer){
                arrayToBeReturned[i] = pointer->value;
                pointer = pointer->next;
                i++;
            }
            return arrayToBeReturned;
        }
        /*
        removes an element on an index i -- inneficient with bigger i's
        make sure that there is an element in the linked list and that 0 <= i < l otherwise it will throw myException(an exception
        */
        void remove(int i){
            if(!head){
                throw myException("there is nothing to remove - the linked list is empty -- linked_list::remove");
            }
            if(l<=i){
                throw myException("value on this index is out of range of this linked_list -- linked_list::remove");
            }
            if(i<0){
                throw myException("invalid index - index smaller than 0 -- linked_list::remove");
            }
            if(!i && head){//deleting the first one
                if(last == head)last = head->next;
                Node *nextNode = head->next;
                delete head;
                i--;
                head = nextNode;
            }
            else remove(accessNode(i-1));
        }
        /*
        returns a boolian about if the linked_list is empty
        */
        bool isEmpty(){
            if(!head)return true;
            else return false;
        }
        /*
        removes an element
        previousNode is a pointer of an element after which you want to remove
        make sure that the passed pointer is not a nullptr and that there is an element after this one otherwise it throws an exception
        */
        void remove(Node *previousNode){//pointer to a Node after which we want to remove
            if(!previousNode){
                throw myException("the passed !pointer -- linked_list::remove");
            }
            if(previousNode->next == last){
                last = previousNode;
            }
            if(previousNode->next){
                Node *nextNode = previousNode->next->next;
                delete previousNode->next;
                l--;
                previousNode->next = nextNode;
            }
            else{
                throw myException("there is nothing after this Node -- linked_list::remove");
            }
        }
        /*
        inserts an element between two elements
        previousNode is a pointer of an element after which you want insert
        make sure that the passed pointer is not a nullptr otherwise it throws an exception
        */
        Node *insert(Node *previousNode, std::string value){//pointer to the node after which we want to insert
            if(!previousNode){
                throw myException("the passed !pointer -- linked_list::insert");
            }
            Node *newNode;
            newNode = new Node;
            newNode->value = value;
            newNode->next = previousNode->next;
            previousNode->next = newNode;
            if(previousNode == last)last = newNode;
            l++;
            return newNode;
        }
        /*
        inserts an element between two elements
        i is index of an element after which you want insert -- inneficient with bigger i's
        make sure that there is an element in the linked_list and that 0 <= i < l otherwise it throws an exception
        */
        Node *insert(int i, std::string value){
            if(!head){
                throw myException("there is nothing to insert after - the linked list is empty -- linked_list::insert");
            }
            if(l<=i){
                throw myException("value on this index is out of range of this linked_list -- linked_list::insert");
            }
            if(i<0){
                throw myException("invalid index - index smaller than 0 -- linked_list::insert");
            }
            return insert(accessNode(i), value);
        }
        /*
        returns a pointer to a specific node -- inneficient with bigger i's
        make sure that there is an element in the linked_list and that 0 <= i < l otherwise it throws an exception
        */
        Node *accessNode(int i){
            if(!head){
                throw myException("there is nothing to access - the linked list is empty -- linked_list::accessNode");
            }
            if(l<=i){
                throw myException("value on this index is out of range of this linked_list -- linked_list::accessNode");
            }
            if(i<0){
                throw myException("invalid index - index smaller than 0 -- linked_list::accessNode");
            }
            Node *pointer = head;
            while(i--){
                pointer = pointer->next;
            }
            return pointer;
        }
        /*
        creates a new element at the end of the list
        */
        Node *append(std::string value){
            Node *newitem;
            newitem = new Node();
            newitem->value = value;
            newitem->next = nullptr;
            if(!last){
                last = newitem;
                head = newitem;
            }
            else{
                last->next = newitem;
                last = newitem;
            }
            l++;
            return newitem;
        }
        /*
        creates a new element at the start of the list
        */
        Node *appendToStart(std::string value){
            Node *newItem;
            newItem = new Node();
            newItem->value = value;
            newItem->next = head;
            if(!head){
                last = newItem;
                head = newItem;
            }
            else{
                head = newItem;
            }
            l++;
            return newItem;
        }
        /*
        returns size of the linked_list
        */
        int size(){
            return l;
        }
        /*
        prints every element in the list from first to last
        */
        void print(){
            Node *pointer = head;
            while(pointer){
                std::cout << pointer->value << " ";
                pointer = pointer->next;
            }
        }
        //------------------------needs to be tested---------------------------------
        /*
        !INEFICCIENT DONT CALL REPEATEDLY!
        Goes through every element in the linked_list until it finds the right value and returns pointer to this element
        make sure that there is an element in the list otherwise it throws an exception
        */
        Node *searchFor(std::string value){
            return searchFor(value, head);
        }
        /*
        !INEFICCIENT DONT CALL REPEATEDLY!
        Goes through every element in the linked_list starting from the startingPoint until it finds the right value and returns a pointer to this element
        make sure that there is an element in the list and that startingPoint is not a nullptr otherwise it throws an exception
        */
        Node *searchFor(std::string value, Node *startingPoint){
            if(!head){
                throw myException("there is nothing to search for - the linked list is empty -- linked_list::searchFor");
            }
            if(!startingPoint){
                throw myException("the passed !pointer -- linked_list::searchFor");
            }
            Node *pointer = startingPoint;
            while(pointer){
                if(pointer->value == value)return pointer;
                pointer = pointer->next;
            }
            return nullptr;
        }
        /*
        !INEFICCIENT DONT CALL REPEATEDLY!
        Goes through every element in the linked_list until it finds the same node as targetNode and returns an index to this element
        make sure that there is an element in the list otherwise it throws an exception
        */
        int searchFor_getIndex(Node *targetNode){
            return searchFor_getIndex(targetNode, head);
        }
        /*
        !INEFICCIENT DONT CALL REPEATEDLY!
        Goes through every element in the linked_list starting from StartingPoint until it finds the same node as targetNode and returns a index to this element
        make sure that there is an element in the list and the passed startingPoint is not a nullptr otherwise it throws an exception
        */
        int searchFor_getIndex(Node *targetNode, Node *startingPoint){//INEFICCIENT DONT CALL REPEATEDLY
            if(!head){
                throw myException("there is nothing to search for - the linked list is empty -- linked_list::searchFor_getIndex");
            }
            if(!startingPoint){
                throw myException("the passed !pointer -- linked_list::searchFor");
            }
            int i = 0;
            Node *pointer = startingPoint;
            while(pointer){
                if(pointer == targetNode)return i;
                pointer = pointer->next;
                i++;
            }
            return -1;
        }
        /*
        !INEFICCIENT DONT CALL REPEATEDLY!
        Goes through every element in the linked_list until it finds the target value and returns an index to this element
        make sure that there is an element in the list otherwise it throws an exception
        */
        int searchFor_getIndex(std::string value){//INEFICCIENT DONT CALL REPEATEDLY
            return searchFor_getIndex(value, 0);
        }
        /*
        !INEFICCIENT DONT CALL REPEATEDLY!
        Goes through every element in the linked_list starting from StartingPoint until it finds the target value and returns an index to this element
        make sure that there is an element in the list and the passed startingPoint is not a nullptr otherwise it throws an exception
        */
        int searchFor_getIndex(std::string value, int startingPoint){//INEFICCIENT DONT CALL REPEATEDLY
            if(!head){
                throw myException("there is nothing to search for - the linked list is empty -- linked_list::searchFor_getIndex");
            }
            if(l<=startingPoint){
                throw myException("value on this starting point index is out of range of this linked_list -- linked_list::searchFor_getIndex");
            }
            if(startingPoint<0){
                throw myException("invalid starting point index - starting point index smaller than 0 -- linked_list::searchFor_getIndex");
            }
            int i = 0;
            Node *pointer = head;
            while(pointer){
                if(pointer->value == value && i>=startingPoint)return i;
                pointer = pointer->next;
                i++;
            }
            return -1;
        }

};
#endif //LINKED_LIST_H