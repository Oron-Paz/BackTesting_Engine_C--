#pragma once
#include <vector>
#include <string>

namespace csv_loader {
    struct PriceData {
        std::string date;
        double open;
        double high;
        double low;
        double close;
        long volume;
    };

    std::vector<PriceData> getData(const std::string& filename);
}
