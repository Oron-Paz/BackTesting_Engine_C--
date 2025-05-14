#include <string>
#include <vector>
#include "csv_loader.hpp"

namespace strategy{
    enum class TradeAction { BUY, SELL, HOLD };

    struct TradeLog{
        std::string date;
        TradeAction action;
        double current_cash;
        double cash_after_action;
        csv_loader::PriceData current_price_of_share;
        int shares_owned_before_action;
        int shares_bought;
        int shares_sold;
        int shares_owned_after_action;
        double portfolio_value_after_action;
    };
    
    double simulateRSIStrategy(const std::vector<csv_loader::PriceData>& data, 
                               const std::vector<double>& rsi, 
                               int rsiPeriod, 
                               double startingCash, 
                               double bottomThreshold,
                               double topThreshold,
                               std::vector<TradeLog>& logs,
                               bool printLogs
                            );
}