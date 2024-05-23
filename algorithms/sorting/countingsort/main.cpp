#include <iostream>
#include <fstream>
using namespace std;
int main(){
    int n = 0;
    int *field;
    ifstream theFile("input.txt");
    string line;
    int buckets[2] = {0,0};
    if(theFile){
        int g = 0;
        getline(theFile, line);
        for(int i = 0;line[i] != '\0';i++){
            if(line[i] < 58 && line[i] > 47){
                buckets[g] = buckets[g]*10+(line[i]-48);
            }
            else g++;
        }
        getline(theFile, line);
        for(int i = 0;line[i] != '\0';i++){
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
            if(line[i] < 58 && line[i] > 47){
                field[g] = field[g]*10+(line[i]-48);
            }
            else g++;
        }
        g=0;
    }
    for(int i = 0;i<n;i++){
        cout << field[i] << " ";
    }

    cout << "\n" << n << "\n\n";
    int *bucket = new int[abs(buckets[0] - buckets[1]) + 1];
    int lowerbucket = buckets[0]<buckets[1]?buckets[0]:buckets[1];
    for(int i = 0;i<abs(buckets[0] - buckets[1]) + 1;i++){
        bucket[i] = 0;
    }

    cout << buckets[0] << " " << buckets[1] << "\n";
    for(int i = 0;i<n;i++){
        bucket[field[i]-lowerbucket]++;
    }
    for(int i = 0;i<abs(buckets[0] - buckets[1]) + 1;i++){
        for(int g = 0;g<bucket[i];g++){
            cout << i+lowerbucket << " ";
        }
    }
    delete [] bucket;
    delete [] field;
}