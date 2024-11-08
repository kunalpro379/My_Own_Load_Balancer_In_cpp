#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

class Config {
public:
    Config(const std::string& configPath = "config.json") {
        loadConfig(configPath);
    }

    template<typename T>
    T getValue(const std::string& key, const T& defaultValue = T()) const {
        auto it = config_.find(key);
        if (it != config_.end()) {
            return convertValue<T>(it->second);
        }
        return defaultValue;
    }

    void setValue(const std::string& key, const std::string& value) {
        config_[key] = value;
    }

    bool hasKey(const std::string& key) const {
        return config_.find(key) != config_.end();
    }

private:
    void loadConfig(const std::string& path);
    
    template<typename T>
    T convertValue(const std::string& value) const;

    std::map<std::string, std::string> config_;
};

#endif
