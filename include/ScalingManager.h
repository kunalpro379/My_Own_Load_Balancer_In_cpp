#ifndef SCALING_MANAGER_HPP
#define SCALING_MANAGER_HPP

#include <chrono>
#include <thread>
#include "WorkerPoolManager.h"

class ScalingManager {
public:
    ScalingManager(WorkerPoolManager& poolManager)
        : poolManager_(poolManager)
        , isRunning_(true)
        , scaleCheckInterval_(std::chrono::seconds(30))  // Check scaling every 30 seconds
    {
        // Start scaling monitor thread
        monitorThread_ = std::thread(&ScalingManager::monitor, this);
    }

    ~ScalingManager() {
        shutdown();
    }

    void shutdown() {
        isRunning_ = false;
        if (monitorThread_.joinable()) {
            monitorThread_.join();
        }
    }

    void setScalingPolicy(float upscaleThreshold = 0.75f, float downscaleThreshold = 0.25f) {
        upscaleThreshold_ = upscaleThreshold;
        downscaleThreshold_ = downscaleThreshold;
    }

private:
    void monitor() {
        while (isRunning_) {
            auto stats = poolManager_.getStats();
            float utilizationRate = calculateUtilization(stats);

            if (utilizationRate > upscaleThreshold_) {
                scaleUp();
            } else if (utilizationRate < downscaleThreshold_) {
                scaleDown();
            }

            std::this_thread::sleep_for(scaleCheckInterval_);
        }
    }

    float calculateUtilization(const WorkerPoolManager::PoolStats& stats) {
        if (stats.totalWorkers == 0) return 1.0f;  // Indicate full utilization if no workers
        return static_cast<float>(stats.activeWorkers) / stats.totalWorkers;
    }

    void scaleUp() {
        // Implement scale up logic
        size_t currentSize = poolManager_.getStats().totalWorkers;
        size_t newSize = currentSize + (currentSize / 2);  // Increase by 50%
        poolManager_.adjustPoolSize(newSize);
    }

    void scaleDown() {
        // Implement scale down logic
        size_t currentSize = poolManager_.getStats().totalWorkers;
        size_t newSize = std::max(size_t(1), currentSize - (currentSize / 4));  // Decrease by 25%
        poolManager_.adjustPoolSize(newSize);
    }

    WorkerPoolManager& poolManager_;
    std::thread monitorThread_;
    std::atomic<bool> isRunning_;
    std::chrono::seconds scaleCheckInterval_;
    float upscaleThreshold_ = 0.75f;
    float downscaleThreshold_ = 0.25f;
};

#endif // SCALING_MANAGER_HPP
