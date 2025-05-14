#include <vector>
#include <iostream>
#include "../include/csv_loader.hpp"
#include "../include/strategy_simulation.hpp"

namespace strategy{
    std::string to_string_action(TradeAction action) {
        switch (action) {
            case TradeAction::BUY: return "BUY";
            case TradeAction::SELL: return "SELL";
            case TradeAction::HOLD: return "HOLD";
        }
        return "UNKNOWN";
    }

    void printTradeLog(TradeLog& log){
        std::cout << log.date << " | " << to_string_action(log.action) << " | Cash: " << log.current_cash
              << " -> " << log.cash_after_action << ", Shares: " << log.shares_owned_before_action
              << " -> " << log.shares_owned_after_action << ", Price: " << log.current_price_of_share.close << "\n";
    }

    double simulateRSIStrategy(const std::vector<csv_loader::PriceData>& price_data, const std::vector<double>& rsi_values, const int rsiPeriod, double startingCash, const double bottomThreshold, const double topThreshold, std::vector<TradeLog>& logs, bool printLogs){
        int shares = 0;
        double cash = startingCash;

        for (size_t i = rsiPeriod; i < price_data.size(); ++i) {
            const auto& d = price_data[i];
            double price = d.close;

            TradeLog log;
            log.date = d.date;
            log.current_cash = cash;
            log.current_price_of_share = d;
            log.shares_owned_before_action = shares;
            log.shares_bought = 0;
            log.shares_sold = 0;
            log.action = TradeAction::HOLD;
            log.cash_after_action = cash;
            log.shares_owned_after_action = shares;

            if (rsi_values[i] < bottomThreshold && cash >= price) {
                int buyable = static_cast<int>(cash / price);
                double cost = buyable * price;
                log.action = TradeAction::BUY;
                log.shares_bought = buyable;
                shares += buyable;
                cash -= cost;
                log.cash_after_action = cash;
                log.shares_owned_after_action = shares;
            } else if (rsi_values[i] > topThreshold && shares > 0) {
                double revenue = shares * price;
                log.action = TradeAction::SELL;
                log.shares_sold = shares;
                shares = 0;
                cash += revenue;
                log.cash_after_action = cash;
                log.shares_owned_after_action = shares;
            }

            logs.push_back(log);
            if(printLogs){
                printTradeLog(log);
            }
        }
        return cash + shares * price_data.back().close;
    }


    double simulateRSIStrategy(const std::vector<csv_loader::PriceData>& price_data, const std::vector<double>& rsi_values, const int rsiPeriod, double startingCash, const double bottomThreshold, const double topThreshold, std::vector<TradeLog>& logs, bool printLogs){
        int shares = 0;
        double cash = startingCash;

        for (size_t i = rsiPeriod; i < price_data.size(); ++i) {
            const auto& d = price_data[i];
            double price = d.close;

            TradeLog log;
            log.date = d.date;
            log.current_cash = cash;
            log.current_price_of_share = d;
            log.shares_owned_before_action = shares;
            log.shares_bought = 0;
            log.shares_sold = 0;
            log.action = TradeAction::HOLD;
            log.cash_after_action = cash;
            log.shares_owned_after_action = shares;

            if (rsi_values[i] < bottomThreshold && cash >= price) {
                int buyable = static_cast<int>(cash / price);
                double cost = buyable * price;
                log.action = TradeAction::BUY;
                log.shares_bought = buyable;
                shares += buyable;
                cash -= cost;
                log.cash_after_action = cash;
                log.shares_owned_after_action = shares;
            } else if (rsi_values[i] > topThreshold && shares > 0) {
                double revenue = shares * price;
                log.action = TradeAction::SELL;
                log.shares_sold = shares;
                shares = 0;
                cash += revenue;
                log.cash_after_action = cash;
                log.shares_owned_after_action = shares;
            }

            logs.push_back(log);
            if(printLogs){
                printTradeLog(log);
            }
        }
        return cash + shares * price_data.back().close;
    }

}
