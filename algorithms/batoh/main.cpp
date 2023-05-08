#include <iostream>
#include <fstream>
using namespace std;
int main(){
    int bagSize;
    int *possibleSizes; //field in which there are determined possible sums of elements
    int *items;
    int n = 0;
    ifstream inputFile("input.txt");//input
    if(inputFile){
        string line;
        getline(inputFile, line);
        for(int i = 0;line[i] != '\0';i++){
            if(line[i]<58 && line[i]>47){
                bagSize = bagSize*10+(line[i]-48);
            }
        }
        possibleSizes = new int[bagSize+1];
        possibleSizes[0] = -404;
        int g = 0;
        getline(inputFile, line);
        for(int i = 0;line[i] != '\0';i++){
            if(line[i]<58 && line[i]>47){
                n = n*10+(line[i]-48);
            }
        }
        getline(inputFile, line);
        items = new int[n];
        for(int i = 0; i<n; i++){
            items[i] = 0;
        }
        for(int i = 0;i<bagSize+1;i++){
            possibleSizes[i] = -1;
        }

        for(int i = 0;line[i] != '\0';i++){
            if(line[i] < 58 && line[i] > 47){
                items[g] = items[g]*10+(line[i]-48);
            }
            else g++;
        }
    }
    else(cout << "error while reading the file :( \n");
    for(int i = 0; i<n; i++){
        cout << items[i] << " ";
    }
    cout << " -> " << bagSize << '\n';

    //the bag algorithm
    for(int i = 0;i<n;i++){
        if(items[i]<=bagSize)possibleSizes[items[i]] = i;
    }//assigning the default options (just putting one item in the bag)
    bool dontmakechange = false;
    int t;
    for(int i = 0;i<n && possibleSizes[bagSize] == -1;i++){ // checks if we haven't reached the end of either possiblesizes array or the elements array (basically goes through each element in the list)
        for(int g = 1;g<bagSize+1 && possibleSizes[bagSize] == -1;g++){ //same here except its for the elements in possibleSizes array
            t = g;
            while(possibleSizes[t] != -1 && t > -1){ //checking if the thing isn't already in the path
                if(possibleSizes[t] == i){
                    dontmakechange = true;
                    break;
                }
                t -= items[possibleSizes[t]];
            }
            if(dontmakechange || possibleSizes[g] == -1){
                dontmakechange = false;
                continue;
            }
            if(g+items[i] < bagSize+1 && possibleSizes[g+items[i]] == -1)possibleSizes[g+items[i]] = i; // assigning the values
            for(int i = 1;i<bagSize+1;i++){//printing out the process
                if(possibleSizes[i]!=-1)cout << possibleSizes[i] << " ";
                else cout << "-- ";
            }
            cout << "\n\n";
            dontmakechange = false;
        }
    }
    cout << "\nelements that fit in the bag:\n";
    for(int i = bagSize;i;i--){
        if(possibleSizes[i] == -1)continue;
        while(i-items[possibleSizes[i]]>0){
            cout << items[possibleSizes[i]] << " + ";
            i -= items[possibleSizes[i]];
        }
        cout << items[possibleSizes[i]];
        break;
    }
    delete [] items;
    delete [] possibleSizes;
}