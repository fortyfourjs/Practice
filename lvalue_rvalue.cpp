#include <iostream>

int main()
{
    int x{ 1 };
    int& ref{ x };

    std::cout << x << ref << '\n'; // 1, 1

    int y{ 2 };
    ref = y;
    y = 3;

    std::cout << x << ref << '\n'; // 2, 2

    x = 4;

    std::cout << x << ref << '\n'; // 4. 4

    return 0;
}