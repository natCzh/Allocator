#ifndef _FACTORIAL_H_
#define _FACTORIAL_H_

#include <cstddef>

std::size_t factorial(int n)
{
    std::size_t f = 1;
    for (int i = 1; i < n+1; i++)
        f *= i;

    return f;
}

#endif /* _FACTORIAL_H_ */
