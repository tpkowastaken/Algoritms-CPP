#include <iostream>
using namespace std;
bool *field, *fieldDefined;
int n;
int defX,defY; //default values (typed in by the user) + 1 - for counting the index from field to use
int format(int x, int y, int z){
    return x+defX*(y+defY*z);
}
bool winning(int x, int y, int z){
    if(x<0 || y<0 || z<0)return true;
    if(fieldDefined[format(x,y,z)]){
        return field[format(x,y,z)]; // checking if we have found this configuration's status already
    }
    bool foundlosing = false;

    //checking if there is a losing configuration going from here. Then this position would be winning
    for(int i = 1;i<=x;i++){
        if(!winning(x-i,y,z))foundlosing = true;
    }
    for(int i = 1;i<=y;i++){
        if(!winning(x,y-i,z))foundlosing = true;
    }
    for(int i = 1;i<=z;i++){
        if(!winning(x,y,z-i))foundlosing = true;
    }
    fieldDefined[format(x,y,z)] = true;
    field[format(x,y,z)] = foundlosing;
    if(!foundlosing)cout << x << " " << y << " " << z << '\n';
    return foundlosing;
}
int main(){
    int x, y, z;
    cout << "input the number of pins in each line: \n";
    cin >> x >> y >> z;
    n = (x+1)*(y+1)*(z+1);
    field = new bool[n];
    fieldDefined = new bool[n];
    defX = x+1;
    defY = y+1;
    for(int i = 0;i<n;i++){
        fieldDefined[i] = 0;
    }
    cout << "\nif there is a move where you can get to these configurations just play it\n";
    cout << "the last move is what you should do now\n";
    cout << "\nlosing configurations: \n";
    field[format(0,0,0)] = false;
    fieldDefined[format(0,0,0)] = true;
    if(winning(x,y,z))cout << "\nthis position is winning";
    else cout << "\nthis position is losing unless your oponent makes a mistake";
    delete [] field;
    delete [] fieldDefined;
}