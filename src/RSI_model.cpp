#include "../include/RSI_model.hpp"
#include "../include/csv_loader.hpp"
#include <iostream>


double averageInitialGain(const std::vector<csv_loader::PriceData>& data, const int period){
    double sum = 0.0;

    for(int i=1; i< period; i++){
        if(data[i].close - data[i-1].close > 0){
            sum += data[i].close - data[i-1].close;
        }
    }

    return (sum/period);
}

double averageInitialLoss(const std::vector<csv_loader::PriceData>& data, const int period){
    double sum = 0.0;

    for(int i=1; i< period; i++){
        if(data[i].close - data[i-1].close < 0){
            sum +=  data[i-1].close - data[i].close;
        }
    }

    return (sum/period);
}


double relativeStrength(const std::vector<csv_loader::PriceData>& data, const int period){
    double avg_gain = averageInitialGain(data, period);
    double avg_loss = averageInitialLoss(data, period);
    if (avg_loss == 0) {
        return 100; 
    }
    return avg_gain / avg_loss; 
}

std::vector<double> calculateRSI(const std::vector<csv_loader::PriceData>& data, const int period) {
    double avg_gain = averageInitialGain(data, period);
    double avg_loss = averageInitialLoss(data, period);
    
    std::vector<double> rsiValues;  
    
    // initial RSI (first cycle)
    double relative_strength = avg_gain / avg_loss;
    double rsi = 100.0 - (100.0 / (1 + relative_strength));
    rsiValues.push_back(rsi); 

    // start smoothing process for next periods ( cycles)
    for (size_t i = period; i < data.size(); i++) {
        double change = data[i].close - data[i - 1].close;
        double gain = (change > 0) ? change : 0;
        double loss = (change < 0) ? -change : 0;
        
        // wilders smoothing method
        avg_gain = ((avg_gain * (period - 1)) + gain) / period;
        avg_loss = ((avg_loss * (period - 1)) + loss) / period;

        //std::cout << "Initial avg_gain: " << avg_gain << " avg_loss: " << avg_loss << std::endl;
        
        relative_strength = avg_gain / avg_loss;
        rsi = 100 - (100 / (1 + relative_strength));

        rsiValues.push_back(rsi);
    }

    return rsiValues;
}

