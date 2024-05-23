#include <iostream>
#include <fstream>
#include <string>

using namespace std;
ofstream output("output.txt");
int *connections, *in, *out, *low;
int n, location, hey, most1,most2;
void cleanup(){
    delete [] connections;
    delete [] in;
    delete [] out;
    delete [] low;
}

int dfs(int num, int p){
    location++;
    int g;
    cout << "(" << num;
    in[num] = location;
    low[num] = in[num];
    for(int i = 0;connections[(num*n)+i]!=-1;i++){
        if(!in[connections[(num*n)+i]]){
            g = dfs(connections[(num*n)+i], num);
            if(g < low[num]) low[num] = g;
        }
        else if(in[connections[num*n+i]] && in[connections[num*n+i]] < low[num] && connections[num*n+i] != p){
            low[num] = in[connections[num*n+i]];
        }
    }
    for(int i = 0;connections[(num*n)+i]!=-1;i++){
        if(in[num] < low[connections[(num*n)+i]] && low[connections[num*n+i]] && connections[num*n+i] != p && output)output << "nalezen most: " << num << " <-> " << connections[num*n+i] << '\n';
    }
    location++;
    cout << ")" << num;
    out[num] = location;
    return low[num];
}

int main(){
    
    //importing data
    ifstream file("input.txt");
    int h = 0, k = 0;
    bool action, nFound;

    if(file){
        string line;
        while(getline(file, line)){
            for(int i = 0;line[i]!='\0';i++){
                if(line[i]==35)break;//komentare
                else if(line[i]==32){//kontrolovani zda to je mezera
                    h++;
                }
                else if(!nFound && line[i]<58 && line[i]>47){
                    n = line[i]-48;
                    for(int g = 1;line[g]!='\0' && line[g]<58 && line[g]>47;g++){
                        n = n*10+(line[g]-48);
                    }
                    //creating connections
                    connections = new int[n*n];
                    in = new int[n];
                    out = new int[n];
                    low = new int[n];
                    for(int i = 0;i<n*n;i++){
                        connections[i] = -1;
                    }
                    for(int i = 0;i<n;i++){
                        in[i] = 0;
                        out[i] = 0;
                        low[i] = -1;
                    }
                    //marking it so it doesn't start this again
                    nFound = true;
                    break;
                }
                else if(line[i]<58 && line[i]>47){
                    if(connections[(n*k)+h] == -1 )connections[(n*k)+h] = 0; //making sure we don't have a -1 when the command under tries to handle that
                    connections[(n*k)+h] = connections[(n*k)+h]*10+(line[i]-48); //transfering from ascii to int (this logic only works with positive integers)
                    action = true;
                }
                
            }
            if(action)k++;
            action = false;
            h=0;
        }
    }
    file.close();
    int p = 0;
    if(output)output << "vypisování všech mostů: \n";
    for(int i = 0;i<n*n;i++){
        if(connections[i] != -1)cout << connections[i] << " ";
        if(p<(i+1)/n){
            cout << "\n";
            p++;
        }
    }
    dfs(0, -1);
    cout << "\nnum  in  out\n";
    output.close();
    for(int i = 0;i<n;i++){
        cout << i << "  " << in[i] << "  " << out[i] << "  " << low[i] << "\n";
    }
    for(int i = 0;i<n-1;i++){
        if(low[i]!=low[i+1]){
        }
    }
    cleanup();
}