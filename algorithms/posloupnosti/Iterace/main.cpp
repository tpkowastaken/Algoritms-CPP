#include <iostream>
#include <fstream>
using namespace std;
//funkcni aktualne yayy
int *adresy, *delky, *dalsi, *pole;
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
        adresy = new int[n];
        delky = new int[n];
        dalsi = new int[n];
        pole = new int[n];
        for(int i = 0;i<n;i++){
            adresy[i] = -1;
            delky[i] = -1;
            pole[i] = 0;
            dalsi[i] = 0;
        }
        int g = 0;
        getline(theFile, line);
        for(int i = 0;line[i] != '\0';i++){
            if(line[i] < 58 && line[i] > 47){
                pole[g] = pole[g]*10+(line[i]-48);
            }
            else g++;
        }
    }
    //iterace:
    for(int i = n;i>-1;i--){
        delky[i] = 1;
        dalsi[i] = 0;
        for(int j = i+1;j<n;j++){
            if(pole[i]<=pole[j] && delky[i] <= delky[j]){
                delky[i] = delky[j] + 1;
                dalsi[i] = j;
            }
        }
    }
    cout << "i  delky  dalsi  hodnota" << '\n';
    cout << "\n\nposloupnost: \n";
    ofstream file("output.txt");
    for(int i = 0; i<n && i>-1;i++){
        if(delky[i]>1){
            for(int k = 0;k<n;k++){
                cout << pole[i] << '\n';
                file << pole[i] << " ";
                if(!dalsi[i])break;
                else i = dalsi[i];
            }
            i = -2;
        }
    }
    file.close();
}