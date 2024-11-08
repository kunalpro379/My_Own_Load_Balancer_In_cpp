// RateLimiter.hpp
#ifndef RATELIMITER_HPP
#define RATELIMITER_HPP

#include <chrono>
#include <queue>

class RateLimiter
{
public:
    // Constructor to initialize the RateLimiter with maxRequests and timeWindow
    RateLimiter(int maxRequests, int timeWindow);

    // Method to check if a new request is allowed
    bool isRequestAllowed();

private:
    int maxRequests;                                                     // Maximum number of requests allowed
    int timeWindow;                                                      // Time window in seconds for rate limiting
    std::queue<std::chrono::steady_clock::time_point> requestTimestamps; // Queue to store request timestamps
};

#endif // RATELIMITER_HPP
