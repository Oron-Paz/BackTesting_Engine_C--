#include <vector>
#include "../include/csv_loader.hpp"
#include "../include/strategy_simulation.hpp"

double cash = 10000.0;
const int RSI_PERIOD = 14;

double simulateRSIStrategy(const std::vector<csv_loader::PriceData>& data,const std::vector<double>& rsi,int rsiPeriod,double startingCash,double bottomThreshold,double topThreshold,std::vector<TradeLog>& logs){
    double cash = startingCash;
    int sharesHeld = 0;

    for (size_t i = rsiPeriod; i < data.size(); ++i) {
        double stockPrice = data[i].close;
        TradeLog log;
        log.date = data[i].date;
        log.price = stockPrice;

        if (rsi[i] < bottomThreshold && cash >= stockPrice) {
            // BUY
            int sharesToBuy = cash / stockPrice;
            double cost = sharesToBuy * stockPrice;

            cash -= cost;
            sharesHeld += sharesToBuy;

            log.action = "BUY";
            log.shares = sharesToBuy;
        } else if (rsi[i] > topThreshold && sharesHeld > 0) {
            // SELL
            double proceeds = sharesHeld * stockPrice;

            cash += proceeds;

            log.action = "SELL";
            log.shares = sharesHeld;
            sharesHeld = 0;
        } else {
            // HOLD
            log.action = "HOLD";
            log.shares = 0;
        }

        logs.push_back(log);
    }

    return cash + (sharesHeld * data.back().close);
}