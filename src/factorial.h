#ifndef _FACTORIAL_H_
#define _FACTORIAL_H_

#include <cstddef>

std::size_t factorial(int n)
{
    std::cout << "factorial " << n << std::endl;
    std::size_t f = 1;
    for (int i = 1; i < n+1; i++)
        f *= i;

    std::cout << "return factorial " << f << std::endl;
    return f;
}

#endif /* _FACTORIAL_H_ */
