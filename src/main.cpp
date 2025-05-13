#include "../include/csv_loader.hpp"
#include "../include/RSI_model.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main(){
    std::vector<csv_loader::PriceData> data = csv_loader::getData("../data/historical.csv");
    int period = 14;

    std::vector<double> rsi_values = calculateRSI(data, period);

    for(int i=0;  i<rsi_values.size(); i++){
        std::cout << rsi_values[i] << "\n";
    }
    return 0;
}
