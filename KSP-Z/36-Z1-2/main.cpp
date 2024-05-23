#include <iostream>
#include <fstream>
struct souradnice
{
    int x;
    int y;
};
int main()
{
    souradnice bagr;
    souradnice krabice;
    std::string instrukce;
    std::ifstream file("01.in");
    file >> bagr.x >> bagr.y >> krabice.x >> krabice.y >> instrukce;
    std::cout << bagr.x << bagr.y << krabice.x << krabice.y << instrukce;
    for (int i = 0; instrukce[i] != '\0'; i++)
    {
        switch (instrukce[i])
        {
        case 'N':
        case 'n':
            bagr.y++;
            if (bagr.x == krabice.x && bagr.y == krabice.y)
                krabice.y++;
            break;
        case 'P':
        case 'p':
            bagr.x++;
            if (bagr.x == krabice.x && bagr.y == krabice.y)
                krabice.x++;
            /* code */
            break;
        case 'L':
        case 'l':
            bagr.x--;
            if (bagr.x == krabice.x && bagr.y == krabice.y)
                krabice.x--;
            /* code */
            break;
        case 'D':
        case 'd':
            bagr.y--;
            if (bagr.x == krabice.x && bagr.y == krabice.y)
                krabice.y--;
            /* code */
            break;

        default:
            break;
        }
    }
    std::cout << bagr.x << " " << bagr.y << '\n'
              << krabice.x << " " << krabice.y;
}