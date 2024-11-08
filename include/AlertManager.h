#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H

#include "Config.h"
#include <string>
#include <queue>
#include <mutex>
#include <thread>

class AlertManager {
public:
    AlertManager(const Config& config) 
        : config_(config)
        , isRunning_(true) {
        alertThread_ = std::thread(&AlertManager::processAlerts, this);
    }

    ~AlertManager() {
        isRunning_ = false;
        if (alertThread_.joinable()) {
            alertThread_.join();
        }
    }

    void sendAlert(const std::string& message, AlertLevel level = AlertLevel::WARNING) {
        std::lock_guard<std::mutex> lock(mutex_);
        alerts_.push({message, level, std::chrono::system_clock::now()});
    }

private:
    enum class AlertLevel {
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    struct Alert {
        std::string message;
        AlertLevel level;
        std::chrono::system_clock::time_point timestamp;
    };

    void processAlerts() {
        while (isRunning_) {
            std::unique_lock<std::mutex> lock(mutex_);
            if (!alerts_.empty()) {
                Alert alert = alerts_.front();
                alerts_.pop();
                lock.unlock();
                
                // Process alert based on level
                switch (alert.level) {
                    case AlertLevel::CRITICAL:
                        notifyOnCall(alert);
                        break;
                    case AlertLevel::ERROR:
                        logError(alert);
                        break;
                    default:
                        logWarning(alert);
                        break;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void notifyOnCall(const Alert& alert);
    void logError(const Alert& alert);
    void logWarning(const Alert& alert);

    Config config_;
    std::queue<Alert> alerts_;
    std::mutex mutex_;
    std::thread alertThread_;
    std::atomic<bool> isRunning_;
};

#endif
