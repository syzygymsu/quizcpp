#include <iostream>
 
int direct(int b)
{
    return b;
}
 
int sum(int a, int b)
{
    return a+b;
}
 
void print(int b,int (*func)(int))
{
    std::cout << func(b) << std::endl;
}
 
int main(int argc, char** argv)
{
    int arg=5;
    print(arg,&direct);
    print(arg, [](int a) { return sum(1, a); });
}
