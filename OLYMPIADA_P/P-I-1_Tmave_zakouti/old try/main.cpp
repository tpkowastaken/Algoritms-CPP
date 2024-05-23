#include <iostream>
void swap(int *element1, int *element2){
    int tmp = *element1;
    *element1 = *element2;
    *element2 = tmp;
}
void quicksort(int *inputfield, int n){
    if(n>2){
        //getting the pivot: (this can be replaced with getting the median, choosing the last one or choosing a random pivot)
        int pivot;
        {
            double pivotaverage = (inputfield[0] + inputfield[n/2] + inputfield[n-1])/3; // average of those pivots
            double a,b,c;
            a = abs(inputfield[0] - pivotaverage);
            b = abs(inputfield[n/2] - pivotaverage);
            c = abs(inputfield[n-1] - pivotaverage);
            if(a<=b && a<=c)pivot = 0; // getting the closest to average
            else if(b<=a && b<=c)pivot = n/2; //getting the closest to average
            else pivot = n-1; // getting the closest to average
        }
        //doing the partitioning
        int i = -1;
        for(int j = 0;j<n;j++){
            if(j == pivot)continue;
            else if(inputfield[j] > inputfield[pivot])continue;
            else if(inputfield[j] <= inputfield[pivot]){
                i++;
                if(i == pivot)i++;
                swap(inputfield + i, inputfield + j);
            }
        }
        if(pivot <= i){//calling the recursion and swapping the pivots in the process
            swap(inputfield + i, inputfield + pivot);
            quicksort(inputfield, i);
            quicksort(inputfield + i + 1, n-(i+1));//give a pointer to element after the one that is scanned = (i+1); then the length is n-that thing. The pointer has already been skipped in the partitioning.
        }
        else if(pivot > i){//calling the recursion and swapping the pivots in the process
            swap(inputfield + i + 1,inputfield + pivot);
            quicksort(inputfield, i+1);
            quicksort(inputfield + i + 2, n-(i+2));//give a pointer to element after the one that is scanned = (i+1) and skip the pointer = +1; then the length is n-that thing
        }
    }
    else if(n == 2 && inputfield[0] > inputfield[1]){ // this is just to faster things up when it gets to the end
        swap(inputfield,inputfield + 1);
    }
    //if n == 1 or n == 0 there are no changes needed
}
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
    private:
        Node<T> *next = nullptr;
        Node<T> *previous = nullptr;
        ~Node(){}
        Node(T value){
            this->value = value;
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
        returns a pointer to a newly created array with the size of linked_list::size
        make sure that there is at least 1 element in the linked_list - otherwise it will throw myException(an exception
        */
        T *exportAsAnArray(){
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
        void sort(){
            T *ptr = this->exportAsAnArray();
            quicksort(ptr, l);
            int k = l;
            clear();
            Node<T> *pointer = append(ptr[0]);
            for(int i = 0;i<k;i++){
                if(pointer->value != ptr[i]){
                    pointer = append(ptr[i]);
                }
            }
            delete [] ptr;
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
        Node<T> *insertAfter(Node<T> *previousNode, T value){
            Node<T> *newNode;
            newNode = new Node<T>(value);
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
            Node<T> *newNode;
            newNode = new Node<T>(value);
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
        creates a new element at the end of the list
        */
        Node<T> *append(T value){
            Node<T> *newitem;
            newitem = new Node(value);
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
            newItem = new Node(value);
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
        void print(){
            Node<T> *pointer = head;
            while(pointer){
                std::cout << pointer->value << " ";
                pointer = pointer->next;
            }
            std::cout << "\n";
        }
};
/*
    reach available positions
*/
void rap(linked_list<int> *accessedPositions, linked_list<int> *table){
        Node<int> *a = table->firstNode(), *b = accessedPositions->firstNode();
        Node<int> *pointerToReturnToA, *pointerToReturnToB;
        bool goingBack = false;
        while(a && b){
            if(a->value < b->value-1){
                if(goingBack){
                    goingBack = false;
                    a = pointerToReturnToA;
                    b = pointerToReturnToB;
                }
                a = a->nextNode();
            }
            else if(a->value == b->value-1){
                if(!goingBack){
                    pointerToReturnToA = a->nextNode();
                    pointerToReturnToB = b;
                    goingBack = true;
                }
                accessedPositions->insertBefore(b, a->value);
                a = a->previousNode();
                b = b->previousNode();
            }
            else if(a->value == b->value){
                a = a->nextNode();
            }
            else if(a->value == b->value + 1){
                accessedPositions->insertAfter(b, a->value);
                b = b->nextNode();
                a = a->nextNode();
            }
            else if(a->value > b->value + 1){
                b = b->nextNode();
            }
        }
}
/*
    list elements included in both
*/
linked_list<int> *leiib(linked_list<int> *firstList, linked_list<int> *secondList, bool deleteOld = true){
    linked_list<int> *c = new linked_list<int>;
    Node<int> *a = firstList->firstNode(), *b = secondList->firstNode();
    while(a && b){

        if(a->value < b->value){
            a = a->nextNode();
        }
        else if(a->value == b->value){
            c->append(a->value);
            a = a->nextNode();
            b = b->nextNode();
        }
        else {
            b = b->nextNode();
        }
    }
    if(deleteOld)delete firstList;
    return c;
}
/*
    delete elements included in both
*/
void deiib(linked_list<int> *firstList, linked_list<int> *secondList){
    Node<int> *a = firstList->firstNode(), *b = secondList->firstNode();
    while(a && b){

        if(a->value < b->value){
            a = a->nextNode();
        }
        else if(a->value == b->value){
            Node<int> *tmp = a;
            a = a->nextNode();
            firstList->remove(tmp);
            b = b->nextNode();
        }
        else {
            b = b->nextNode();
        }
    }
}

int main(){
    int result = 0;
    int n, m;
    std::cin >> n >> m;
    linked_list<int> *table = new linked_list<int>[n];
    bool anythingNeedsToBeSorted = false;
    bool *needsToBeSorted = new bool[n];
    for(int i = 0;i<n;i++){
        needsToBeSorted[i] = false;
    }
    linked_list<int> *accessedPositions = new linked_list<int>;
    {
        int x,y;
        Node<int> *ptr;
        for(int i = 0;i<m;i++){
            std::cin >> x >> y;
            ptr = table[x-1].append(y-1);
            if(ptr->previousNode() && ptr->previousNode()->value >= ptr->value){
                needsToBeSorted[x-1] = true;
                anythingNeedsToBeSorted = true;
            }
        }
        if(table[n-1].isEmpty() || table[n-1].lastNode()->value != n-1){
            table[n-1].append(n-1);
        }
        if(table[0].isEmpty() || table[0].firstNode()->value != 0){
            table[0].appendToStart(0);
        }
        accessedPositions->append(0);
    }
    if(anythingNeedsToBeSorted){
        for(int i = 0;i<n;i++){
            if(needsToBeSorted[i]){
                table[i].sort();
            }
        }
    }
    //debug print
    bool **hey = new bool*[n];
    for(int i = 0;i<n;i++){
        hey[i] = new bool[n];
        for(int k = 0;k<n;k++){
            hey[i][k] = false;
        }
    }
    for(int i = 0;i<n;i++){
        if(!table[i].isEmpty()){
            Node<int> *ptr = table[i].firstNode();
            while(ptr){
                hey[i][ptr->value] = true;
                ptr = ptr->nextNode();
            }
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
    //end of debug print
    std::cout << "\n\n";
    for(int i = 0;i<n-1;i++){//pro každý sloupec
        if(table[i+1].isEmpty()){
            result = -1;
            break;
        }
        linked_list<int> *oldAccessedPositions = new linked_list<int>;
        Node<int> *a = accessedPositions->firstNode();
        while(a){
            oldAccessedPositions->append(a->value);
            a = a->nextNode();
        }
        rap(accessedPositions, &table[i]);//1 -> 1 1 1 1 1
        if(i){
            linked_list<int> *comparator = leiib(accessedPositions, &table[i-1], false);//1 1 1 1 1 -> 1 1
            linked_list<int> *backup;
            if(comparator->size() > oldAccessedPositions->size()){//1 1 > 1
                deiib(comparator, oldAccessedPositions);//1 1 -> 1
                for(int k = i;k && !table[k-1].isEmpty() && !comparator->isEmpty();k--){
                    rap(comparator, &table[k]);//1 -> 1 1 | 1 -> 1 | 1 -> 1 1 1
                    backup = leiib(comparator, &table[k-1], false);//1 1 -> 1 | 1 -> 1 | 1 1 1 -> {}
                    if(backup->isEmpty()){
                        delete backup;
                    }
                    else{
                        delete comparator;
                        comparator = backup;
                    }
                }
            }
            delete comparator;
        }
        delete oldAccessedPositions;
        accessedPositions = leiib(accessedPositions, &table[i+1]);
        if(accessedPositions->isEmpty()){
            result++;
            Node<int> *ptr = table[i+1].firstNode();
            while(ptr){
                accessedPositions->append(ptr->value);
                ptr = ptr->nextNode();
            }
        }
    }
    //posledni sloupec
    if(result != -1){
        rap(accessedPositions, &table[n-1]);
        if(accessedPositions->lastNode()->value != n-1){
            result++;
        }
    }

    std::cout << result;
    delete accessedPositions;
    delete [] table;
}