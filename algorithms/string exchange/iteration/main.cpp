#include <iostream>
#include <string.h>
using namespace std;
int *dafield;
int wordSize1, wordSize2;
string word1, word2;
int getFieldNum(int i){
    int value1 = dafield[i+1]; //right from the current checking num
    int value2 = dafield[i+wordSize2]; //down one
    int value3 = dafield[i+wordSize2+1]; // diagonal down right
    if(word1[i/wordSize2] == word2[i%wordSize2])return value3;
    if(value1 <= value2 && value1 <= value3)return value1+1;
    if(value2 <= value1 && value2 <= value3)return value2+1;
    else return value3+1;

}
int main(){
    cin >> word1 >> word2;
    wordSize1 = word1.size() + 1;
    wordSize2 = word2.size() + 1;
    int n = wordSize1 * wordSize2;
    dafield = new int[n];
    for(int i = 0;i<n;i++){
        dafield[i] = -1;
    }
    /* 
    pravidla:
    1. moznost: zmena pismenka - +1
    2. moznost: smazani - +1
    3. moznost: pridani - +1
    4. moznost: nic - +0
    snazime se zmenit word1, aby se rovnal word2
    */
    for(int i = 0;i<wordSize2;i++){ // filling out the outer obvious editation distance
        dafield[(n-1)-i] = i;
    }
    for(int i = 0;i<wordSize1;i++){
        dafield[(n-1)-((wordSize2)*i)] = i;
    }
    //pro každý zjišťujeme nejmenší možnou editační vzdálenost tím vyplňujeme doleva nahoru šikmo:
    // (wordSize2*y)+x
    {
        int currentFieldIndex;
        for(int i = 1;i<wordSize1 && i<wordSize2;i++){
            //doing the diagonal number
            currentFieldIndex = (wordSize2*(wordSize1-i-1))+(wordSize2-1-i);
            //doing the other numbers
            for(int g = currentFieldIndex;g>-1;g-=wordSize2){//going up 
                dafield[g] = getFieldNum(g);
            }
            for(int g = currentFieldIndex;g>currentFieldIndex-wordSize2+i;g--){//going left
                dafield[g] = getFieldNum(g);
            }
        }
    }


    cout << "editation distance: " << dafield[0] << '\n';





    cout << "\n  ";
    for(int i = 0;i<wordSize2;i++){
        cout << word2[i] << " ";
    }
    cout << "\n" << word1[0] << " ";
    for(int i = 0;i<n;i++){
        cout << dafield[i] << " ";
        if((i+1) % (wordSize2) == 0 && i!=n-1)cout << "\n" << word1[(i+1)/(wordSize2)] << " ";
    }
    delete [] dafield;
}