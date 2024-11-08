#include "ResponseHandler.h"
#include <iostream>

ResponseHandler::ResponseHandler() {}

void ResponseHandler::handleResponse(ResponseStatus status, const std::string& response) {
    if (status == ResponseStatus::Success) {
        handleSuccess(response);
    }
    else {
        handleError(response);
    }
    updateMetrics(status);
}

void ResponseHandler::handleSuccess(const std::string& response) {
    retryCount_ = 0;
    // Process successful response
    std::cout << "Success: " << response << std::endl;
}

void ResponseHandler::handleError(const std::string& errorMessage) {
    if (isRetryNeeded(errorMessage) && retryCount_ < MAX_RETRIES) {
        triggerRetry();
    }
    else if (errorCallback_) {
        errorCallback_(errorMessage);
    }
}

bool ResponseHandler::isRetryNeeded(const std::string& errorMessage) {
    // Implement retry logic based on error type
    // For example, retry on temporary failures but not on permanent errors
    return errorMessage.find("temporary") != std::string::npos;
}

void ResponseHandler::triggerRetry() {
    retryCount_++;
    if (retryCallback_) {
        retryCallback_();
    }
}

void ResponseHandler::setRetryCallback(std::function<void()> callback) {
    retryCallback_ = std::move(callback);
}

void ResponseHandler::setErrorCallback(std::function<void(const std::string&)> callback) {
    errorCallback_ = std::move(callback);
}

void ResponseHandler::updateMetrics(ResponseStatus status) {
    // Update metrics based on response status
    // This could integrate with a metrics collection system
} 