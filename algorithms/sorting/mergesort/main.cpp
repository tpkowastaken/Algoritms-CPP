#include <iostream>
#include <fstream>
using namespace std;
void mergesort(int *inputfield, int n){// n stands for the size at which we want to input
    if(n>2){
        mergesort(inputfield, n/2);
        mergesort(inputfield + n/2, n-(n/2));
        int index1 = 0;
        int index2 = n/2;
        int permindex2 = index2;
        int *newfield = new int[n];
        int i = 0;
        while(index1 < permindex2 && index2 < n){//sorting it until one gets to the end
            if(inputfield[index1] < inputfield[index2]){
                newfield[i] = inputfield[index1];
                index1++;
            }
            else{
                newfield[i] = inputfield[index2];
                index2++;
            }
            i++;
        }
        if(index1 == permindex2){//handling the first one getting to the end
            while(index2<n){
                newfield[i] = inputfield[index2];
                index2++;
                i++;
            }
        }
        else{//handling the second one getting to the end
            while(index1<permindex2){
                newfield[i] = inputfield[index1];
                index1++;
                i++;
            }
        }
        memcpy(inputfield, newfield, n*sizeof(int));
        delete [] newfield;
    }
    else if(n == 2 && inputfield[0] > inputfield[1]){
        int tmp = inputfield[0];//swap
        inputfield[0] = inputfield[1];
        inputfield[1] = tmp;
        return;
    }
}
int main(){
    int *field;
    int n;
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
    cout << "\n\n";
    mergesort(field, n);
    for(int i = 0;i<n;i++){
        cout << field[i] << " ";
    }
    delete [] field;
}