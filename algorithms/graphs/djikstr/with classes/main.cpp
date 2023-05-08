#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int n; //počet vrcholů
int *connections, *d, *p; //d = vzdálenost od startu, p = předchozí vrchol
int start,finish;

void cleanup(){
    delete [] connections;
}

int format(int x, int y, int z){
    return x+n*(y+n*z);
}

class node{
    public:
        int s;
        int l = 0;
        int *x,*vals, *nodes;
        node(){
            s = n+1;
            x = new int[s]; // stores active distances from start
            vals = new int[s]; //vals[index in x] = node relative to x[index in x]
            nodes = new int[n]; //nodes[node] = node position in x = index in x
            for(int i = 0;i<n;i++){
                x[i] = -1;
                nodes[i] = -1; 
            }
            x[n] = -1; //last value in x
            x[0] = -404;//an empty value
            vals[0] = -404;
        }
        ~node(){
            delete [] x;
            delete [] nodes;
            delete [] vals;
        }
        void move(int from, int to){
            x[to] = x[from];
            vals[to] = vals[from];
            nodes[vals[from]] = to;
        }
        void write(int value, int i, int node){
            x[i] = value;
            vals[i] = node;
            nodes[node] = i;
            l++;
        }
        void remove(int i){
            x[i] = -1;
            vals[i] = -1;
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


class heap{
    private:
        node pole;
    public:
        int low(){return pole.vals[1];}
        void add(int value, int node){
            if(pole.nodes[node] != -1){
                cout << "trying to create duplicate node!: node: " << node << " new value: " << value << " value in heap: " << pole.x[pole.nodes[node]] << " x index: " << pole.nodes[node] << "\n";
                return;
            }
            int i = pole.l+1;
            while(pole.x[i/2] != -404){
                if(pole.x[i/2]>value){
                    pole.move(i, i/2);
                    i = i/2;
                }
                else{
                    pole.write(value, i, node);
                    return;
                }
            }
            pole.write(value, i, node);
        }
        void extractMin(){//vars vals and nodes not done yet
            int i = 1;
            pole.nodes[pole.vals[1]] = -1;//removing it from nodes
            while((pole.x[i*2] !=-1 || pole.x[i*2+1] != -1) && i*2+1 < pole.s){//dokud existuje aspon jedna hodnota pod a nesnazi se to pristoupit k hodnote mimo pole
                if(pole.x[i*2] != -1 && pole.x[i*2+1] == -1){//if the second is non-existant move it up
                    pole.move(i*2, i);
                    i = i*2;
                }
                else if(pole.x[i*2] == -1 && pole.x[i*2+1] != -1){//if the first is non-existant move it up
                    pole.move(i*2+1, i);
                    i = i*2+1;
                }
                else if(pole.x[i*2] <= pole.x[i*2+1]){//if the first is smaller move that up
                    pole.move(i*2, i);
                    i = i*2;
                }
                else if(pole.x[i*2+1] < pole.x[i*2]){//if the second is smaller move that up
                    pole.move(i*2+1, i);
                    i = i*2+1;
                }
            }
            if(i*2+1 >= pole.s && i*2 < pole.s && pole.x[i*2] != -1){//pokud failnulo while u posledni podminky, ale existuje hodnota na poslednim indexu
                pole.move(i*2, i);
                i = i*2;
            }
            pole.remove(i);
        }
        void decrease(int value, int node){
            int i = pole.nodes[node];
            if(value>pole.x[i]){
                cout << "error while decreasing: entered value: " << value << " original value: " << pole.x[i] << " index: " << i << '\n';
                return;
            }
            if(pole.nodes[node] == -1){
                cout << "trying to decreasae a non-existant node: node: " << node << " new value: " << value << " value in heap: " << pole.x[pole.nodes[node]] << " x index: " << pole.nodes[node] << "\n";
                return;
            }
            while(pole.x[i/2] != -404){
                if(pole.x[i/2] > value){
                    pole.move(i/2, i);
                    i = i/2;
                }
                else{
                    pole.write(value, i, node);
                    return;
                }
            }
            pole.write(value, i, node);
        }
        void print(){
            pole.print();
        }
};

int main(){
    //importing data
    ifstream file("input.txt");
    int h, k = -1, space = 0;//h - first index, k - second index, space - third index
    bool action, nFound; //action - if there has been a change - counters random new lines and comments

    if(file){
        string line;
        while(getline(file, line)){
            for(int i = 0;line[i] != '\0';i++){
                if(line[i] == 'N'){
                    action = true;
                    break;
                }
                if(line[i] == 35)break;//komentare (check pro #)
                else if(line[i] == 47){//check pro / (start a finish)
                    bool first = true;//bool jestli to je prvni nebo druhy cislo v radku
                    for(int g = i+1;line[g] != '\0';g++){
                        if(line[g]<58 && line[g]>47){
                            if(first){
                                start = start*10+(line[g]-48);
                            }
                            else finish = finish*10+(line[g]-48);
                        }
                        else first = false;
                    }
                    break;
                }
                if(line[i] == 32 && space == 1){//kontrolování zda to je mezera a oddeleni pokud ano
                    space = 0;
                    h++;
                }
                else if(line[i] == 32){//kontrolovani zda to je mezera
                    space = 1;
                }
                else if(!nFound && line[i] < 58 && line[i]>47){
                    n = line[i]-48;
                    for(int g = 1;line[g] != '\0' && line[g]<58 && line[g]>47;g++){
                        n = n*10+(line[g]-48);
                    }
                    //creating variables since we know n
                    connections = new int[n*n*2];
                    d = new int[n];
                    p = new int[n];
                    for(int i = 0;i<n*n*2;i++){
                        connections[i] = -1;
                    }
                    for(int i = 0;i<n;i++){
                        d[i] = -1;
                        p[i] = -1;
                    }
                    //marking it so it doesn't start this again
                    nFound = true;
                    break;
                }
                else if(line[i] < 58 && line[i] > 47){
                    if(connections[format(k,h,space)] == -1 )connections[format(k,h,space)] = 0; //making sure we don't have a -1 when the command under tries to handle that
                    connections[format(k,h,space)] = connections[format(k,h,space)]*10+(line[i]-48); //transfering from ascii to int (this logic only works with positive integers)
                    action = true;
                }
                
            }
            if(action)k++;
            action = false;
            space = 0;
            h = 0;
        }
    }
    file.close();
    cout << "\n";
    //printing connection
    for(int i = 0;i<n;i++){
        for(int u = 0; u<n-1; u++){
            if(connections[format(i,u,0)] != -1)cout << connections[format(i,u,0)] << " " <<connections[format(i,u,1)] << " ";
            
        }
        if(connections[format(n-1,n-1,0)] != -1)cout << connections[format(i,n-1,0)] << " " << connections[format(i,n-1,0)];
        cout << '\n';
    }

    cout << "\nstart: " << start << " finish: " << finish << '\n';
    //creating heap structure
    heap s;
    //djikstras algorithm
    d[start] = 0;
    s.add(0,start);
    while(s.low() != -1){
        for(int i = 0;connections[format(s.low(), i, 0)] != -1 && i<n;i++){
            if(d[connections[format(s.low(), i, 0)]] > d[s.low()] + connections[format(s.low(), i, 1)]){//pokud vzdálenost k nodu je větší než vzdálenost k aktualnímu bodu + cesta k nodu
                s.decrease( ( d[s.low()] + connections[format(s.low(), i, 1)] ), connections[format(s.low(), i, 0)]); //zmenšení v haldě
                d[connections[format(s.low(), i, 0)]] = d[s.low()] + connections[format(s.low(), i, 1)];//přepsání vzdálenosti
                p[connections[format(s.low(), i, 0)]] = s.low(); // přepsání předchozího bodu
            }
            else if(d[connections[format(s.low(), i, 0)]] == -1){ //pokud node ještě nemá vzdálenost
                s.add(( d[s.low()] + connections[format(s.low(), i, 1)] ), connections[format(s.low(), i, 0)]);
                d[connections[format(s.low(), i, 0)]] = d[s.low()] + connections[format(s.low(), i, 1)];//vytvoření vzdálenosti
                p[connections[format(s.low(), i, 0)]] = s.low(); // vytvoření předchozího bodu
            }
        }
        s.extractMin();
    }
    //print path
    int i = finish;
    while(p[i]!=-1){
        cout << i << " <- ";
        i = p[i];
    }
    cout << i << "\n";




    cleanup();
}