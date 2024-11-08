#ifndef LOAD_BALANCER_HPP
#define LOAD_BALANCER_HPP

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>

class Worker
{
public:
     Worker(int id) : id(id), isBusy(false) {}

     // Simulate work handling
     void handleRequest()
     {
          isBusy = true;
          // Simulated work; in a real implementation, replace this with actual logic
          std::cout << "Worker " << id << " is handling a request.\n";
          isBusy = false; // Reset state after request (for demonstration)
     }

     bool isWorkerBusy() const { return isBusy; }
     int getId() const { return id; }

private:
     int id;
     bool isBusy;
};

class LoadBalancer
{
public:
     LoadBalancer(int initialWorkerCount, int maxWorkerCount)
         : maxWorkerCount(maxWorkerCount)
     {
          // Initialize workers
          for (int i = 0; i < initialWorkerCount; ++i)
          {
               workers.emplace_back(std::make_shared<Worker>(i));
          }
     }

     // Main load balancing logic
     void balanceLoad()
     {
          if (needScaling())
          {
               scaleWorkers();
          }
          else
          {
               selectWorker();
          }
     }

private:
     std::vector<std::shared_ptr<Worker>> workers;
     const int maxWorkerCount;
     const int minWorkerCount = 1; // Minimum number of workers

     bool needScaling()
     {
          // Check if more than 75% of workers are busy (simple logic)
          int busyCount = std::count_if(workers.begin(), workers.end(),
                                        [](const std::shared_ptr<Worker> &worker)
                                        { return worker->isWorkerBusy(); });

          float busyRatio = static_cast<float>(busyCount) / workers.size();
          return busyRatio > 0.75 || busyRatio < 0.25; // Example: Scale up if >75% busy, scale down if <25%
     }

     void scaleWorkers()
     {
          int busyCount = std::count_if(workers.begin(), workers.end(),
                                        [](const std::shared_ptr<Worker> &worker)
                                        { return worker->isWorkerBusy(); });

          if (static_cast<float>(busyCount) / workers.size() > 0.75)
          {
               // Scale up if not at max capacity
               if (workers.size() < maxWorkerCount)
               {
                    workers.emplace_back(std::make_shared<Worker>(workers.size()));
                    std::cout << "Scaled up: New worker added. Total workers: " << workers.size() << "\n";
               }
          }
          else if (static_cast<float>(busyCount) / workers.size() < 0.25)
          {
               // Scale down if above minimum capacity
               if (workers.size() > minWorkerCount)
               {
                    workers.pop_back(); // Remove the last worker
                    std::cout << "Scaled down: Worker removed. Total workers: " << workers.size() << "\n";
               }
          }
     }

     void selectWorker()
     {
          // Select the first available worker
          for (const auto &worker : workers)
          {
               if (!worker->isWorkerBusy())
               {
                    worker->handleRequest();
                    return;
               }
          }
          std::cout << "All workers are busy. Please try again later.\n";
     }
};

#endif // LOAD_BALANCER_HPP
