#include "core/payout.h"

std::vector<WinLine> PayoutCalculator::calculateWin(const std::vector<std::vector<std::string>>& grid, double betAmount) const {
    std::vector<WinLine> wins;

    // Config via the singleton configManager
    const auto& paylinesConfig = ConfigManager::getInstance().getPaylinesConfig();
    const auto& paytableConfig = ConfigManager::getInstance().getPaytableConfig();

    // Safety check
    if (grid.empty() || paylinesConfig.paylines.empty() || paytableConfig.payouts.empty()) return wins;

    int paylineIndex = 0;
    for (const auto& line : paylinesConfig.paylines) {
        // A payline is a list of row indices for each reel
        if (line.size() != grid.size()) continue;

        std::string firstSymbol = grid[0][line[0]];
        int matchCount = 1;

        // Count consecutive matching symbols from left to right
        for (size_t reelIdx = 1; reelIdx < grid.size(); ++reelIdx) {
            int rowIdx = line[reelIdx];
            if (grid[reelIdx][rowIdx] == firstSymbol) {
                matchCount++;
            } else {
                break; // break if the match is broken
            }
        }

        // Check if the match -> payout
        double multiplier = getMultiplierForMatch(firstSymbol, matchCount);
        if (multiplier > 0) {
            WinLine win;
            win.payline_index = paylineIndex;
            win.symbol = firstSymbol;
            win.match_count = matchCount;
            win.win_amount = betAmount * multiplier;
            wins.push_back(win);
        }
        paylineIndex++;
    }
    return wins;
}

double PayoutCalculator::getMultiplierForMatch(const std::string& symbol, int matchCount) const {
    const auto& payouts = ConfigManager::getInstance().getPaytableConfig().payouts;

    for (const auto& rule : payouts) {
        if (rule.symbol == symbol && rule.match_count == matchCount) {
            return rule.multiplier;
        }
    }
    return 0.0; // No payout found
}
