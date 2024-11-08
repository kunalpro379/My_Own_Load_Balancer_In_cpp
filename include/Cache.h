#ifndef CACHE_CHECKER_HPP
#define CACHE_CHECKER_HPP

#include <unordered_map>
#include <string>

class CacheChecker
{
public:
     // Constructor
     CacheChecker() {}

     // Check if the cache contains the requested key
     bool checkCache(const std::string &key, std::string &cachedResponse);

     // Add or update the cache
     void updateCache(const std::string &key, const std::string &response);

     // Clear cache for a specific key
     void clearCache(const std::string &key);

private:
     std::unordered_map<std::string, std::string> cache; // Cache storage
};

#endif // CACHE_CHECKER_HPP
