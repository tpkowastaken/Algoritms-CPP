//nefunguje pro negativní čísla (halda jen pro -404 a -1)- potřeba upravit import, extract min, bubbledown
#include <iostream>
#include <fstream>
#include <math.h>
#include "heap.h"
using namespace std;
int *field;
int n;
int main(){
    ifstream theFile("input.txt");
    string line;
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
    cout << n << '\n';
    for(int i = 0;i<n;i++){
        cout << field[i] << " ";
    }
    heap s;
    s.importheap(field, n);
    cout << "\n";
    s.print();
    s.sort();
    s.print();
    for(int i = 0;i<n;i++){
        cout << s.low() << " ";
        s.extractMin();
    }
    delete [] field;
}