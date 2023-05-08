#include <iostream>
#include <fstream>
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
int main(){
    int *field;
    int n;
    std::ifstream theFile("input.txt");
    std::string line;
    if(theFile){
        getline(theFile, line);
        for(int i = 0;line[i] != '\0';i++){
            if(line[i]<58 && line[i]>47){
                n = n*10+(line[i]-48);
            }
        }
        bool negative = false;
        field = new int[n];
        for(int i = 0;i<n;i++){field[i] = 0;}
        int g = 0;
        getline(theFile, line);
        for(int i = 0;line[i] != '\0';i++){
            if(line[i] == '-'){
                negative = true;
            }
            else if(line[i] < 58 && line[i] > 47){
                field[g] = field[g]*10+(line[i]-48);
            }
            else{
                if(negative)field[g] = 0 - field[g];
                negative = false;
                g++;
            }
        }
        if(negative)field[g] = 0 - field[g];
    }
    else return 1;
    for(int i = 0;i<n;i++){
        std::cout << field[i] << " ";
    }
    quicksort(field, n);
    std::cout << '\n';
    for(int i = 0;i<n;i++){
        std::cout << field[i] << " ";
    }
    delete [] field;
}