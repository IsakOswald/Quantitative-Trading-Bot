#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Candle.h"
#include "Engine.h"

// "Date","Price","Open","High","Low","Vol.","Change %"

std::vector<Candle> readCsv(std::string& file_name);

int main()
{
    std::string fn = "SPY-HISTORY.csv";

    Engine eng = Engine("Test Engine", readCsv(fn));
    eng.orderBlock();

    return 0;
}

std::vector<Candle> readCsv(std::string& file_name)
{
    // Create a vector to hold our extracted data.
    std::vector<Candle> candles;

    // Create a file stream to read data from (.csv)
    std::fstream file(file_name);

    // Check if file open...
    if (!(file.is_open()))
    {
        std::cerr << "File not found\n";
        exit(1);
    }

    // Create a buffer to hold the read contents of the .csv.
    std::string buffer;

    // Continiously read the .csv
    while (std::getline(file, buffer))
    {
        // Turn the buffer into a stream itself, so we can read up-to a delimiter.
        std::stringstream stream(buffer);
        // Create a candle
        Candle c;

        // temp string for converting types.
        std::string temp;

        std::getline(stream, temp, ',');
        temp = temp.substr(1, (temp.size() - 2));
        c.date = temp;

        std::getline(stream, temp, ',');
        temp = temp.substr(1, (temp.size() - 2));
        c.close_price = std::stod(temp);

        // Add the candle to vector of candle data.
        candles.push_back(c);
    }

    return candles;
}
