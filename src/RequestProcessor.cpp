#include "RequestProcessor.h"
#include <thread>

RequestProcessor::RequestProcessor(std::shared_ptr<CircuitBreaker> circuitBreaker)
    : circuitBreaker_(std::move(circuitBreaker))
    , responseHandler_(std::make_shared<ResponseHandler>()) {
}

template<typename Request>
void RequestProcessor::processRequest(Request&& request, bool isAsync) {
    if (!circuitBreaker_->allowRequest()) {
        responseHandler_->handleResponse(ResponseStatus::Error, "Circuit breaker open");
        return;
    }

    if (isAsync) {
        processAsync(std::forward<Request>(request));
    }
    else {
        processSync(std::forward<Request>(request));
    }
}

template<typename Request>
void RequestProcessor::processAsync(Request&& request) {
    std::async(std::launch::async, [this, request = std::forward<Request>(request)]() {
        processSync(std::forward<Request>(request));
    });
}

template<typename Request>
void RequestProcessor::processSync(Request&& request) {
    if (!checkBackendHealth()) {
        circuitBreaker_->recordFailure();
        responseHandler_->handleResponse(ResponseStatus::Error, "Backend unhealthy");
        return;
    }

    try {
        forwardToBackend(request);
        circuitBreaker_->recordSuccess();
        updateMetrics(true);
    }
    catch (const std::exception& e) {
        circuitBreaker_->recordFailure();
        responseHandler_->handleResponse(ResponseStatus::Error, e.what());
        updateMetrics(false);
    }
}

bool RequestProcessor::checkBackendHealth() {
    // Implement backend health check logic
    return true;
}

void RequestProcessor::forwardToBackend(const std::string& request) {
    // Implement backend request forwarding logic
}

void RequestProcessor::updateMetrics(bool success) {
    // Update request processing metrics
} 