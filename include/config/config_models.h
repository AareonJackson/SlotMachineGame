#pragma once
#include <string>
#include <nlohmann/json.hpp>

// 1. Define the standard C++ struct
struct GameConfig {
    std::string gameTitle;
    int windowWidth;
    int windowHeight;
    // ... add whatever is in the game_config.json
};

struct ReelsConfig {
    int num_reels;
    int num_visible_rows;
    std::vector<std::vector<std::string>> reel_strips;
};

struct PaylinesConfig {
    // each payline is a vector of integers, representing row indices per reel
    std::vector<std::vector<int>> paylines;
};

struct PayoutRule {
    std::string symbol;
    int match_count;
    int multiplier; // the multiplier applied to the player's bet
};

struct PaytableConfig {
    std::vector<PayoutRule> payouts;
};

// struct FeaturesConfig {};

/*

2. Main Point: Use the macro to tell the library how to map JSON keys to struct variables

Details: These macros can be used to simplify the serialization/deserialization of types if you want to use a JSON
        object as serialization and want to use the member variable names as object keys in that object. The macro is
        to be defined outside the class/struct to create code for, but inside its namespace. Unlike
        NLOHMANN_DEFINE_TYPE_INTRUSIVE, it cannot access private members. The first parameter is the name of the
        class/struct, and all remaining parameters name the members.

Will use (at) during deserialization and will throw out_of_range.403 if a key is missing in the JSON object.
Will use (value) during deserialization and fall back to the default value for the respective type of the member
variable if a key in the JSON object is missing. The generated from_json() function default constructs an object and
uses its values as the defaults when calling the value function. Only defines the serialization. Useful in cases when
the type does not have a default constructor and only serialization is required.

*/

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GameConfig, gameTitle, windowWidth, windowHeight)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ReelsConfig, num_reels, num_visible_rows, reel_strips)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PaylinesConfig, paylines)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PayoutRule, symbol, match_count, multiplier)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PaytableConfig, payouts)
// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FeaturesConfig, )


