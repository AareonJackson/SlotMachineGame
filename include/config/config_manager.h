#pragma once
#include "config_models.h"

class ConfigManager {
public:
    // Delete copy/move constructors and assignment operators so it can't be cloned
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    // The single point of access
    static ConfigManager& getInstance() {
        static ConfigManager instance; // Guaranteed to be destroyed, instantiated on first use
        return instance;
    }

    // Method to trigger loading all files
    bool loadAllConfigs(const std::string& configDirectory);

    // Getters
    const GameConfig& getGameConfig() const { return gameConfig; }
    const ReelsConfig& getReelsConfig() const { return reelsConfig; }
    const PaylinesConfig& getPaylinesConfig() const { return paylinesConfig; }
    const PaytableConfig& getPaytableConfig() const { return paytableConfig; }
    // const FeaturesConfig& getFeaturesConfig() const { return featuresConfig; }


private:
    // Private constructor so nobody else can instantiate it
    ConfigManager() = default;
    ~ConfigManager() = default;

    // The actual stored data
    GameConfig gameConfig;
    ReelsConfig reelsConfig;
    PaylinesConfig paylinesConfig;
    PaytableConfig paytableConfig;
    // FeaturesConfig featuresConfig;
};