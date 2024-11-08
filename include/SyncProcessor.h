#ifndef SYNC_PROCESSOR_H
#define SYNC_PROCESSOR_H

#include "CircuitBreaker.h"
#include "AlertManager.h"
#include <memory>
#include <functional>

class SyncProcessor {
public:
    SyncProcessor(std::shared_ptr<CircuitBreaker> circuitBreaker, 
                 std::shared_ptr<AlertManager> alertManager)
        : circuitBreaker_(circuitBreaker)
        , alertManager_(alertManager) {}

    template<typename Request>
    bool processRequest(Request& request) {
        if (!circuitBreaker_->allowRequest()) {
            alertManager_->sendAlert("Circuit breaker open, request rejected");
            return false;
        }

        try {
            bool result = processSync(request);
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
            alertManager_->sendAlert("Sync processing failed: " + std::string(e.what()));
            updateMetrics(false);
            return false;
        }
    }

private:
    template<typename Request>
    bool processSync(Request& request) {
        // Synchronous processing logic
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
