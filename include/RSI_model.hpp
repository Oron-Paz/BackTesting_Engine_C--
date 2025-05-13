#pragma once
#include <vector>
#include "csv_loader.hpp"

double averageInitialGain(const std::vector<csv_loader::PriceData>& data);
double averageInitialLoss(const std::vector<csv_loader::PriceData>& data, const int period);
double relativeStrength(const std::vector<csv_loader::PriceData>& data, const int period);
std::vector<double> calculateRSI(const std::vector<csv_loader::PriceData>& data, const int period);



