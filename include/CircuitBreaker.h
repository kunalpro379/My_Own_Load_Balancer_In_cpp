#ifndef CIRCUIT_BREAKER_H
#define CIRCUIT_BREAKER_H
#include <chrono>
using namespace std::chrono;
class CircuitBreaker
{
public:
    CircuitBreaker(int failureThreshold, int resetTimeout); // constructor
    // if reqest can proceed
    bool allowRequest();
    void recordFailure();
    void recordSuccess();

private:
    enum class State
    {
        OPEN,
        CLOSED,
        HALF_OPEN
    };

    bool isRateOk();
    void transitionTo(State newState); // State transitions
    State state;                       // current state
    int failureThreshold;
    int failureCount;
    // time after which to retry
    std::chrono::milliseconds resetTimeout;
    // time of last failure
    std::chrono::steady_clock::time_point lastFailureTime;

    int currentRate;
    int maxAllowedRequests;
};
#endif