#pragma once

#include <vector>
#include "Candle.h"
#include "Trade.h"

class Engine
{
   private:
    // This is the candle data.
    //   std::vector<Candle> _data;

    // The strategy the user selects.
    void (*_strategy)();

    // The accounts balance.
    double _balance;
    // The accounts risk per trade (defualt at 1%);
    float _risk_percentage;
    // The reward per trande (default at 2%)
    float _reward_percentage;

    // Current Trades.
    std::vector<Trade> trades;

   public:
    // Constructor and destructor.
    std::vector<Candle> _data;
    Engine(double _b, float _risk_p, float _reward_p);
    ~Engine();

    void select_data_set(std::vector<Candle> data_set);
    void print_candle_data_range();

    // Calculate and return the price of the stock when we will get stopped out accounting to our SL (risk_percentage) relative to our balance (one share).
    double calculate_risk_price(Candle candle);
    // Same thing but for out reward, check what price we will cash out at (one share).
    double calculate_reward_price(Candle candle);

    // Stategys
    void trade_OB();
};
