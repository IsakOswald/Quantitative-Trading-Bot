#include "parseCandles.h"
#include "Engine.h"

// #include <iostream>

int main()
{
    std::string fn = "SPY-HISTORY.csv";

    Engine eng(1000, 1, 2);

    eng.select_data_set(parseCandles(fn));

    eng.print_candle_data_range();

    eng.trade_OB();

    return 0;
}
