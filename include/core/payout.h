#pragma once
#include "config/config_manager.h"
#include <vector>
#include <string>

struct WinLine {
    int payline_index;
    std::string symbol;
    int match_count;
    double win_amount;
};

class PayoutCalculator {
public:
    PayoutCalculator() = default;

    /*
     * Calculate the total payout for a spin based on reel results.
     *
     * @param grid a 2D vector [reel][row] representing the visible symbols after a spin.
     * @param betAmount The amount the player bet on this spin.
     * @return A vector of WinLine objects describing each winning payLine.
     */
    std::vector<WinLine> calculateWin(const std::vector<std::vector<std::string>>& grid, double betAmount) const;

private:
    double getMultiplierForMatch(const std::string& symbol, int matchCount) const;
};