#include <iostream>
#include <string.h>
using namespace std;
int *dafield, *nextIndex;
int wordSize1, wordSize2;
int word(const string word1, const string word2){
    string newWord1 = word1, newWord2 = word2;
    int value1, value2, value3;
    if(word1.size() == 0 || word1 == "\0" || word1 == "\n"){ 
        dafield[wordSize2*((wordSize1-1) - word1.size()) + ((wordSize2-1) - word2.size())] = word2.size();
        nextIndex[wordSize2*((wordSize1-1) - word1.size()) + ((wordSize2-1) - word2.size())] = -1;
        return word2.size();
        }
    if(word2.size() == 0 || word2 == "\0" || word2 == "\n"){
        dafield[wordSize2*((wordSize1-1) - word1.size()) + ((wordSize2-1) - word2.size())] = word1.size();
        nextIndex[wordSize2*((wordSize1-1) - word1.size()) + ((wordSize2-1) - word2.size())] = -1;
        return word1.size();
        }
    if(dafield[wordSize2*((wordSize1-1) - word1.size()) + ((wordSize2-1) - word2.size())] != -1) return dafield[wordSize2*((wordSize1-1) - word1.size()) + ((wordSize2-1) - word2.size())];
    if(word1[0] == word2[0]){//(posouváme se šikmo dolů doprava)
        newWord1.erase(0,1);
        newWord2.erase(0,1);
        value1 = word(newWord1, newWord2) + 0;
    }
    else{//měníme znak newWord1[0] na newWord2[0] (posouváme se šikmo dolů doprava)
        newWord1.erase(0,1);
        newWord2.erase(0,1);
        value1 = word(newWord1, newWord2) + 1;
    }
    newWord1 = word1;
    {//mažeme znak newWord1[0]posouváme se dolů
        newWord1.erase(0,1);
        value2 = word(newWord1, word2) + 1;
    }
    newWord2 = word2;
    {//přidáme znak newword2[0] na začátek newword1 další krok by pak byl odstranění obou, protože znaky budou stejné, tak to přeskočíme.
        newWord2.erase(0,1);//posouváme se doprava v tabulce
        value3 = word(word1, newWord2) + 1;
    }
    if(value1 <= value2 && value1 <= value3){
        int currentIndex = wordSize2*((wordSize1-1) - word1.size()) + ((wordSize2-1) - word2.size());
        dafield[currentIndex] = value1;
        nextIndex[currentIndex] = currentIndex + wordSize2 + 1;
        return value1;
    }//min(value1,value2,value3)
    if(value2 <= value1 && value2 <= value3){
        int currentIndex = wordSize2*((wordSize1-1) - word1.size()) + ((wordSize2-1) - word2.size());
        dafield[currentIndex] = value2;
        nextIndex[currentIndex] = currentIndex + wordSize2;
        return value2;
    }
    else{
        int currentIndex = wordSize2*((wordSize1-1) - word1.size()) + ((wordSize2-1) - word2.size());
        dafield[currentIndex] = value3;
        nextIndex[currentIndex] = currentIndex + 1;
        return value3;
    } 



    

}
int main(){
    string word1, word2;
    cin >> word1 >> word2;
    wordSize1 = word1.size() + 1;
    wordSize2 = word2.size() + 1;
    int n = wordSize1 * wordSize2;
    dafield = new int[n];
    nextIndex = new int[n];
    for(int i = 0;i<n;i++){
        dafield[i] = -1;
        nextIndex[i] = -1;
    }
    cout << "editation distance: " << word(word1, word2);
    /* 
    pravidla:
    1. moznost: zmena pismenka - +1
    2. moznost: smazani - +1
    3. moznost: pridani - +1
    4. moznost: nic - +0
    snazime se zmenit word1, aby se rovnal word2
    */
    cout << "\n  ";
    for(int i = 0;i<wordSize2;i++){
        cout << word2[i] << " ";
    }
    cout << "\n" << word1[0] << " ";
    for(int i = 0;i<n;i++){
        cout << dafield[i] << " ";
        if((i+1) % (wordSize2) == 0 && i!=n-1)cout << "\n" << word1[(i+1)/(wordSize2)] << " ";
    }
    cout << "\n\n";
    for(int i = 0;i<n && i != -1;){
        for(int g = i/wordSize2;g<wordSize1;g++){//printing the first word (word1)
            cout << word1[g];
        }
        cout << " ";
        for(int g = i%wordSize2;g<wordSize2;g++){//printing the second word (word2)
            cout << word2[g];
        }
        cout << "\n";
        if(nextIndex[i] == i+1)cout << "pridani znaku: \'" << word2[i%wordSize2] << "\' k prvnimu slovu\n";
        else if(nextIndex[i] == i+wordSize2)cout << "mazeme znak: \'" << word1[i/wordSize2] << "\' z prvniho slova\n";
        else if(nextIndex[i] == i+wordSize2 + 1 && word1[i/wordSize2] == word2[i%wordSize2])cout << "pokracujeme beze zmen\n";
        else if(word1[i/wordSize2] != '\0' || word2[i%wordSize2] != '\0')cout << "menime prvni znak z prvniho slova: \'" << word1[i/wordSize2] << "\' na prvni znak druheho slova: \'" << word2[i%wordSize2] << "\' \n";

        i = nextIndex[i];
    }
   
    delete [] nextIndex;
    delete [] dafield;
}