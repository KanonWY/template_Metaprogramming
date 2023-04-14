#include <iostream>

/**
//  *   dependName and non-dependName
*/

template <typename T>
struct parser;

void handle(double value)
{
    std::cout << "double" << std::endl;
}

template <typename T>
struct parser
{
    void parse()
    {
        handle(63); //这个属于依赖名称，在模板定义时执行. 因此这里绑定的是double的。
    }
};

void handle(int value)
{
    std::cout << "int" << std::endl;
}


int main()
{
    parser<int> p;
    p.parse();
    return 0;
}