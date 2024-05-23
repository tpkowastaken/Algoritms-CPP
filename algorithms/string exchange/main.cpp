#include <iostream>
#include <string.h>
using namespace std;
int wordSize1, wordSize2;
int word(const string word1, const string word2){
    string newWord1 = word1, newWord2 = word2;
    int value1, value2, value3;
    if(word1.size() <= 0 || word1 == "\0" || word1 == "\n") return word2.size();
    if(word2.size() <= 0 || word2 == "\0" || word2 == "\n") return word1.size();
    if(word1[0] == word2[0]){
        newWord1.erase(0,1);
        newWord2.erase(0,1);
        value1 = word(newWord1, newWord2) + 0;
    }
    else{//měníme znak newWord1[0] na newWord2[0]
        newWord1.erase(0,1);
        newWord2.erase(0,1);
        value1 = word(newWord1, newWord2) + 1;
    }
    newWord1 = word1;
    {//mažeme znak newWord1[0]
        newWord1.erase(0,1);
        value2 = word(newWord1, word2) + 1;
    }
    newWord2 = word2;
    {//přidáme znak newword2[0] na začátek newword1
        newWord2.erase(0,1);
        value3 = word(word1, newWord2) + 1;
    }
    if(value1 <= value2 && value1 <= value3)return value1;
    if(value2 <= value1 && value2 <= value3)return value2;
    else return value3;



    

}
int main(){
    string word1, word2;
    cin >> word1 >> word2;
    wordSize1 = word1.size() + 1;
    wordSize2 = word2.size() + 1;
    cout << "editation distance: " << word(word1, word2);
    /* 
    pravidla:
    1. moznost: zmena pismenka - +1
    2. moznost: smazani - +1
    3. moznost: pridani - +1
    4. moznost: nic - +0
    snazime se zmenit word1, aby se rovnal word2
    */
}