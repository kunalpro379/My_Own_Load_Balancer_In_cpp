#include "CircuitBreaker.h"

#include <chrono>
#include "../client/RateLimiter.hpp"
#include <chrono>

// constructor
CircuitBreaker::CircuitBreaker(int failureThreshold, int resetTimeout)
{
    this->failureThreshold = failureThreshold;
    this->resetTimeout = std::chrono::milliseconds(resetTimeout);
    this->state = State::CLOSED;
    this->failureCount = 0;
}

bool CircuitBreaker::allowRequest()
{

    // This gets current time to check circuit breaker state and timeout
    auto now = std::chrono::steady_clock::now();

    // check if the breaker is open
    // and if the reset timeout has expired
    if (state == State::OPEN && (now - lastFailureTime) > resetTimeout)
    {
    }
}
