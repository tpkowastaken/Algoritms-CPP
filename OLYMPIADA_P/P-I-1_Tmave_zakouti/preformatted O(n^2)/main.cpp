#include <iostream>
#include <stdio.h>
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
int main(){
    int result = 0;
    int n, m;
    std::cin >> n >> m;
    bool **pole = new bool*[n];
    for(int i = 0;i<n;i++){
        pole[i] = new bool[n];
        for(int k = 0;k<n;k++){
            pole[i][k] = false;
        }
    }
    bool **visited = new bool*[n];
    for(int i = 0;i<n;i++){
        visited[i] = new bool[n];
        for(int k = 0;k<n;k++){
            visited[i][k] = false;
        }
    }
    {
        int x, y;
        while(m--){
            std::cin >> x >> y;
            pole[x-1][y-1] = 1;
        }
        pole[0][0] = 1;
        pole[n-1][n-1] = 1;
        visited[0][0] = true;
    }



    /*
    //debug print 2
    std::cout << "\n   ";
    for(int i = 0;i<n;i++){
        std::cout << i << " ";
    }
    std::cout << "\n";
    for(int i = 0;i<n;i++){
        std::cout << i << ": ";
        for(int k = 0;k<n;k++){
            std::cout << pole[k][i] << " ";
        }
        std::cout << "\n";
    }
    //end of debug print 2
    */




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
                    if(!visited[n-1][n-1]){
                        result++;
                    }
                    break;
                }
                else {//rozsvícení
                    result++;
                    highest_x++;
                    for(int p = 0;p<n;p++){
                        if(pole[highest_x][p]){
                            queue->append({highest_x, p});
                        }
                    }
                    if(queue->isEmpty()){
                        result = -1;
                        break;
                    }
                }
            }
            ptr = queue->firstNode();
            if(ptr->value.y +1 < n){//going up
                if(pole[ptr->value.x][ptr->value.y +1] && !visited[ptr->value.x][ptr->value.y +1]){
                    visited[ptr->value.x][ptr->value.y +1] = true;
                    queue->append({ptr->value.x, ptr->value.y+1});
                }
            }
            if(ptr->value.y -1 >= 0){//going down
                if(pole[ptr->value.x][ptr->value.y-1] && !visited[ptr->value.x][ptr->value.y-1]){
                    visited[ptr->value.x][ptr->value.y -1] = true;
                    queue->append({ptr->value.x, ptr->value.y-1});
                }
            }
            if(ptr->value.x +1 < n){//going right
                if(pole[ptr->value.x+1][ptr->value.y] && !visited[ptr->value.x+1][ptr->value.y]){
                    visited[ptr->value.x+1][ptr->value.y] = true;
                    queue->append({ptr->value.x+1, ptr->value.y});
                }
            }
            if(ptr->value.x -1 >= 0){//going left
                if(pole[ptr->value.x-1][ptr->value.y] && !visited[ptr->value.x-1][ptr->value.y]){
                    visited[ptr->value.x-1][ptr->value.y] = true;
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


    for(int i = 0;i<n;i++){
        delete [] visited[i];
    }
    delete [] visited;

    for(int i = 0;i<n;i++){
        delete [] pole[i];
    }
    delete [] pole;
}