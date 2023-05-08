#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "myException.h"
template <typename T> class linked_list;
template <typename T> class Node {
    template <typename U> friend class linked_list;
    public:
        T value;
        /*
        returns a pointer to a next Node
        */
        Node<T> *nextNode(){
            return next;
        }
        /*
        returns a pointer to the list this node is in
        */
        linked_list<T> *list(){
            return currentList;
        }
    private:
        Node<T> *next = nullptr;
        linked_list<T> *currentList;
        ~Node(){}
        Node(T value, linked_list<T>*currentList){
            this->value = value;
            this->currentList = currentList;
        }
        
};
template <typename T> class linked_list {//Singly linked list
    
    private:
        Node<T> *head = nullptr;
        Node<T> *last = nullptr;
        int l = 0; //length of the list
    public:
        ~linked_list(){
            clear();
        }
        /*
        clears the linked_list's elements
        */
        void clear(){
            Node<T> *pointer = head;
            Node<T> *tmp;
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
        T *exportAsAnArray(){
            if(!l){
                throw myException("cannot export an array with size of 0 -- linked_list::exportAsAnArray");
            }
            T *arrayToBeReturned = new T[l];
            Node<T>*pointer = head;
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
                Node<T> *nextNode = head->next;
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
        the passed pointer must point to an element contained in THIS linked_list - otherwise it throws an exception
        */
        void remove(Node<T> *previousNode){//pointer to a Node<T> after which we want to remove
            if(!previousNode){
                throw myException("the passed !pointer -- linked_list::remove");
            }
            if(previousNode->list() != this){
                throw myException("the passed pointer is to an element which isn't contained in this linked_list. you need to call the function from it's own linked_list -- linked_list::remove");
            }
            if(previousNode->next == last){
                last = previousNode;
            }
            if(previousNode->next){
                Node<T> *nextNode = previousNode->next->next;
                delete previousNode->next;
                l--;
                previousNode->next = nextNode;
            }
            else{
                throw myException("there is nothing after this Node<T> -- linked_list::remove");
            }
        }
        /*
        inserts an element between two elements
        previousNode is a pointer of an element after which you want insert
        make sure that the passed pointer is not a nullptr otherwise it throws an exception
        the passed pointer must point to an element contained in THIS linked_list - otherwise it throws an exception
        */
        void insert(Node<T> *previousNode, T value){//pointer to the node after which we want to insert
            if(!previousNode){
                throw myException("the passed !pointer -- linked_list::insert");
            }
            if(previousNode->list() != this){
                throw myException("the passed pointer is to an element which isn't contained in this linked_list. you need to call the function from it's own linked_list -- linked_list::insert");
            }
            Node<T> *newNode;
            newNode = new Node<T>(value, this);
            newNode->next = previousNode->next;
            previousNode->next = newNode;
            if(previousNode == last)last = newNode;
            l++;
        }
        /*
        inserts an element between two elements
        i is index of an element after which you want insert -- inneficient with bigger i's
        make sure that there is an element in the linked_list and that 0 <= i < l otherwise it throws an exception
        */
        void insert(int i, T value){
            if(!head){
                throw myException("there is nothing to insert after - the linked list is empty -- linked_list::insert");
            }
            if(l<=i){
                throw myException("value on this index is out of range of this linked_list -- linked_list::insert");
            }
            if(i<0){
                throw myException("invalid index - index smaller than 0 -- linked_list::insert");
            }
            insert(accessNode(i), value);
        }
        /*
        returns a pointer to a specific node -- inneficient with bigger i's
        make sure that there is an element in the linked_list and that 0 <= i < l otherwise it throws an exception
        */
        Node<T> *accessNode(int i){
            if(!head){
                throw myException("there is nothing to access - the linked list is empty -- linked_list::accessNode");
            }
            if(l<=i){
                throw myException("value on this index is out of range of this linked_list -- linked_list::accessNode");
            }
            if(i<0){
                throw myException("invalid index - index smaller than 0 -- linked_list::accessNode");
            }
            Node<T> *pointer = head;
            while(i--){
                pointer = pointer->next;
            }
            return pointer;
        }
        /*
        creates a new element at the end of the list
        */
        void append(T value){
            Node<T> *newitem;
            newitem = new Node(value, this);
            if(!last){
                last = newitem;
                head = newitem;
            }
            else{
                last->next = newitem;
                last = newitem;
            }
            l++;
        }
        /*
        creates a new element at the start of the list
        */
        void appendToStart(T value){
            Node<T> *newItem;
            newItem = new Node(value,this);
            newItem->next = head;
            if(!head){
                last = newItem;
                head = newItem;
            }
            else{
                head = newItem;
            }
            l++;
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
            Node<T> *pointer = head;
            while(pointer){
                std::cout << pointer->value << " ";
                pointer = pointer->next;
            }
        }
        //------------------------needs to be tested---------------------------------
        /*
        !INEFICCIENT DONT CALL REPEATEDLY!
        Goes through every element in the linked_list until it finds the right value and returns pointer to this element
        make sure that there is ate least one element in the list otherwise it throws an exception
        */
        Node<T> *searchFor(T value){
            return searchFor(value, head);
        }
        /*
        !INEFICCIENT DONT CALL REPEATEDLY!
        Goes through every element in the linked_list starting from the startingPoint until it finds the right value and returns a pointer to this element
        make sure that there is at least one element in the list and that startingPoint is not a nullptr otherwise it throws an exception
        the passed pointer must point to an element contained in THIS linked_list - otherwise it throws an exception
        */
        Node<T>*searchFor(T value, Node<T> *startingPoint){
            if(!head){
                throw myException("there is nothing to search for - the linked list is empty -- linked_list::searchFor");
            }
            if(!startingPoint){
                throw myException("the passed !pointer -- linked_list::searchFor");
            }
            if(startingPoint->list() != this){
                throw myException("the passed pointer is to an element which isn't contained in this linked_list. you need to call the function from it's own linked_list -- linked_list::searchFor");
            }
            Node<T> *pointer = startingPoint;
            while(pointer){
                if(pointer->value == value)return pointer;
                pointer = pointer->next;
            }
            return nullptr;
        }
        /*
        !INEFICCIENT DONT CALL REPEATEDLY!
        Goes through every element in the linked_list until it finds the same node as targetNode and returns an index to this element
        make sure that there is at least one element in the list otherwise it throws an exception
        the passed pointer must point to an element contained in THIS linked_list - otherwise it throws an exception
        */
        int searchFor_getIndex(Node<T> *targetNode){
            if(targetNode->list() != this){
                throw myException("the passed pointer is to an element which isn't contained in this linked_list. you need to call the function from it's own linked_list -- linked_list::searchFor_getIndex");
            }
            return searchFor_getIndex(targetNode, head);
        }
        /*
        !INEFICCIENT DONT CALL REPEATEDLY!
        Goes through every element in the linked_list starting from StartingPoint until it finds the same node as targetNode and returns a index to this element
        make sure that there is at least one element in the list and the passed startingPoint is not a nullptr otherwise it throws an exception
        the passed pointers must point to an element contained in THIS linked_list - otherwise it throws an exception
        */
        int searchFor_getIndex(Node<T> *targetNode, Node<T> *startingPoint){//INEFICCIENT DONT CALL REPEATEDLY
            if(!head){
                throw myException("there is nothing to search for - the linked list is empty -- linked_list::searchFor_getIndex");
            }
            if(!startingPoint){
                throw myException("the passed !pointer -- linked_list::searchFor");
            }
            if(targetNode->list() != this){
                throw myException("the passed pointer is to an element which isn't contained in this linked_list. you need to call the function from it's own linked_list -- linked_list::searchFor_getIndex(TargetNode)");
            }
            if(startingPoint->list() != this){
                throw myException("the passed pointer is to an element which isn't contained in this linked_list. you need to call the function from it's own linked_list -- linked_list::searchFor_getIndex(StartingPoint)");
            }
            int i = 0;
            Node<T> *pointer = startingPoint;
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
        make sure that there is at least one element in the list otherwise it throws an exception
        */
        int searchFor_getIndex(T value){//INEFICCIENT DONT CALL REPEATEDLY
            return searchFor_getIndex(value, 0);
        }
        /*
        !INEFICCIENT DONT CALL REPEATEDLY!
        Goes through every element in the linked_list starting from StartingPoint until it finds the target value and returns an index to this element
        make sure that there is at least one element in the list and the passed startingPoint is not a nullptr otherwise it throws an exception
        */
        int searchFor_getIndex(T value, int startingPoint){//INEFICCIENT DONT CALL REPEATEDLY
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
            Node<T> *pointer = head;
            while(pointer){
                if(pointer->value == value && i>=startingPoint)return i;
                pointer = pointer->next;
                i++;
            }
            return -1;
        }

};
#endif //LINKED_LIST_H