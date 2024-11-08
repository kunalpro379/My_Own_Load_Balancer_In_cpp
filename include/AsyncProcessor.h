#ifndef ASYNC_PROCESSOR_H
#define ASYNC_PROCESSOR_H

#include "CircuitBreaker.h"
#include "AlertManager.h"
#include <future>
#include <memory>

class AsyncProcessor {
public:
    AsyncProcessor(std::shared_ptr<CircuitBreaker> circuitBreaker,
                  std::shared_ptr<AlertManager> alertManager)
        : circuitBreaker_(circuitBreaker)
        , alertManager_(alertManager) {}

    template<typename Request>
    std::future<bool> processRequest(Request& request) {
        if (!circuitBreaker_->allowRequest()) {
            alertManager_->sendAlert("Circuit breaker open, async request rejected");
            return std::async(std::launch::deferred, []() { return false; });
        }

        return std::async(std::launch::async, [this, request]() {
            try {
                bool result = processAsync(request);
                if (result) {
                    circuitBreaker_->recordSuccess();
                    updateMetrics(true);
                } else {
                    circuitBreaker_->recordFailure();
                    updateMetrics(false);
                }
                return result;
            } catch (const std::exception& e) {
                circuitBreaker_->recordFailure();
                alertManager_->sendAlert("Async processing failed: " + std::string(e.what()));
                updateMetrics(false);
                return false;
            }
        });
    }

private:
    template<typename Request>
    bool processAsync(Request& request) {
        // Asynchronous processing logic
        if (checkBackendHealth()) {
            return forwardToBackend(request);
        }
        return false;
    }

    bool checkBackendHealth();
    bool forwardToBackend(const std::string& request);
    void updateMetrics(bool success);

    std::shared_ptr<CircuitBreaker> circuitBreaker_;
    std::shared_ptr<AlertManager> alertManager_;
};

#endif
