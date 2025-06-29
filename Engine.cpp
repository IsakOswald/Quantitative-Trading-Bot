#include <iostream>
#include "Engine.h"

Engine::Engine(double _b, float _risk_p, float _reward_p) : _balance(_b), _risk_percentage(_risk_p), _reward_percentage(_reward_p)
{
    _strategy = nullptr;
    _data = {};
}

Engine::~Engine() { _strategy = nullptr; }

void Engine::select_data_set(std::vector<Candle> data_set) { _data = std::move(data_set); }
void Engine::print_candle_data_range() { std::cout << "Data range -> " << _data[0].date << " - " << _data.back().date << '\n'; }

double Engine::calculate_risk_price(Candle candle) {}
double Engine::calculate_reward_price(Candle candle) {}

void Engine::trade_OB()
{
    int valid_OBs_found = 0;

    // Loop throught all of the candles.
    for (int i = 0; i < _data.size() - 15; i++)
    {
        // For each candle, record their closing price.
        float candidate_OB = _data[i].closing_price;
        // A variable to determine if we have found a better price.
        bool found_better = false;

        // From the current candle, loop throgh 14 more candles.
        for (int j = i + 1; j < i + 15; j++)
        {
            // Check if any of the candles are LOWER than the origional lowest price.
            if (_data[j].closing_price <= candidate_OB)
            {
                found_better = true;
                break;
            }
        }

        // If there was a better price in 15 candles, do nothing and continue to the next candle.
        if (found_better == true)
        {
            continue;
        }

        // If a valid OB was found, update the counter and print out the price it was found.
        valid_OBs_found++;
        std::cout << "Orderblock found @ " << _data[i].closing_price << '\n';

        // Here we are actually doing to execute a trade and add it to the engines "trades". We can have multiple trades at once.
    }

    // Print out the total ammount of orderblocks found during the anaysis.
    std::cout << "OB's found -> " << valid_OBs_found << "\n";
}
