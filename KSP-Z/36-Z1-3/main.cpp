#include <iostream>
#include <vector>
int main()
{
    unsigned long long pocetSlepic = 0;
    unsigned long long d = 0;
    unsigned long long k = 0;
    unsigned long long p = 0;
    std::cin >> k >> p >> d;
    std::vector<unsigned long long> vylihnutiSlepic(d, 0);
    std::vector<unsigned long long> sneseniVajec(d, 0);
    for (unsigned long long i = 0; i < d; i++)
    {
        vylihnutiSlepic[i] = 0;
        sneseniVajec[i] = 0;
    }
    vylihnutiSlepic[k - 1] = 1;
    for (unsigned long long i = 0; i < d; i++)
    {
        if (vylihnutiSlepic[i] == 0 && sneseniVajec[i] == 0)
            continue;
        pocetSlepic += vylihnutiSlepic[i];
        if (i + p < d)
        {
            sneseniVajec[i + p] += vylihnutiSlepic[i];
        }
        if (i + k < d)
        {
            vylihnutiSlepic[i + k] += sneseniVajec[i];
            sneseniVajec[i + p] += sneseniVajec[i];
        }
    }
    std::cout << pocetSlepic;
}