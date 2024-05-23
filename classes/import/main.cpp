#include <iostream>
#include <fstream>
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
                cout << "hey";
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
    delete [] field;

}