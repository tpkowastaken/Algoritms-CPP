#include <iostream>
#include <fstream>
#include <string>
#include "linked_list.h"
void radixsort(std::string *words, int n){
    const int ASCIISIZE = 256;
    linked_list<std::string> *buckets = new linked_list<std::string>[ASCIISIZE];
    for(int i = 0;i<n;i++){//bucketsort
        int letter = words[i][0];
        buckets[letter].append(words[i]); //putting words to a bucket sorted by the first letter
    }
    for(int i = 0;i<ASCIISIZE;i++){
        if(buckets[i].isEmpty() || buckets[i].size() <= 1)continue;
        int bucketsSize = buckets[i].size();
        //converting from linked_list to an array
        std::string *newWords = buckets[i].exportAsAnArray();//O!(n)
        char currentLetter = i;
        for(int j = 0;j<bucketsSize;j++){
            newWords[j].erase(0,1);
        }
        radixsort(newWords, bucketsSize);//passing it further and sorting the words without the first letter
        buckets[i].clear();//removing elements from buckets
        for(int s = 0;s<bucketsSize;s++){//getting the new 
            buckets[i].append(currentLetter + newWords[s]);
        }
        delete [] newWords;
    }
    int k = 0;
    for(int i = 0;i<ASCIISIZE;i++){
        if(buckets[i].isEmpty()){
            continue;
        }
        Node<std::string> *nodePointer = buckets[i].accessNode(0);
        while(nodePointer != NULL){
            words[k] = nodePointer->value;
            nodePointer = nodePointer->nextNode();
            k++;
        }
    }
    delete [] buckets;
}
int main(){
    std::ifstream file("input.txt");
    int n;
    file >> n;
    std::string *words = new std::string[n];
    int i = 0;
    while(file >> words[i]){
        i++;
    }
    for(int i = 0;i<n;i++){
        std::cout << words[i] << " ";
    }
    std::cout << "\n";
    radixsort(words,n);
    std::cout << "\n";
    for(int i = 0;i<n;i++){
        std::cout << words[i] << " ";
    }
    delete [] words;    
}