#include <iostream>

using namespace std;
const int n = 13;
int connections[n][n-1] = {
{1,5},
{0, 4, 2},
{1, 3},
{2, 4, 7, 12},
{1, 3, 7, 5},
{0, 4, 7, 6 }, 
{5, 8, 11}, 
{5, 4, 3, 8}, 
{6, 7, 9}, 
{11, 12, 10, 8}, 
{9}, 
{6, 9}, 
{3, 9}
};// map of connections (graph)
int path[n][n]; //path from finnish to start
int vals[n]; //labels
int pathnum = 0;
int printpath[n];
void pathback(int num, int x, int p){
    path[x][p] = num;
    p++;
    bool f = true; //boolean signalling if this is the first path in this iteration or if it should create a new path
    for(int b = 0;connections[num][b] != -1; b++){
        if(vals[connections[num][b]] == 0){//ending the recursion
            path[x][p] = connections[num][b];
            printpath[x] = p;
            break;
        }
        else if(vals[connections[num][b]] == vals[num]-1 && f){ //if this is the first path dont create a new path and continue
            pathback(connections[num][b], x, p);
            f = false;
        }
        else if(vals[connections[num][b]] == vals[num]-1){
            pathnum++; //creating a new path
            for(int i = 0; i<p; i++){ //copying the path already found to the new target path[x] (memcpy could be used)
                path[pathnum][i] = path[x][i];
            }
            pathback(connections[num][b], pathnum, p); //continuing on the new path
        }
    }
}

int main()
{
    //defining variables
    int pointer = 1, location = 1; //pointer is a index that signalizes where to write in queue, location means the number of steps from start (current label)
    int q[n]; //queue
    int start, finnish;
    cout << "map: \n";
    for(int i = 0; i<n; i++){//replacing zeros with -1
        q[i] = -1;
        vals[i] = -1;
        for(int g = 0; g<n-1; g++){
            if(connections[i][g] == 0)connections[i][g] = -1;
        }
    }
    //placing zeros that are inside
    connections[1][0] = 0;
    connections[5][0] = 0;
    //printing connections (in console it's called a map)
    for(int i = 0; i<n;i++){
        cout << "{";
        for(int s = 0;s<n-2;s++){
            cout << connections[i][s] << ", ";
        }
        cout << connections[i][n-2] << "}\n";
    }
    cout << "\n \n";
    cout << "input where do u want to start and then when do u want to end (in this format: {start} {finnish}): ";
    cin >> start >> finnish;
    //bfs loop
    q[0] = start;
    vals[start] = 0;
    for(int k = 0; q[k]!=-1 && q[n-1] == -1;k++){//looping through the queue
        location = vals[q[k]] + 1;//setting current label
        for(int s = 0;connections[q[k]][s]!=-1 && q[n-1] == -1;s++){//looping through connections of the num in queue
            if(vals[connections[q[k]][s]] == -1){ //if the label hasn't been set replace it with location
                vals[connections[q[k]][s]] = location;
                q[pointer] = connections[q[k]][s]; //adding the number into queue
                pointer++; //adding to the writing index used for where to write in queue
            }
            /*
            //printing queue as it's running
            cout << "queue: \n";
            cout << "{";
            for(int i = 0; i<n-1;i++){
            cout << q[i] << ", ";
            }
            cout << q[n-1] << "}\n";
            */
        }
    }
    
    //printing labels
    cout << "labels: \n";
    cout << "{";
    for(int i = 0; i<n-1;i++){
        cout << vals[i] << ", ";
    }
    cout << vals[n-1] << "}\n\n";
    

    //finding the route from labels
    pathback(finnish, 0, 0);
    //printing paths
    cout << pathnum + 1 << " shortest paths (" << start << " -> " << finnish << "): \n";
    for(int i = 0; i<=pathnum;i++){
        for(int s = printpath[i];s;s--){
            cout << path[i][s] << " -> ";
        }
        cout << path[i][0] << "\n";
    }
}