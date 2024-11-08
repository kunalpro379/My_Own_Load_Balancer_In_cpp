// RateLimiter.cpp
#include "RateLimiter.hpp"
#include <iostream> // Include for debugging

// Constructor implementation
RateLimiter::RateLimiter(int maxRequests, int timeWindow)
    : maxRequests(maxRequests), timeWindow(timeWindow)
{
    std::cout << "RateLimiter initialized with maxRequests: " << maxRequests
              << " and timeWindow: " << timeWindow << " seconds." << std::endl;
}

// isRequestAllowed method implementation
bool RateLimiter::isRequestAllowed()
{
    auto now = std::chrono::steady_clock::now();

    // Clean up requests that are outside the time window
    std::cout << "Checking if request is allowed at time: "
              << std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count() << " seconds." << std::endl;

    while (!requestTimestamps.empty())
    {
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - requestTimestamps.front()).count();
        std::cout << "Elapsed time since first request: " << elapsed << " seconds." << std::endl;

        if (elapsed >= timeWindow)
        {
            std::cout << "Request timestamp outside of time window. Removing timestamp." << std::endl;
            requestTimestamps.pop();
        }
        else
        {
            std::cout << "Oldest request is still within the time window. Stopping cleanup." << std::endl;
            break; // Exit the loop if the oldest request is still within the time window
        }
    }

    // Check if we can allow a new request
    if (requestTimestamps.size() < maxRequests)
    {
        requestTimestamps.push(now); // Record the timestamp of this request
        std::cout << "Request allowed. Total requests: " << requestTimestamps.size() << std::endl;
        return true;
    }

    std::cout << "Request denied. Total requests: " << requestTimestamps.size() << std::endl;
    return false;
}
