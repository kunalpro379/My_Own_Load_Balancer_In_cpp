#ifndef WORKER_QUEUE_HPP
#define WORKER_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include "LoadBalancer.h"

class WorkerQueue {
public:
    WorkerQueue() = default;

    // Add a worker to the queue
    void push(std::shared_ptr<Worker> worker) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(worker);
        condition_.notify_one();
    }

    // Get a worker from the queue, will block if queue is empty
    std::shared_ptr<Worker> pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty()) {
            condition_.wait(lock);
        }
        auto worker = queue_.front();
        queue_.pop();
        return worker;
    }

    // Try to get a worker without blocking
    bool tryPop(std::shared_ptr<Worker>& worker) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return false;
        }
        worker = queue_.front();
        queue_.pop();
        return true;
    }

    size_t size() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return queue_.size();
    }

private:
    std::queue<std::shared_ptr<Worker>> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
};

#endif // WORKER_QUEUE_HPP
