#ifndef RESPONSE_HANDLER_H
#define RESPONSE_HANDLER_H

#include <string>
#include <functional>
#include <memory>

enum class ResponseStatus {
    Success,
    Error
};

class ResponseHandler {
public:
    ResponseHandler();
    
    void handleResponse(ResponseStatus status, const std::string& response);
    bool isRetryNeeded(const std::string& errorMessage);
    void setRetryCallback(std::function<void()> callback);
    void setErrorCallback(std::function<void(const std::string&)> callback);

private:
    void handleSuccess(const std::string& response);
    void handleError(const std::string& errorMessage);
    void triggerRetry();
    void updateMetrics(ResponseStatus status);

    std::function<void()> retryCallback_;
    std::function<void(const std::string&)> errorCallback_;
    int retryCount_ = 0;
    static constexpr int MAX_RETRIES = 3;
};

#endif
