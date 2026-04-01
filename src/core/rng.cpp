#include "core/rng.h"

std::vector<int> RNG::generateStops(const std::vector<int>& reelLengths) {
    std::vector<int> stops;
    stops.reserve(reelLengths.size());

    for (int length : reelLengths) {
        if (length <= 0) {
            stops.push_back(0);
        } else {
            // Feed the cryptographically secure random_device directly into the distribution
            std::uniform_int_distribution<int> distribution(0, length - 1);
            stops.push_back(distribution(m_cryptoRng));
        }
    }
    return stops;
}

int RNG::getRandomInt(int min, int max) {
    if (min > max) {
        std::swap(min, max);
    }
    std::uniform_int_distribution<int> distribution(min, max);
    // directly poll the OS entropy pool
    return distribution(m_cryptoRng);
}