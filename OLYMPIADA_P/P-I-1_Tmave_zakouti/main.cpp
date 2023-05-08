#include <iostream>
#include "linked_list.h"
struct coordinate
{
    int x,y;
};
int main(){
    int result = 0;
    int n, m;
    std::cin >> n >> m;
    bool **pole = new bool*[n];
    for(int i = 0;i<n;i++){
        pole[i] = new bool[n];
        for(int k = 0;k<n;k++){
            pole[i][k] = false;
        }
    }
    bool **visited = new bool*[n];
    for(int i = 0;i<n;i++){
        visited[i] = new bool[n];
        for(int k = 0;k<n;k++){
            visited[i][k] = false;
        }
    }
    {
        int x, y;
        while(m--){
            std::cin >> x >> y;
            pole[x-1][y-1] = 1;
        }
        pole[0][0] = 1;
        pole[n-1][n-1] = 1;
        visited[0][0] = true;
    }



    /*
    //debug print 2
    std::cout << "\n   ";
    for(int i = 0;i<n;i++){
        std::cout << i << " ";
    }
    std::cout << "\n";
    for(int i = 0;i<n;i++){
        std::cout << i << ": ";
        for(int k = 0;k<n;k++){
            std::cout << pole[k][i] << " ";
        }
        std::cout << "\n";
    }
    //end of debug print 2
    */




    //the actual algorithm
    {   
        Node<coordinate> *ptr;
        linked_list<coordinate> *queue = new linked_list<coordinate>;
        queue->append({0, 0});
        int highest_x = 0;
        //basically bfs
        while(true){
            if(queue->isEmpty()){
                if(highest_x == n-1){//došel jsem na konec
                    if(!visited[n-1][n-1]){
                        result++;
                    }
                    break;
                }
                else {//rozsvícení
                    result++;
                    highest_x++;
                    for(int p = 0;p<n;p++){
                        if(pole[highest_x][p]){
                            queue->append({highest_x, p});
                        }
                    }
                    if(queue->isEmpty()){
                        result = -1;
                        break;
                    }
                }
            }
            ptr = queue->firstNode();
            if(ptr->value.y +1 < n){//going up
                if(pole[ptr->value.x][ptr->value.y +1] && !visited[ptr->value.x][ptr->value.y +1]){
                    visited[ptr->value.x][ptr->value.y +1] = true;
                    queue->append({ptr->value.x, ptr->value.y+1});
                }
            }
            if(ptr->value.y -1 >= 0){//going down
                if(pole[ptr->value.x][ptr->value.y-1] && !visited[ptr->value.x][ptr->value.y-1]){
                    visited[ptr->value.x][ptr->value.y -1] = true;
                    queue->append({ptr->value.x, ptr->value.y-1});
                }
            }
            if(ptr->value.x +1 < n){//going right
                if(pole[ptr->value.x+1][ptr->value.y] && !visited[ptr->value.x+1][ptr->value.y]){
                    visited[ptr->value.x+1][ptr->value.y] = true;
                    queue->append({ptr->value.x+1, ptr->value.y});
                }
            }
            if(ptr->value.x -1 >= 0){//going left
                if(pole[ptr->value.x-1][ptr->value.y] && !visited[ptr->value.x-1][ptr->value.y]){
                    visited[ptr->value.x-1][ptr->value.y] = true;
                    queue->append({ptr->value.x-1, ptr->value.y});
                }
            }
            if(ptr->value.x == n-1 && ptr->value.y == n-1){
                break;
            }
            if(ptr->value.x > highest_x)highest_x = ptr->value.x;
            queue->remove(ptr);
        }
        delete queue;
    }
    std::cout << result;


    for(int i = 0;i<n;i++){
        delete [] visited[i];
    }
    delete [] visited;

    for(int i = 0;i<n;i++){
        delete [] pole[i];
    }
    delete [] pole;
}