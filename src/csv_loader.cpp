#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "../include/csv_loader.hpp"

namespace csv_loader{

    std::string cleanField(std::string field) {
        if (!field.empty() && field.front() == '"' && field.back() == '"') {
            field = field.substr(1, field.length() - 2);
        }
        field.erase(std::remove(field.begin(), field.end(), ','), field.end());
        return field;
    }

    std::vector<PriceData> getData(const std::string& filename) {
        std::vector<PriceData> data;
        std::ifstream file(filename);
        std::string line;

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::getline(file, line); //skips the header line

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string field;
            std::vector<std::string> fields;

            while (std::getline(ss, field, ',')) {
                if (field.front() == '"') {
                    std::string temp;
                    while (field.back() != '"' && std::getline(ss, temp, ',')) {
                        field += "," + temp;
                    }
                }
                fields.push_back(cleanField(field));
            }

            if (fields.size() < 6) continue;

            PriceData row;
            row.date  = fields[0];
            row.open  = std::stod(fields[1]);
            row.high  = std::stod(fields[2]);
            row.low   = std::stod(fields[3]);
            row.close = std::stod(fields[4]);
            row.volume = std::stol(fields[5]);

            data.push_back(row);
        }

        return data;
    }

}