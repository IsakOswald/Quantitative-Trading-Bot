#include <fstream>
#include <sstream>
#include "Candle.h"

std::vector<Candle> parseCandles(std::string& fn)
{
    // All of the candles in the .csv will be here
    std::vector<Candle> candles;

    // Open the file during initilization.
    std::fstream file(fn);

    if (!(file.is_open()))
    {
        // Return empty vector (no candles)
        return candles;
    }

    // A buffer to read lines into from the .csv.
    std::string buffer;

    // Skip the first line of the .csv because of the BOM (Byte Order Mark). On the byte level, the first character of the fist line is hex (BOM) not
    // our date string.
    std::getline(file, buffer);

    // Continiously read each line
    while (std::getline(file, buffer))
    {
        // Create a string stream so we can manipulate the string like a file.
        std::stringstream sstream(buffer);

        // Create a buffer to hold the output from the string stream.
        std::string final_buf;

        // Create a new candle to store the data in.
        Candle c;

        // Read in the contents from the string stream untill the first ',' character and store it in the final_buf buffer. This will exract the date.
        // So the first peice of text untill the ',' will be the candle date.
        std::getline(sstream, final_buf, ',');

        // Since the .csv is weird, the actual date string is "XX/XX/XXXX" (with the quotes) so we need to remove them.
        // final_buf.size() will give us eg 10, meaning index 0-9 so .size() - 1 is the last char (the "), however we want to cut include one less so -2.
        c.date = final_buf.substr(1, final_buf.size() - 2);  // This will turn ""XX/XX/XXXX"" to just "XX/XX/XXXX".

        std::getline(sstream, final_buf, ',');
        c.closing_price = std::stof(final_buf.substr(1, final_buf.size() - 2));

        // Now that we have the candle data in the candle struct, appending it to the candles vector.
        candles.push_back(c);
    }

    std::vector<Candle> candles_rev;

    for (int i = candles.size() - 1; i >= 0; i--)
    {
        candles_rev.push_back(candles[i]);
    }

    // Now return the fully populated vector of candle data.
    return candles_rev;
}
