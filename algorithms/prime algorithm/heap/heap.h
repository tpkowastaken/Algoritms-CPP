#ifndef HEAP_H
#define HEAP_H
#include "myException.h"
#include "math.h"
struct graph_node 
{
    int index;
    int length;
};
class heap{
    private:
        graph_node *x;//the array that the heap will be stored in
        int n;//current length of the array
        int currentIndex = -1;
        int lastLineSize;//size of the last line (the not entirely filled one)
        bool shrinkArray = true;
        const int EMPTY = INT_MAX;//integer limit
        //quick math functions
        int parentOf(int i){
            return (i+1)/2-1;
        }
        int leftChildOf(int i){
            return (i+1)*2-1;
        }
        int rightChildOf(int i){
            return (i+1)*2;
        }
        int swap(int target, int source){
            int tmp = x[target].length;
            x[target].length = x[source].length;
            x[source].length = tmp;
            return target;
        }
        void bubbleUp(int i){
            while(parentOf(i) != -1 && x[parentOf(i)].length > x[i].length){
                i = swap(parentOf(i), i);
            }
        }
        void bubbleDown(int i){
            while(rightChildOf(i) < n && (x[leftChildOf(i)].length < x[i].length || x[rightChildOf(i)].length < x[i].length)){
                i = swap(x[leftChildOf(i)].length < x[rightChildOf(i)].length ? leftChildOf(i) : rightChildOf(i), i);
            }
        }

    public:
        ~heap(){
            delete [] x;
        }
        /*
        heap structure with dynamic array which will dynamically decrease its size as well
        */
        heap() : heap(1, true){}
        /*
        heap structure with dynamic array which may dynamically decrease its size as well
        shrink array means if it should dynamically decrease its size
        */
        heap(bool shrinkArray) : heap(1, shrinkArray){}
        /*
        creates a heap structure with the starting size as 2^n-1. which doesn't decrease it's size
        n could also be imagined as the rows of the heap with n being the number of rows
        */
        heap(int n) : heap(n, false){}
        /*
        creates a heap structure with the starting size as 2^n-1. which doesn't decrease it's size
        n could also be imagined as the rows of the heap with n being the number of rows
        shrink array means if it should dynamically decrease its size
        if shrink array == true n will automatically be set to 1
        */
        heap(int n, bool shrinkArray){
            if(!n || n < 0){
                throw myException("size with which was heap tried to be built is 0 or lower therefore invalid -- heap::heap");
            }
            if(shrinkArray){//if the user is dumb enough to not understand it doesn't even try to build the heap with the n size
                n = 1;
            }
            this->shrinkArray = shrinkArray;
            this->n = pow(2, n)-1;
            lastLineSize = (this->n+1)/2;
            x = new graph_node[this->n];
            for(int i = 0;i<this->n;i++){
                x[i].length = EMPTY;
            }
        }
        /*
        creates a new heap structure and imports it's values from an array.
        n is the size of the array, pointerToAnArray is the array, and sorted means if it has been sorted either from INT_MIN to INT_MAX or being from a different heap
        */

        heap(int n, int *pointerToAnArray, bool sorted) : heap(pointerToAnArray, n, false, sorted){}
        /*
        creates a new heap structure and imports it's values from an array.
        n is the size of the array, pointerToAnArray is the array, and sorted means if it has been sorted either from INT_MIN to INT_MAX or being from a different heap
        shrink array means if it should dynamically decrease its size
        */
        heap(int *pointerToAnArray, int n, bool shrinkArray = false, bool sorted = false){
            if(!n || n < 0){
                throw myException("size with which was heap tried to be built is 0 or lower therefore invalid -- heap::heap");
            }
            if(!pointerToAnArray){
                throw myException("passed pointer to an array == nullptr -- heap::heap");
            }
            int i = 1;
            {
                int k = 2;
                while(i <= n){
                    i += k;
                    k *= 2;
                }
            }
            this->shrinkArray = shrinkArray;
            this->n = i;
            lastLineSize = (this->n+1)/2;
            x = new graph_node[this->n];
            memcpy(x, pointerToAnArray, n*sizeof(int));
            for(int i = n;i<this->n;i++){
                x[i].length = EMPTY;
            }
            currentIndex = n-1;
            if(!sorted){
                sort();
            }
        }
        /*
        sorts the heap
        */
        void sort(){
            if(currentIndex == -1){
                throw myException("nothing to be sorted - the heap is empty -- heap::sort");
            }
            for(int i = currentIndex; i>=0; i--){
                for(int g = i;
                g > 0 && x[parentOf(g)].length > x[g].length //as long as we are in range and parent is smaller
                && (leftChildOf(parentOf(g)) == g //and as long as we are either leftchild or smaller than leftchild
                || x[leftChildOf(parentOf(g))].length > x[g].length);g = parentOf(g)){//modified bubbleup
                    swap(parentOf(g), g);
                    bubbleDown(g);
                }
            }
        }
        /*
        assigns the shrinkArray option a new value and shrinks the array if possible
        */
        void changeshrinkArray(bool arrayShrinking){
            if(!arrayShrinking){
                this->shrinkArray = false;
            }
            else if(!shrinkArray){
                this->shrinkArray = true;
                currentIndex++;
                if(n-currentIndex > lastLineSize && shrinkArray){//shrinking the array
                    n -= lastLineSize;
                    lastLineSize /= 2;
                    graph_node *newArray = new graph_node[n];
                    memcpy(newArray, x, (currentIndex+1)*sizeof(int));
                    delete [] x;
                    x = newArray;
                    x[n-1].length = EMPTY;
                }
                currentIndex--;
            }
        }
        /*
        extracts the insides of the heap in an array - could be used to create a new heap structure without sorting it
        returns pointer to an array with size of this heap
        you can get the size calling this->size
        */
        int *extractAsHeapArray(){
            if(currentIndex == -1){
                throw myException("nothing to be extracted - the heap is empty -- heap::extractAsUnsortedArray");
            }
            int *newArray = new int[size()];
            memcpy(newArray, x, size()*sizeof(int));
            return newArray;
        }
        /*
        extracts the values inside the heap in an sorted array from INT_MIN to INT_MAX
        returns pointer to an array with size of this heap
        you can get the size calling this->size()
        */
        int *extractAsSortedArray(){
            if(currentIndex == -1){
                throw myException("nothing to be extracted - the heap is empty -- heap::extractAsSortedArray");
            }
            int *newArray = new int[size()];
            heap heapsort(x, size(), false, true);
            for(int i = 0;i<size(); i++){
                newArray[i] = heapsort.extractMin();
            }
            return newArray;
        }
        /*
        returns size of the heap
        */
        int size(){
            return currentIndex+1;
        }
        /*
        getter for values inside this heap
        */
        int getvalue(int i){
            if(i>currentIndex || i<0){
                throw myException("index is out of range -- heap::getValue");
            }
            return x[i];
        }
        /*
        setter for values inside this heap
        */
        void changevalue(int i, int value){
            if(i>currentIndex || i<0){
                throw myException("index is out of range -- heap::changevalue");
            }
            if(x[i] > value){
                x[i] = value;
                bubbleUp(i);
            }
            if(x[i] < value){
                x[i] = value;
                bubbleDown(i);
            }
        }
        /*
        returns the lowest value
        */
        int min(){
            return x[0];
        }
        /*
        removes the lowest value from the heap
        */
        int extractMin(){
            int value = min();
            if(currentIndex == -1){
                throw myException("there is nothing to remove - the heap is empty! -- heap::extractMin()");
            }
            swap(currentIndex, 0);
            x[currentIndex] = EMPTY;
            if(n-currentIndex > lastLineSize && shrinkArray){//shrinking the array
                n -= lastLineSize;
                lastLineSize /= 2;
                int *newArray = new int[n];
                memcpy(newArray, x, (currentIndex+1)*sizeof(int));
                delete [] x;
                x = newArray;
                x[n-1] = EMPTY;
            }
            currentIndex--;
            bubbleDown(0);
            return value;
        }
        /*
        adds a new value to the heap
        */
        void insert(int value){
            currentIndex++;
            x[currentIndex] = value;
            bubbleUp(currentIndex);

            if(currentIndex == n-1){//expanding the array
                lastLineSize *= 2;
                n += lastLineSize;
                int *newArray = new int[n];
                memcpy(newArray, x, (currentIndex+1)*sizeof(int));
                delete [] x;
                x = newArray;
                for(int i = currentIndex+1; i<n; i++){
                    x[i] = EMPTY;
                }
            }
        }
        /*
        prints the heap in array like style
        */
        void print(){
            std::cout << "[";
            int k = 1;
            int s = 1;
            for(int i = 0;i<n;i++){
                if(i == k){
                    k += pow(2, s);
                    s++;
                    std::cout << "]\n[";
                }
                if(x[i] == EMPTY){
                    std::cout << 0 << ", ";
                }
                else {
                    std::cout << x[i] << ", ";
                }
            }
            std::cout << "]\n";
        }

};



#endif //HEAP_H