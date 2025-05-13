#include <string>
#include <vector>
#include "csv_loader.hpp"


struct TradeLog{
    std::string date;
    std::string action;
    int shares;
    double price;
};

double simulateRSIStrategy(const std::vector<csv_loader::PriceData>& data, 
                           const std::vector<double>& rsi, 
                           int rsiPeriod, 
                           double startingCash, 
                           double bottomThreshold,
                           double topThreshold,
                           std::vector<TradeLog>& logs);