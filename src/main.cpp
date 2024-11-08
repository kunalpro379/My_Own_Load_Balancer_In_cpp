// main.cpp
#include <iostream>
#include "../client/RateLimiter.hpp"

int main()
{
    RateLimiter limiter(1000, 120); // 10 requests per 120 seconds
    if (limiter.isRequestAllowed())
    {
        std::cout << "Request allowed." << std::endl;
    }
    else
    {
        std::cout << "Request denied." << std::endl;
    }
    return 0;
}
