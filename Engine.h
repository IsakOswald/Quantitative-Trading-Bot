#pragma once

#include <string>
#include <vector>
#include "Candle.h"

typedef void (*errorFP)();

struct Engine
{
    std::string name;
    std::vector<Candle> candles;
    errorFP current_error;

    Engine(std::string n, std::vector<Candle> c);

    void orderBlock();
};
