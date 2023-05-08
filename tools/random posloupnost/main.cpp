#include <iostream>
#include <fstream>
using namespace std;
int main(){
    int n = 10000, num;
    srand(time(0));
    ofstream theFile("output.txt");
    theFile << n << '\n';
    while(n--){
        num = rand() % 1000;
        theFile << num << " ";
    }
}