#include <type_traits>
#include <iostream>

int main()
{
    std::cout << std::is_same_v<int, const int> << std::endl;
    return 0;
}