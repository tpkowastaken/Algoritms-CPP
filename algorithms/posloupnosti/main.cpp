#include <iostream>
using namespace std;
const int n = 13;
int pole[n] = {3, 14, 15, 92, 65, 35, 89 ,79 ,32, 38, 46, 26, 43};
int adresy[n];
int delky[n];

int Nrp(int i){
    if(delky[i] != -1)return delky[i];
    int d = 1;
    for(int j = i+1;j<n;j++){
        if(pole[i]<pole[j]){
            if(Nrp(j)+1 > d){
                d = Nrp(j)+1;
                adresy[i] = j;
            }
        }
    }
    delky[i] = d;
    return d;
}

int main(){
    for(int i = 0;i<n;i++){
        adresy[i] = -1;
        delky[i] = -1;
    }
    cout << Nrp(0) << "\n";
    int i = 0;
    while(adresy[i] != -1){
        
        cout << pole[i] << " ";
        i = adresy[i];
    }
    cout << pole[i];
}