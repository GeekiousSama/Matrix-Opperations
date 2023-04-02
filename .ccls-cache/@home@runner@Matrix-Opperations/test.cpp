#include <iostream>
#include <typeinfo>

class Test
{
    int a;
public:
    Test(): a{1}
    {
        Test(Test::a);
        std::cout << "In Test::Test() with a = " << Test::a << '\n';
    }
    Test(int a): a{a}
    {
        std::cout << "In Test::Test(int a) with a = " << Test::a << '\n';
        if(Test::a < 4)
        {
            Test::a++;
            Test(Test::a);
        }
    }
    int get()
    {
        return a;
    }
};

int main()
{
    try
        Test t;
    
    std::cout << t.get();

    return 0;
}