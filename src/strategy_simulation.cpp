#include <vector>
#include "../include/csv_loader.hpp"
#include "../include/strategy_simulation.hpp"

double cash = 10000.0;
const int RSI_PERIOD = 14;

double simulateRSIStrategy( const std::vector<csv_loader::PriceData>& data, const std::vector<double>& rsi, int rsiPeriod, double startingCash, double bottomThreshold, double topThreshold, std::vector<TradeLog>& logs){
    int current_period = RSI_PERIOD; //we want to start when we already have RSI values.
    for(size_t current_period = RSI_PERIOD; current_period < data.size(); current_period++) {
        TradeLog currentDateLog;
        double stockPrice = data[current_period].close;

        currentDateLog.date = data[current_period].date;
        currentDateLog.price = data[current_period].close;

        if (rsi[current_period] < bottomThreshold){
            int sharesAffordable = cash / stockPrice;
            int cashLeftover = cash - stockPrice * sharesAffordable;
            
            currentDateLog.action = "BUY";
            if(current_period > 0 ){

            }else{
                
            }
            currentDateLog.shares =;
            
            
        }
    }

    return 0;
}