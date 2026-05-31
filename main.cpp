#include <iostream>
#include "BigInt.h"

template <typename T>
T sqr(const T &value)
{
    return value * value;
}

int main()
{
    std::cout << "Exceptions check\n"
              << std::endl;

    try
    {
        std::cout << "Wrong string cheeck" << std::endl;
        BigInt invalid("123a45");
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Err caught " << e.what() << "\n"
                  << std::endl;
    }

    BigInt a("999999999999999999999999999999");
    BigInt b("111111111111111111111111111111");

    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "A + B   = " << (a + b) << std::endl;
    std::cout << "A - B   = " << (a - b) << std::endl;
    std::cout << "A * B   = " << (a * b) << "\n"
              << std::endl;

    BigInt c("-500000000000000000");
    BigInt d("100000000000000000");
    std::cout << "C (" << c << ") + D (" << d << ") = " << (c + d) << std::endl;
    std::cout << "D (" << d << ") - C (" << c << ") = " << (d - c) << "\n"
              << std::endl;

    int simple_num = 12;
    BigInt big_num("123456789123456789123456789");

    std::cout << "Default int sqrt: " << sqr(simple_num) << std::endl;
    std::cout << "BigInt sqrt: " << sqr(big_num) << std::endl;

    return 0;
}