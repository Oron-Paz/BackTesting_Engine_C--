#include "../include/csv_loader.hpp"
#include "../include/RSI_model.hpp"
#include "../include/strategy_simulation.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main(){
    std::vector<csv_loader::PriceData> data = csv_loader::getData("../data/historical.csv");
    int period = 14;

    std::reverse(data.begin(), data.end());

    std::vector<double> rsi_values = calculateRSI(data, period);
    std::vector<strategy::TradeLog> trade_logs;
    
    bool printLogs = true;

    double simulationRSIResult = strategy::simulateRSIStrategy(data, rsi_values, 14, 100000, 100, 100, trade_logs, printLogs);
    
    
    std::cout << simulationRSIResult << " <- This is how much money we made using our strategy \n";

    return 0;
}
