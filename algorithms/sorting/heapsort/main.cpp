//nefunguje pro negativní čísla (přesně pro -1 a -404) - potřeba upravit import a extract min
#include <iostream>
#include <fstream>
using namespace std;
int *field;
int n;
class heap{
    private:
        int *x;
        int l = 0;//number of values in heap
    public:
        heap(){
            x = new int[n+1]; // stores active distances from start
            for(int i = 0;i<n+1;i++){
                x[i] = -1;
            }
            x[0] = -404;//an empty value
        }
        ~heap(){
            delete [] x;
        }
        void add(int value){
            int i = l+1;
            while(i/2){
                if(x[i/2]>value){
                    x[i] = x[i/2]; //moving
                    i = i/2;
                }
                else{
                    x[i] = value; //writing
                    l++;
                    return;
                }
            }
            x[i] = value; //writing
            l++;
        }
        int low(){return x[1];}
        void extractMin(){//vars vals and nodes not done yet
            int i = 1;
            while((x[i*2] !=-1 || x[i*2+1] != -1) && i*2+1 < n+1){//dokud existuje aspon jedna hodnota pod a nesnazi se to pristoupit k hodnote mimo field
                if(x[i*2] != -1 && x[i*2+1] == -1){//if the second is non-existant move it up
                    x[i] = x[i*2]; //moving
                    i = i*2;
                }
                else if(x[i*2] == -1 && x[i*2+1] != -1){//if the first is non-existant move it up
                    x[i] = x[i*2+1]; //moving
                    i = i*2+1;
                }
                else if(x[i*2] <= x[i*2+1]){//if the first is smaller move that up
                    x[i] = x[i*2]; //moving
                    i = i*2;
                }
                else if(x[i*2+1] < x[i*2]){//if the second is smaller move that up
                    x[i] = x[i*2+1]; //moving
                    i = i*2+1;
                }
            }
            if(i*2+1 >= n+1 && i*2 < n+1 && x[i*2] != -1){//pokud failnulo while u posledni podminky, ale existuje hodnota na poslednim indexu
                x[i] = x[i*2]; //moving
                i = i*2;
            }
            x[i] = -1;//writing
            l--;
        }
        void print(){
            cout << "printing array x:\n{";
            for(int i = 1;i<l;i++){
                cout << x[i] << ", ";
            }
            cout << x[l] << "}\n";
        }
};
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
        field = new int[n];
        for(int i = 0;i<n;i++){
            field[i] = 0;
        }
        int g = 0;
        getline(theFile, line);
        for(int i = 0;line[i] != '\0';i++){
            if(line[i] < 58 && line[i] > 47){
                field[g] = field[g]*10+(line[i]-48);
            }
            else g++;
        }
    }
    for(int i = 0;i<n;i++){
        cout << field[i] << " ";
    }
    cout << "\n";
    heap s;
    for(int i = 0;i<n;i++){
        s.add(field[i]);
    }
    for(int i = 0;i<n;i++){
        cout << s.low() << " ";
        s.extractMin();
    }
    delete [] field;
}