#include <vector>
#include "../include/csv_loader.hpp"
#include "../include/strategy_simulation.hpp"

namespace strategy{
    double simulateRSIStrategy(const std::vector<csv_loader::PriceData>& price_data, const std::vector<double>& rsi_values, const int rsiPeriod, double startingCash, const double bottomThreshold, const double topThreshold, std::vector<TradeLog>& logs, bool printLogs){
    
    }
}
