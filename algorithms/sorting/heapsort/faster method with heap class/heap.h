#ifndef HEAP_H
#define HEAP_H


class heap{
    private:
        int *x;
        int n;
        int l = 0;//number of values in heap
        int empty = 2147483647;//integer limit
    public:

        void setup(int size){//creates the object
            if(!size){
                std::cout << "error: function setup called with input: 0\n";
                return;
            }
            n = size;
            x = new int[n+1]; // stores active distances from start
            for(int i = 1;i<n+1;i++){
                x[i] = 0;
            }
            x[0] = empty;//an empty value
        }

        ~heap(){
            delete [] x;
        }

        void bubbledown(int i){
            int value = x[i];
            while((x[i*2] !=empty || x[i*2+1] != empty) && i*2+1 <= n+1){//dokud existuje aspon jedna hodnota pod a nesnazi se to pristoupit k hodnote mimo pole
                if(i*2+1 >= n+1 && i*2 < n+1 && x[i*2] != empty && x[i*2] < value){//pokud failnulo while u posledni podminky, ale existuje hodnota na poslednim indexu
                    i = move(i*2,i);
                    break;
                }
                if(x[i*2] != empty && x[i*2+1] == empty && (x[i*2] < value )){//if the second is non-existant move it up
                    i = move(i*2,i);
                }
                else if(x[i*2] == empty && x[i*2+1] != empty && (x[i*2+1] < value)){//if the first is non-existant move it up
                    i = move(i*2+1,i);
                }
                else if(x[i*2] <= x[i*2+1] && x[i*2] < value){//if the first is smaller move that up
                    i = move(i*2,i);
                }
                else if(x[i*2+1] < x[i*2] && x[i*2+1] < value){//if the second is smaller move that up
                    i = move(i*2+1,i);
                }
                else break;
            }
            x[i] = value;//writing
        }

        void sort(){
            int value;
            for(int i = l;i-1;i--){
                value = x[i];
                if(i%2 == 1){
                    int g = i;
                    while(g){
                        if(x[g-1] <= x[g] || x[g/2] <= x[g] || g-1 == 0)break;
                        x[g] = x[g/2];
                        bubbledown(g);
                        g /= 2;
                    }
                    x[g] = value;
                }
                else{
                    int g = i;
                    while(g){
                        if(x[g/2] <= x[g] || g-1 == 0)break;
                        x[g] = x[g/2];
                        bubbledown(g);
                        g /= 2;
                    }
                    x[g] = value;
                }
            }
        }

        void importheap(int *pointer, int size){
            if(!size){
                std::cout << "error: function importheap called with input: 0\n";
                return;
            }
            n = size;
            x = new int[n+1]; // stores active distances from start
            for(int i = 1;i<n+1;i++){
                x[i] = 0;
            }
            x[0] = empty;//an empty value

            memcpy(x+1,pointer,size*sizeof(int));
            l = n;
        }
        void importheap(int *pointer){
            if(!n){
                std::cout << "n is zero. This either means that this object hasn't been built using setup() or u typed zero as input\n";
            }
            memcpy(x+1,pointer,n*sizeof(int));
            l = n;
        }
        void add(int value){
            int i = l+1;
            while(i/2){
                if(x[i/2]>value){
                    i = move(i/2,i);
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

        int move(int from, int to){
            x[to] = x[from];
            return from;
        }

        int low(){return x[1];}

        void extractMin(){
            int i = 1;
            while((x[i*2] != empty || x[i*2+1] != empty) && i*2+1 < n+1){//dokud existuje aspon jedna hodnota pod a nesnazi se to pristoupit k hodnote mimo pole
                if(x[i*2] != empty && x[i*2+1] == empty ){//if the second is non-existant move it up
                    i = move(i*2,i);
                }
                else if(x[i*2] == empty && x[i*2+1] != empty){//if the first is non-existant move it up
                    i = move(i*2+1,i);
                }
                else if(x[i*2] <= x[i*2+1]){//if the first is smaller move that up
                    i = move(i*2,i);
                }
                else if(x[i*2+1] < x[i*2]){//if the second is smaller move that up
                    i = move(i*2+1,i);
                }
            }
            if(i*2+1 == n+1 && x[i*2] != empty){//pokud failnulo while u posledniho indexu, ale existuje hodnota na tomto poslednim indexu
                i = move(i*2,i);
            }
            x[i] = empty;//writing
            l--;
        }

        void print(){
            std::cout << "printing array x:\n{";
            for(int i = 1;i<l;i++){
                std::cout << x[i] << ", ";
            }
            std::cout << x[l] << "}\n";
        }

};




#endif //HEAP_H