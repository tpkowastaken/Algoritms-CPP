#include <fstream>
#include <iostream>
#include <unordered_map>
int main()
{
    std::ifstream myfile("01.in");
    std::unordered_map<std::string, int> hashPoctu;
    {
        std::string pocet;
        bool prvni = true;
        while (std::getline(myfile, pocet))
        {
            if (prvni)
            {
                prvni = false;
                continue;
            }
            hashPoctu[pocet]++;
        }
    }
    int highest = 0;
    std::string highestName;
    for (auto &pocet : hashPoctu)
    {
        if (pocet.second > highest)
        {
            highest = pocet.second;
            highestName = pocet.first;
        }
    }
    std::cout << highestName << " " << highest;
}