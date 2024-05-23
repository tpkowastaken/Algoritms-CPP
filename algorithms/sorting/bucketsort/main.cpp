#include <iostream>
#include <fstream>
#include "linked_list.h"
#include <math.h>
using namespace std;
int low(int a, int b){
    return a<b?a:b;
}

int main(){
    int n = 0;
    int *field;
    ifstream theFile("input.txt");
    string line;
    string *content;
    int buckets[2] = {0,0};

    //importing the file
    if(theFile){
        int g = 0;
        bool negative = false;
        getline(theFile, line);
        for(int i = 0;line[i] != '\0';i++){
            if(line[i] == '#')break;
            if(line[i] == '-'){
                negative = true;
            }
            else if(line[i] < 58 && line[i] > 47){
                buckets[g] = buckets[g]*10+(line[i]-48);
            }
            else{
                if(negative)buckets[g] = 0 - buckets[g];
                negative = false;
                g++;
            }
        }
        if(negative)buckets[g] = 0 - buckets[g];
        negative = false;
        getline(theFile, line);
        for(int i = 0;line[i] != '\0';i++){
            if(line[i] == '#')break;
            if(line[i]<58 && line[i]>47){
                n = n*10+(line[i]-48);
            }
        }
        field = new int[n];
        for(int i = 0;i<n;i++){
            field[i] = 0;
        }
        g = 0;
        getline(theFile, line);
        for(int i = 0;line[i] != '\0';i++){
            if(line[i] == '#')break;
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
        g=0;
        content = new string[n];
        while(theFile >> content[g++]);
    }


    for(int i = 0;i<n;i++){
        cout << field[i] << " ";
    }

    for(int i = 0;i<n;i++){
        cout << content[i] << " ";
    }
    cout << "\n";
    cout << buckets[0] << " " << buckets[1] << "\n";
    int lowerbucket = low(buckets[0],buckets[1]);
    cout << "lowerbucket: " << lowerbucket << '\n';
    linked_list *bucket = new linked_list[abs(buckets[1]-buckets[0]) + 1];
    for(int i = 0;i<n;i++){
        bucket[field[i]-lowerbucket].append(content[i]);
    }
    for(int i = 0;i<abs(buckets[1]-buckets[0]+1);i++){
        bucket[i].print();
    }
    delete [] bucket;
    delete [] field;
    delete [] content;
}