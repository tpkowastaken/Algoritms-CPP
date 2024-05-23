#include <iostream>
#include <fstream>
#include "linked_list.h"
int n;
int format(int x, int y, int z){
    return x+n*(y+n*z);
}
int main(){
    int *connections, *d;
    //importing data
    std::ifstream file("input.txt");
    if(file){
        int h, k = 0, space = 0;//h - first index, k - second index, space - third index
        bool action, nFound; //action - if there has been a change - counters random new lines and comments
        std::string line;
        bool negative = false;
        while(getline(file, line)){
            for(int i = 0;line[i]!='\0';i++){
                if(line[i] == 'N'){
                    action = true;
                    break;
                }
                if(line[i]==35)break;//komentare (check pro #)
                if(line[i] == '-')negative = true;
                else if(line[i]==32&&space==1){//kontrolování zda to je mezera a oddeleni pokud ano
                    if(negative)connections[format(k,h,space)] = 0 - connections[format(k,h,space)];
                    negative = false;
                    space = 0;
                    h++;
                }
                else if(line[i]==32){//kontrolovani zda to je mezera
                    negative = false;
                    space = 1;
                }
                else if(!nFound && line[i]<58 && line[i]>47){
                    n = line[i]-48;
                    for(int g = 1;line[g]!='\0' && line[g]<58 && line[g]>47;g++){
                        n = n*10+(line[g]-48);
                    }
                    //creating variables since we know n
                    connections = new int[n*n*2];
                    d = new int[n];
                    for(int i = 0;i<n*n*2;i++){
                        connections[i] = INT32_MAX;
                    }
                    for(int i = 0;i<n;i++){
                        d[i] = INT32_MAX;
                    }
                    //marking it so it doesn't start this again
                    nFound = true;
                    negative = false;
                    break;
                }
                else if(line[i]<58 && line[i]>47){
                    if(connections[format(k,h,space)] == INT32_MAX)connections[format(k,h,space)] = 0; //making sure we don't have a -1 when the command under tries to handle that
                    connections[format(k,h,space)] = connections[format(k,h,space)]*10+(line[i]-48); //transfering from ascii to int (this logic only works with positive integers)
                    action = true;
                }
                
            }
            if(negative)connections[format(k,h,space)] = 0 - connections[format(k,h,space)];
            negative = false;
            if(action)k++;
            action = false;
            space = 0;
            h = 0;
        }
        file.close();
    }
    /*
    //printing the connections list out
    for(int i = 0;i<n;i++){
        for(int g = 0;g<n;g++){
            if(connections[format(i,g,0)] != INT32_MAX)std::cout << connections[format(i,g,0)] << " " << connections[format(i,g,1)] << "\n";
        }
    }
    */
    //bellman ford algorithm:

    d[0] = 0;
    linked_list queue;
    {
        queue.append(0);
        while(!queue.isEmpty()){//first iteration of the relaxing algorithm
            for(int i = 0;connections[format(queue.accessNode(0)->value, i, 0)] != INT32_MAX && i<n;i++){
                if(d[connections[format(queue.accessNode(0)->value, i, 0)]] == INT32_MAX)queue.append(connections[format(queue.accessNode(0)->value, i, 0)]); // adding the node to the queue
                if(d[connections[format(queue.accessNode(0)->value, i, 0)]] > d[queue.accessNode(0)->value] + connections[format(queue.accessNode(0)->value, i, 1)]){//pokud vzdálenost k nodu je větší než vzdálenost k aktualnímu bodu + cesta k nodu
                    d[connections[format(queue.accessNode(0)->value, i, 0)]] = d[queue.accessNode(0)->value] + connections[format(queue.accessNode(0)->value, i, 1)];//přepsání vzdálenosti
                }
            }
            queue.remove(0);
        }
    }

    bool action = true;
    bool *visited = new bool[n];
    for(int i = 0;i<n;i++){
        visited[i] = 0;
    }

    for(int k = 0;k<n-2 && action; k++){//other n-2 iterations
        queue.append(0);
        action = false;
        while(!queue.isEmpty()){
            for(int i = 0;connections[format(queue.accessNode(0)->value, i, 0)] != INT32_MAX && i<n;i++){
                if(!visited[format(queue.accessNode(0)->value, i, 0)])queue.append(connections[format(queue.accessNode(0)->value, i, 0)]); // adding the node to the queue
                if(d[connections[format(queue.accessNode(0)->value, i, 0)]] > d[queue.accessNode(0)->value] + connections[format(queue.accessNode(0)->value, i, 1)]){//pokud vzdálenost k nodu je větší než vzdálenost k aktualnímu bodu + cesta k nodu
                    d[connections[format(queue.accessNode(0)->value, i, 0)]] = d[queue.accessNode(0)->value] + connections[format(queue.accessNode(0)->value, i, 1)];//přepsání vzdálenosti
                    visited[connections[format(queue.accessNode(0)->value, i, 0)]] = true;
                    action = true;
                }
            }
            queue.remove(0);
        }
        for(int i = 0;i<n;i++){
            visited[i] = 0;
        }
    }

    bool negativeLoop = false;
    {//last iteration to check if there arent any negative cycles
        queue.append(0);
        action = false;
        while(!queue.isEmpty()){
            for(int i = 0;connections[format(queue.accessNode(0)->value, i, 0)] != INT32_MAX && i<n;i++){
                if(d[queue.accessNode(0)->value] == INT32_MIN){
                    d[connections[format(queue.accessNode(0)->value, i, 0)]] = INT32_MIN;//přepsání vzdálenosti
                    if(!visited[format(queue.accessNode(0)->value, i, 0)])queue.append(connections[format(queue.accessNode(0)->value, i, 0)]); // adding the node to the queue
                    continue;
                }
                if(!visited[format(queue.accessNode(0)->value, i, 0)])queue.append(connections[format(queue.accessNode(0)->value, i, 0)]); // adding the node to the queue
                if(d[connections[format(queue.accessNode(0)->value, i, 0)]] > d[queue.accessNode(0)->value] + connections[format(queue.accessNode(0)->value, i, 1)]){//pokud vzdálenost k nodu je větší než vzdálenost k aktualnímu bodu + cesta k nodu
                    d[connections[format(queue.accessNode(0)->value, i, 0)]] = INT32_MIN;//přepsání vzdálenosti
                    visited[connections[format(queue.accessNode(0)->value, i, 0)]] = true;
                    action = true;
                    negativeLoop = true;
                }
            }
            queue.remove(0);
        }
    }
    for(int i = 0;i<n;i++){
        std::cout << i << ": " << d[i] << "\n";
    }
    if(negativeLoop){
        std::cout << "there has been found a negative loop\n";
    }
    delete [] d;
    delete [] connections;
}