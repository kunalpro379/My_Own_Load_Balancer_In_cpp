#ifndef WORKER_POOL_MANAGER_HPP
#define WORKER_POOL_MANAGER_HPP

#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include "WorkerQueue.h"
#include "LoadBalancer.h"

class WorkerPoolManager
{
public:
     WorkerPoolManager(size_t initialPoolSize = std::thread::hardware_concurrency())
         : isRunning_(true)
     {
          // Initialize worker pool
          for (size_t i = 0; i < initialPoolSize; ++i)
          {
               availableWorkers_.push(std::make_shared<Worker>(i));
          }

          // Start the management thread
          managementThread_ = std::thread(&WorkerPoolManager::manage, this);
     }

     ~WorkerPoolManager()
     {
          shutdown();
     }

     // Get an available worker
     std::shared_ptr<Worker> getWorker()
     {
          return availableWorkers_.pop();
     }

     // Return a worker to the pool
     void returnWorker(std::shared_ptr<Worker> worker)
     {
          if (worker)
          {
               availableWorkers_.push(worker);
          }
     }

     // Shutdown the pool manager
     void shutdown()
     {
          if (isRunning_)
          {
               isRunning_ = false;
               if (managementThread_.joinable())
               {
                    managementThread_.join();
               }
          }
     }

     // Get current pool statistics
     struct PoolStats
     {
          size_t totalWorkers;
          size_t availableWorkers;
          size_t activeWorkers;
     };

     PoolStats getStats() const
     {
          size_t available = availableWorkers_.size();
          return PoolStats{
              .totalWorkers = totalWorkers_,
              .availableWorkers = available,
              .activeWorkers = totalWorkers_ - available};
     }

private:
     void manage()
     {
          while (isRunning_)
          {
               // Monitor worker health and handle any necessary cleanup
               std::this_thread::sleep_for(std::chrono::seconds(1));

               // Check for stalled or crashed workers
               checkWorkerHealth();

               // Scale worker pool if needed
               adjustPoolSize();
          }
     }

     void checkWorkerHealth()
     {
          // Implementation to check worker health
          // Could involve checking last activity time, memory usage, etc.
     }

     void adjustPoolSize()
     {
          // Implementation to scale pool size based on demand
          // Could involve adding or removing workers based on usage patterns
     }

private:
     WorkerQueue availableWorkers_;
     std::thread managementThread_;
     std::atomic<bool> isRunning_;
     std::atomic<size_t> totalWorkers_{0};
};

#endif // WORKER_POOL_MANAGER_HPP
