#ifndef WORK_STEALER_HPP
#define WORK_STEALER_HPP

#include <deque>
#include <mutex>
#include <condition_variable>
#include "WorkerQueue.h"

class WorkStealer {
public:
    WorkStealer(WorkerQueue& queue) : queue_(queue) {}

    bool stealWork(std::shared_ptr<Worker>& worker) {
        // Try to steal work from other queues when a worker is idle
        return queue_.tryPop(worker);
    }

    void redistributeWork() {
        // Implement work redistribution logic
        // This could involve moving tasks between queues to balance load
        auto stats = queue_.getStats();
        if (stats.queueSize > stats.optimalQueueSize) {
            balanceQueues();
        }
    }

private:
    void balanceQueues() {
        // Implementation of queue balancing logic
        // Could move tasks between queues to achieve better distribution
    }

    struct QueueStats {
        size_t queueSize;
        size_t optimalQueueSize;
    };

    WorkerQueue& queue_;
};

#endif // WORK_STEALER_HPP
