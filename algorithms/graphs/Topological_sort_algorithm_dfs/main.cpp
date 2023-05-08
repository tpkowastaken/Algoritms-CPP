#include <iostream>

using namespace std;
const int n = 6;
bool dag = true;
int topological_order[n];
int in[n], out[n];
int location, closed_nodes; // location value for determining ins and outs
// n = 6
bool connections[n][n] = {
{0,1,0,1,0,1},
{0,0,1,0,0,0},
{0,0,0,1,1,0},
{0,0,0,0,1,0},
{0,0,0,0,0,1},
{0,0,0,1,0,0}
};

/*
// graph from the video n = 13
bool connections[n][n] = {
{0,0,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,0,0,0,0,0},
{1,0,0,1,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,1,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,0,0,0,1,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,1,1},
{0,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0}
};
*/
void dfs(int num){
    location++;
    cout << "(" << num;
    in[num] = location;
    for(int i = 0;i<n;i++){
        if(connections[num][i] && !in[i]){
            dfs(i);
        }
        else if(connections[num][i] && in[i] && !out[i]){ //detecting if there is a cycle
            dag = false;
            cout << "\ndetekována zpětná hrana: \n" << num << " -> " << i << "\n";
        }
    }
    location++;
    cout << ")" << num;
    out[num] = location;
    //topological algorithm change
    closed_nodes++;
    topological_order[n-closed_nodes] = num;
}
int main(){
    for(int s = 0;s<n;s++){
        if(!out[s])dfs(s);
    }
    cout << "\nnum  in  out\n";
    for(int i = 0;i<n;i++){
        cout << i << "  " << in[i] << "  " << out[i] << "\n";
    }
    if(dag){ 
        cout << "\ntopological order: \n";
        for(int t = 0;t<n-1;t++){
            cout << topological_order[t] << ", ";
        }
        cout << topological_order[n-1];
    }
    else cout << "\nToto není DAG, protože to má zpětnou hranu - viz výše\n";
}
