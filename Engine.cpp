#include <iostream>
#include "Engine.h"

Engine::Engine(std::string n, std::vector<Candle> c) : name(n), candles(c) { current_error = nullptr; }

void Engine::orderBlock()
{
    for (int i = 0; i < candles.size() - 15; i++)
    {
        // Grab the current candle lowest price.
        float closing_price = candles[i].close_price;

        bool found_lower = false;

        // From the CURRENT candle, loop through the next 15 candles.
        for (int j = i + 1; j < i + 15; j++)
        {
            // Check if any of the next 15 candles have broken the "root" candles price.
            if (candles[j].close_price < closing_price)
            {
                found_lower = true;
                break;
            }
        }

        // If one of the next 15 candles managed to find a lower price....
        if (found_lower == true)
        {
            std::cout << "No valid OB formed\n";
            // Continue the loop and do nothing
            continue;
        }

        // If there was NO lower candle in the next 15 candles....
        else
        {
            // Mark the order block as a potential buy.
            // Buy in for 1% of account balance with a 2:1 Risk : Reward. (1000 balance risk 10$ (SL) 20$ profit)
            std::cout << "Potential buy area found\n";
        }
    }
}
