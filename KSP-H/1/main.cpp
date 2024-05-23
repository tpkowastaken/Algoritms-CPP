#include <iostream>
#include <fstream>
#include <vector>
int main()
{
    int numberOfppl = 0;
    std::ifstream file("01.in");
    file >> numberOfppl;
    std::vector<int> zeny(numberOfppl, 0);
    for (int i = 0; i < numberOfppl; i++)
    {
        file >> zeny[i];
    }
    int aktualniMin = INT32_MAX;
    int aktualniMax = INT32_MIN;
    int aktualniIndex = 0;
    int aktualniPocet = 0;
    int nejvyssiIndex = -1;
    int nejvyssiPocet = 0;
    std::vector<std::vector<int>> vector(numberOfppl, std::vector<int>(numberOfppl, -1));
    for (int i = 0; i < numberOfppl; i++)
    {
        aktualniPocet = 0;
        aktualniIndex = 0;
        aktualniMin = INT32_MAX;
        aktualniMax = INT32_MIN;
        for (int k = i; k < numberOfppl; k++)
        {
            if (zeny[k] > aktualniMax)
            {
                aktualniMax = zeny[k];
                aktualniPocet++;
                vector[i][aktualniIndex++] = k;
                if (zeny[k] < aktualniMin)
                {
                    aktualniMin = zeny[k];
                }
            }
        }
        aktualniMax = 0;
        for (int k = 0; k < i; k++)
        {
            if (zeny[k] < aktualniMin && zeny[k] > aktualniMax)
            {
                aktualniMax = zeny[k];
                aktualniPocet++;
                vector[i][aktualniIndex++] = k;
            }
        }
        if (aktualniPocet > nejvyssiPocet)
        {
            nejvyssiPocet = aktualniPocet;
            nejvyssiIndex = i;
        }
    }
    std::ofstream file2("01.out");
    for (int i = 0; i < numberOfppl; i++)
    {
        if (vector[nejvyssiIndex][i] == -1)
        {
            break;
        }
        file2 << vector[nejvyssiIndex][i] << " ";
    }
}