#include <iostream>
class myException{
    public:
        const char *error;
        myException(const char *error){
            this->error = error;
            printf("\n%s\n", error);
        }
};
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
        returns a pointer to a previous Node
        */
        Node<T> * previousNode(){
            return previous;
        }
        /*
        returns a pointer to the list this node is in
        */
        linked_list<T> *list(){
            return currentList;
        }
    private:
        Node<T> *next = nullptr;
        Node<T> *previous = nullptr;
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
        Node<T> *lastNode(){
            return last;
        }
        Node<T> *firstNode(){
            return head;
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
        returns a boolian about if the linked_list is empty
        */
        bool isEmpty(){
            if(!head)return true;
            else return false;
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
        removes an element on an index i -- the closer it gets to i/2 the more inefficient it becomes
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
            remove(accessNode(i));
        }
        /*
        removes an element
        make sure that the passed pointer is not a nullptr and that there is an element after this one otherwise it throws an exception
        the passed pointer must point to an element contained in THIS linked_list - otherwise it throws an exception
        */
        void remove(Node<T> *NodeToBeRemoved){//pointer to a Node<T> which we want to remove
            if(!NodeToBeRemoved){
                throw myException("the passed !pointer -- linked_list::remove");
            }
            if(NodeToBeRemoved->list() != this){
                throw myException("the passed pointer is to an element which isn't contained in this linked_list. you need to call the function from it's own linked_list -- linked_list::remove");
            }
            if(NodeToBeRemoved == head){
                head = NodeToBeRemoved->next;
            }
            if(NodeToBeRemoved == last){
                last = NodeToBeRemoved->previous;
            }
            if(NodeToBeRemoved->next){
                NodeToBeRemoved->next->previous = NodeToBeRemoved->previous;
            }
            if(NodeToBeRemoved->previous){
                NodeToBeRemoved->previous->next = NodeToBeRemoved->next;
            }
            delete NodeToBeRemoved;
            l--;
        }
        /*
        inserts an element between two elements
        previousNode is a pointer of an element after which you want insert
        make sure that the passed pointer is not a nullptr otherwise it throws an exception
        the passed pointer must point to an element contained in THIS linked_list - otherwise it throws an exception
        */
        Node<T> *insertAfter(Node<T> *previousNode, T value){
            if(!previousNode){
                throw myException("the passed !pointer -- linked_list::insertAfter");
            }
            if(previousNode->list() != this){
                throw myException("the passed pointer is to an element which isn't contained in this linked_list. you need to call the function from it's own linked_list -- linked_list::insertAfter");
            }
            Node<T> *newNode;
            newNode = new Node<T>(value, this);
            //assigning pointers
            newNode->next = previousNode->next;
            newNode->previous = previousNode;
            previousNode->next = newNode;
            if(newNode->next){
                newNode->next->previous = newNode;
            }
            if(previousNode == last)last = newNode;
            l++;
            return newNode;
        }
        Node<T> *insertBefore(Node<T> *NodeToBeInsertedBefore, T value){
            if(!NodeToBeInsertedBefore){
                throw myException("the passed !pointer -- linked_list::insertBefore");
            }
            if(NodeToBeInsertedBefore->list() != this){
                throw myException("the passed pointer is to an element which isn't contained in this linked_list. you need to call the function from it's own linked_list -- linked_list::insertBefore");
            }
            Node<T> *newNode;
            newNode = new Node<T>(value, this);
            //assigning pointers
            newNode->next = NodeToBeInsertedBefore;
            newNode->previous = NodeToBeInsertedBefore->previous;
            NodeToBeInsertedBefore->previous = newNode;
            if(newNode->previous){
                newNode->previous->next = newNode;
            }
            if(NodeToBeInsertedBefore == head)head = newNode;
            l++;
            return newNode;
        }
        /*
        inserts an element between two elements
        i is index of an element after which you want insert -- the closer it gets to l/2 the more inefficient it gets
        make sure that there is an element in the linked_list and that 0 <= i < l otherwise it throws an exception
        */
        Node<T> *insert(int i, T value){
            if(!head){
                throw myException("there is nothing to insert after - the linked list is empty -- linked_list::insert");
            }
            if(l<=i){
                throw myException("value on this index is out of range of this linked_list -- linked_list::insert");
            }
            if(i<0){
                throw myException("invalid index - index smaller than 0 -- linked_list::insert");
            }
            return insertAfter(accessNode(i), value);
        }
        /*
        returns a pointer to a specific node -- inneficient the closer it gets to l/2
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
            if(l-i>l/2){//going from the start
                Node<T> *pointer = head;
                while(i--){
                    pointer = pointer->next;
                }
                return pointer;
            }
            else{//going from the end
                i = l-1-i;
                Node<T> *pointer = last;
                while(i--){
                    pointer = pointer->next;
                }
                return pointer;
            }
        }
        /*
        creates a new element at the end of the list
        */
        Node<T> *append(T value){
            Node<T> *newitem;
            newitem = new Node(value, this);
            if(!last){
                last = newitem;
                head = newitem;
            }
            else{
                last->next = newitem;
                newitem->previous = last;
                last = newitem;
            }
            l++;
            return newitem;
        }
        /*
        creates a new element at the start of the list
        */
        Node<T> *appendToStart(T value){
            Node<T> *newItem;
            newItem = new Node(value,this);
            newItem->next = head;
            if(!head){
                last = newItem;
                head = newItem;
            }
            else{
                head = newItem;
                newItem->next->previous = newItem;
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
            Node<T> *pointer = head;
            while(pointer){
                std::cout << pointer->value << " ";
                pointer = pointer->next;
            }
            std::cout << "\n";
        }
        /*
        prints every element in the list from last to first
        */
        void printLastToFirst(){
            Node<T> *pointer = last;
            while(pointer){
                std::cout << pointer->value << " ";
                pointer = pointer->previous;
            }
            std::cout << "\n";
        }
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
struct coordinate
{
    int x,y;
};
class binary_search_tree;
class binary_node{
    friend class binary_search_tree;
    public:
        int value;
        bool visited;
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
        char mark = 0;
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
        void simpleRotationRight(binary_node *balancingNode){
            if(!balancingNode){
                throw myException("balancing node == nullptr -- binary_search_tree::SimpleRotationRight");
            }
            //relations
            binary_node *x = balancingNode;
            binary_node *y = balancingNode->childSmaller;
            binary_node *b = balancingNode->childSmaller->childBigger;

            y->parent = x->parent;
            if(y->parent){
                y->parent->childBigger = y->parent->childBigger == x ? y : y->parent->childBigger;
                y->parent->childSmaller = y->parent->childSmaller == x ? y : y->parent->childSmaller;
            }
            else head = y;

            y->childBigger = x; 
            x->parent = y;


            x->childSmaller = b;
            if(b)b->parent = x;

            //marks

            x->mark = 0;
            y->mark = 0;

        }
        void simpleRotationLeft(binary_node *balancingNode){
            if(!balancingNode){
                throw myException("balancing node == nullptr -- binary_search_tree::simpleRotationLeft");
            }
            //relations
            binary_node *x = balancingNode;
            binary_node *y = balancingNode->childBigger;
            binary_node *b = balancingNode->childBigger->childSmaller;

            y->parent = x->parent;
            if(y->parent){
                y->parent->childBigger = y->parent->childBigger == x ? y : y->parent->childBigger;
                y->parent->childSmaller = y->parent->childSmaller == x ? y : y->parent->childSmaller;
            }
            else head = y;

            y->childSmaller = x; 
            x->parent = y;


            x->childBigger = b;
            if(b)b->parent = x;

            //marks

            x->mark = 0;
            y->mark = 0;
        }
        void doubleRotationRight(binary_node *balancingNode){
            if(!balancingNode){
                throw myException("balancing node == nullptr -- binary_search_tree::doubleRotationRight");
            }
            //relations
            binary_node *x = balancingNode;
            binary_node *y = balancingNode->childSmaller;
            binary_node *z = balancingNode->childSmaller->childBigger;
            binary_node *b = balancingNode->childSmaller->childBigger->childSmaller;
            binary_node *c = balancingNode->childSmaller->childBigger->childBigger;

            y->childBigger = b;
            if(b)b->parent = y;

            x->childSmaller = c;
            if(c)c->parent = x;
            
            z->childSmaller = y;
            y->parent = z;

            z->parent = x->parent;
            if(z->parent){
                z->parent->childBigger = z->parent->childBigger == x ? z : z->parent->childBigger;
                z->parent->childSmaller = z->parent->childSmaller == x ? z : z->parent->childSmaller;
            }
            else head = z;

            x->parent = z;
            z->childBigger = x;

            //marks
            if(z->mark == 1){
                x->mark = 0;
                y->mark = -1;
            }
            else if(z->mark == -1){
                x->mark = 1;
                y->mark = 0;
            }
            else{
                y->mark = 0;
                x->mark = 0;
            }
            z->mark = 0;
        }
        void doubleRotationLeft(binary_node *balancingNode){
            if(!balancingNode){
                throw myException("balancing node == nullptr -- binary_search_tree::doubleRotationLeft");
            }
            //relations
            binary_node *x = balancingNode;
            binary_node *y = balancingNode->childBigger;
            binary_node *z = balancingNode->childBigger->childSmaller;
            binary_node *b = balancingNode->childBigger->childSmaller->childBigger;
            binary_node *c = balancingNode->childBigger->childSmaller->childSmaller;

            y->childSmaller = b;
            if(b)b->parent = y;

            x->childBigger = c;
            if(c)c->parent = x;
            
            z->childBigger = y;
            y->parent = z;

            z->parent = x->parent;
            if(z->parent){
                z->parent->childBigger = z->parent->childBigger == x ? z : z->parent->childBigger;
                z->parent->childSmaller = z->parent->childSmaller == x ? z : z->parent->childSmaller;
            }
            else head = z;

            x->parent = z;
            z->childSmaller = x;

            //marks
            if(z->mark == 1){
                x->mark = -1;
                y->mark = 0;
            }
            else if(z->mark == -1){
                x->mark = 0;
                y->mark = 1;
            }
            else{
                y->mark = 0;
                x->mark = 0;
            }
            z->mark = 0;
        }
        /*
            operation is either insert - 1 or remove - 0
            Fromleft is if the signal is sent from the left or right (from smaller or bigger child)
            makes the overall heigth of the structure lower therefore close to log(n). This drastically increases the speed of other operations
        */
        void balance(binary_node *balancingNode,bool operation, bool FromLeft){
            if(!balancingNode){
                throw myException("balancing node == nullptr -- binary_search_tree::balance");
            }
            if(operation && FromLeft){//-1 insert from the left
                if(balancingNode->mark == -1){//rotation required here
                    if(balancingNode->childSmaller->mark == -1){
                        simpleRotationRight(balancingNode);
                    }
                    else if(balancingNode->childSmaller->mark == 1){
                        doubleRotationRight(balancingNode);
                    }
                }
                else if(balancingNode->mark == 0){
                    balancingNode->mark = -1;
                    if(balancingNode->parent)balance(balancingNode->parent,1, balancingNode->parent->childBigger == balancingNode ? 0 : 1);
                }
                else if(balancingNode->mark == 1){
                    balancingNode->mark = 0;
                    return;
                }
            }
            else if(operation && !FromLeft){//+1 insert from the right
                if(balancingNode->mark == -1){
                    balancingNode->mark = 0;
                    return;
                }
                else if(balancingNode->mark == 0){
                    balancingNode->mark = 1;
                    if(balancingNode->parent)balance(balancingNode->parent,1, balancingNode->parent->childBigger == balancingNode ? 0 : 1);
                }
                else if(balancingNode->mark == 1){
                    if(balancingNode->childBigger->mark == -1){
                        doubleRotationLeft(balancingNode);
                    }
                    else if(balancingNode->childBigger->mark == 1){
                        simpleRotationLeft(balancingNode);
                    }
                }
            }
            else if(!operation && FromLeft){//+1 remove from the left
                if(balancingNode->mark == -1){
                    balancingNode->mark = 0;
                    if(balancingNode->parent)balance(balancingNode->parent,0, balancingNode->parent->childBigger == balancingNode ? 0 : 1);
                }
                else if(balancingNode->mark == 0){
                    balancingNode->mark = 1;
                    return;
                }
                else if(balancingNode->mark == 1){
                    if(balancingNode->childBigger->mark == -1){
                        doubleRotationLeft(balancingNode);
                        if(balancingNode->parent->parent)balance(balancingNode->parent->parent, 0,balancingNode->parent->parent->childBigger == balancingNode->parent ? 0 : 1 );
                    }
                    else if(balancingNode->childBigger->mark == 0){
                        simpleRotationLeft(balancingNode);
                        balancingNode->parent->mark = -1;
                        balancingNode->mark = 1;
                    }
                    else if(balancingNode->childBigger->mark == 1){
                        simpleRotationLeft(balancingNode);
                        if(balancingNode->parent->parent)balance(balancingNode->parent->parent, 0,balancingNode->parent->parent->childBigger == balancingNode->parent ? 0 : 1 );
                    }
                }
            }
            else if(!operation && !FromLeft){//-1 remove from the right
                if(balancingNode->mark == -1){
                    if(balancingNode->childSmaller->mark == -1){
                        simpleRotationRight(balancingNode);
                        if(balancingNode->parent->parent)balance(balancingNode->parent->parent, 0,balancingNode->parent->parent->childBigger == balancingNode->parent ? 0 : 1 );
                    }
                    else if(balancingNode->childSmaller->mark == 0){
                        simpleRotationRight(balancingNode);
                        balancingNode->parent->mark = 1;
                        balancingNode->mark = -1;
                    }
                    else if(balancingNode->childSmaller->mark == 1){
                        doubleRotationRight(balancingNode);
                        if(balancingNode->parent->parent)balance(balancingNode->parent->parent, 0,balancingNode->parent->parent->childBigger == balancingNode->parent ? 0 : 1 );
                    }

                }
                else if(balancingNode->mark == 0){
                    balancingNode->mark = -1;
                    return;
                }
                else if(balancingNode->mark == +1){
                    balancingNode->mark = 0;
                    if(balancingNode->parent)balance(balancingNode->parent,0, balancingNode->parent->childBigger == balancingNode? 0 : 1);
                    
                }

            }
            
        }
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
            int tmp = firstNode->value;
            firstNode->value = secondNode->value;
            secondNode->value = tmp;
        }
    public:
        bool isEmpty(){
            if(!head){
                return true;
            }
            return false;
        }
        ~binary_search_tree(){
            clear();
        }
        /*
        verifies the marks on the nodes
        */
        void markverify(){
            markverify(head);
        }
        /*
        verifies the marks on the nodes starting from a set node

        */
        int markverify(binary_node *investigationNode){
            if(!investigationNode)return 0;
            int a = markverify(investigationNode->childSmaller);
            int b = markverify(investigationNode->childBigger);
            if(b-a != investigationNode->mark){
                throw myException("incorrect mark -- binary_search_tree::markverify");
            }
            else {
                return a>b? a+1 : b+1;
            }
        }
        void verify(binary_node *StartingPoint = nullptr, binary_node *parent = nullptr){
            if(StartingPoint == nullptr){
                StartingPoint = head;
            }
            if(StartingPoint == nullptr){
                return;
                throw myException("error while verifying binary search tree, it's propably empty - binary_search_tree::verify");
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
                if(StartingPoint->childSmaller->value >= StartingPoint->childBigger->value){
                    throw myException("bigger child smaller or equal to smaller child -- binary_search_tree::verify");
                }
            }
            if(StartingPoint->childBigger && !StartingPoint->childSmaller){
                if(StartingPoint->mark != 1){
                    throw myException("wrong mark - Node under investigation doesnt have mark set as 1 (the only option) -- binary_search_tree::verify");
                }
            }
            if(StartingPoint->childSmaller && !StartingPoint->childBigger){
                if(StartingPoint->mark != -1){
                    throw myException("wrong mark - Node under investigation doesnt have mark set as -1 (the only option) -- binary_search_tree::verify");
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
                return nullptr;
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
        int *exportAsAnArray(){
            if(!head){
                return nullptr;
            }
            int *array = new int[count+1];
            array[count] = 0;
            exportAsAnArray(head, array);
            return array;
        }
        void exportAsAnArray(int *passingArray){
            if(!head){
                return;
            }
            exportAsAnArray(head, passingArray);
        }
        void exportAsAnArray(binary_node *startingPoint, int *array){
                if(startingPoint->childSmaller){
                    exportAsAnArray(startingPoint->childSmaller, array);
                }

                array[array[count]] = startingPoint->value;
                array[count]++;

                if(startingPoint->childBigger){
                    exportAsAnArray(startingPoint->childBigger, array);
                }
        }
        linked_list<coordinate> *exportAsLinkedList(){
            if(!head)return nullptr;
            linked_list<coordinate> *list = new linked_list<coordinate>;
            exportAsLinkedList(list);
            return list;
        }
        void exportAsLinkedList(linked_list<coordinate> *list, int shitThisHasToBeCustom = -1){
            if(!head){
                return;
            }
            exportAsLinkedList(head, list, shitThisHasToBeCustom);
        }
        void exportAsLinkedList(binary_node *startingPoint, linked_list<coordinate> *list, int shitThisHasToBeCustom = -1){
                if(startingPoint->childSmaller){
                    exportAsLinkedList(startingPoint->childSmaller, list, shitThisHasToBeCustom);
                }
            
                list->append({shitThisHasToBeCustom, startingPoint->value});

                if(startingPoint->childBigger){
                    exportAsLinkedList(startingPoint->childBigger, list, shitThisHasToBeCustom);
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
                return;
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
                    balance(nodeToBeRemoved->parent,0, nodeToBeRemoved->parent->childBigger == nodeToBeRemoved? 0 : 1);
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
                    balance(nodeToBeRemoved->parent,0, nodeToBeRemoved->parent->childBigger == nodeToBeRemoved? 0 : 1);
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
                    balance(nodeToBeRemoved->parent,0, nodeToBeRemoved->parent->childBigger == nodeToBeRemoved? 0 : 1);
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
                    balance(nodeToBeRemoved->parent,0, nodeToBeRemoved->parent->childBigger == nodeToBeRemoved? 0 : 1);
                    nodeToBeRemoved->parent->childBigger = nodeToBeRemoved->parent->childBigger == nodeToBeRemoved? nodeToBeRemoved->childBigger : nodeToBeRemoved->parent->childBigger;
                    nodeToBeRemoved->parent->childSmaller = nodeToBeRemoved->parent->childSmaller == nodeToBeRemoved? nodeToBeRemoved->childBigger : nodeToBeRemoved->parent->childSmaller;
                }
                if(nodeToBeRemoved->childBigger){
                    nodeToBeRemoved->childBigger->parent = nodeToBeRemoved->parent;
                }
            }
            if(BOTH_CHILD_NULLPTR && nodeToBeRemoved->parent){
                balance(nodeToBeRemoved->parent,0, nodeToBeRemoved->parent->childBigger == nodeToBeRemoved? 0 : 1);
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
                    return nullptr;
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
                    balance(newNode->parent,1, newNode->parent->childBigger == newNode? 0 : 1);
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
                    balance(newNode->parent,1, newNode->parent->childBigger == newNode? 0 : 1);
                    return newNode;
                }
            }

        }

};
int main(){
    int result = 0;
    int n, m;
    std::cin >> n >> m;
    binary_search_tree *pole = new binary_search_tree[n];
    {
        int x, y;
        while(m--){
            std::cin >> x >> y;
            pole[x-1].insert(y-1);
        }
        pole[0].insert(0);
        pole[n-1].insert(n-1);
        pole[0].lowestNode()->visited = true;
    }



    /*
    //debug print 1
    for(int i = 0;i<n;i++){
        pole[i].print();
        std::cout << "\n\n";
    }
    */
    //end debug print 1
    //debug print 2
    bool **hey = new bool*[n];
    for(int i = 0;i<n;i++){
        hey[i] = new bool[n];
        for(int k = 0;k<n;k++){
            hey[i][k] = false;
        }
    }
    {
        int *ptr;
        for(int i = 0;i<n;i++){
            ptr = pole[i].exportAsAnArray();
            if(ptr){
                for(int k = 0;k<pole[i].size();k++){
                    hey[i][ptr[k]] = true;
                }
            }
            delete [] ptr;
        }
    }
    std::cout << "\n   ";
    for(int i = 0;i<n;i++){
        std::cout << i << " ";
    }
    std::cout << "\n";
    for(int i = 0;i<n;i++){
        std::cout << i << ": ";
        for(int k = 0;k<n;k++){
            std::cout << hey[k][i] << " ";
        }
        std::cout << "\n";
    }

    for(int i = 0;i<n;i++){
        delete [] hey[i];
    }
    delete [] hey;
    //end of debug print 2





    //the actual algorithm
    {   
        Node<coordinate> *ptr;
        linked_list<coordinate> *queue = new linked_list<coordinate>;
        queue->append({0, 0});
        int highest_x = 0;
        //basically bfs
        while(true){
            if(queue->isEmpty()){
                if(highest_x == n-1){//došel jsem na konec
                    if(!pole[n-1].highestNode()->visited){
                        result++;
                    }
                    break;
                }
                if(pole[highest_x + 1].isEmpty()){//nemá smysl rozsvícet - nedostali bychom se dále
                    result = -1;
                    break;
                }
                else {//rozsvícení
                    result++;
                    pole[highest_x+1].exportAsLinkedList(queue, highest_x+1);
                    highest_x++;
                }
            }
            ptr = queue->firstNode();
            if(ptr->value.y +1 < n){//going up
                binary_node *binaryNodePtr = pole[ptr->value.x].searchFor(ptr->value.y +1);
                if(binaryNodePtr && !binaryNodePtr->visited){
                    binaryNodePtr->visited = true;
                    queue->append({ptr->value.x, ptr->value.y+1});
                }
            }
            if(ptr->value.y -1 >= 0){//going down
                binary_node *binaryNodePtr = pole[ptr->value.x].searchFor(ptr->value.y - 1);
                if(binaryNodePtr && !binaryNodePtr->visited){
                    binaryNodePtr->visited = true;
                    queue->append({ptr->value.x, ptr->value.y-1});
                }
            }
            if(ptr->value.x +1 < n){//going right
                binary_node *binaryNodePtr = pole[ptr->value.x+1].searchFor(ptr->value.y);
                if(binaryNodePtr && !binaryNodePtr->visited){
                    binaryNodePtr->visited = true;
                    queue->append({ptr->value.x+1, ptr->value.y});
                }
            }
            if(ptr->value.x -1 >= 0){//going left
                binary_node *binaryNodePtr = pole[ptr->value.x-1].searchFor(ptr->value.y);
                if(binaryNodePtr && !binaryNodePtr->visited){
                    binaryNodePtr->visited = true;
                    queue->append({ptr->value.x-1, ptr->value.y});
                }
            }
            if(ptr->value.x == n-1 && ptr->value.y == n-1){
                break;
            }
            if(ptr->value.x > highest_x)highest_x = ptr->value.x;
            queue->remove(ptr);
        }
        delete queue;
    }
    std::cout << result;



    delete [] pole;
}