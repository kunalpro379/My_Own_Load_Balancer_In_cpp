#ifndef REQUEST_PROCESSOR_H
#define REQUEST_PROCESSOR_H

#include "CircuitBreaker.h"
#include "ResponseHandler.h"
#include <memory>
#include <future>

class RequestProcessor {
public:
    RequestProcessor(std::shared_ptr<CircuitBreaker> circuitBreaker);

    template<typename Request>
    void processRequest(Request&& request, bool isAsync = false);

private:
    template<typename Request>
    void processAsync(Request&& request);

    template<typename Request>
    void processSync(Request&& request);

    bool checkBackendHealth();
    void forwardToBackend(const std::string& request);
    void handleBackendResponse(const std::string& response);
    void updateMetrics(bool success);

    std::shared_ptr<CircuitBreaker> circuitBreaker_;
    std::shared_ptr<ResponseHandler> responseHandler_;
    bool isProcessing_ = false;
};

#endif
