#include <iostream>
#include <memory>

template <typename D>
struct base
{
    void f()
    {
        static_cast<D *>(this)->f_imp();
    }

    base()
    {
        std::cout << "base()" << std::endl;
    }
    ~base()
    {
        std::cout << "~base()" << std::endl;
    }
};

struct God : public base<God>
{
    static void f_imp()
    {
        std::cout << "God f_imp()" << std::endl;
    }
    God()
    {
        std::cout << "God()" << std::endl;
    }

    ~God()
    {
        std::cout << "~God()" << std::endl;
    }
};

struct Dv : public base<Dv>
{
    static void f_imp()
    {
        std::cout << "Dv f_imp()" << std::endl;
    }
};

int nomake()
{
    base<God> *sp = new God(); //这里实际指向的也是base对象
    sp->f();
    delete sp;
    return 0;
}

int makeuse()
{
    std::shared_ptr<base<God>> sp = std::make_shared<God>();
    sp->f();
    return 0;
}

template <typename D>
class registry
{
};

int main()
{

    return 0;
}