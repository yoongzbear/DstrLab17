// read the csv file
// https://cppbyexample.com/parse_csv.html - use vector, cannot dy

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "arrayStorage.hpp"

const int test_size = 10; // for testing to see if array works

// parse transaction csv to be more neat
Transaction parseTransaction(const std::string &line)
{
    std::stringstream stream(line);
    std::string item; // temporary placeholder for each item in a row
    Transaction t;

    std::getline(stream, t.transaction_id, ',');
    std::getline(stream, t.timestamp, ',');
    std::getline(stream, t.sender_account, ',');
    std::getline(stream, t.receiver_account, ',');
    // double
    std::getline(stream, item, ',');
    t.amount = std::stod(item);

    std::getline(stream, t.transaction_type, ',');
    std::getline(stream, t.merchant_category, ',');
    std::getline(stream, t.location, ',');
    std::getline(stream, t.device_used, ',');
    // boolean
    std::getline(stream, item, ',');
    t.is_fraud = (item == "TRUE");

    std::getline(stream, t.fraud_type, ',');
    std::getline(stream, t.time_since_last_transaction, ',');
    // double
    std::getline(stream, item, ',');
    t.spending_deviation_score = std::stod(item);

    // int
    std::getline(stream, item, ',');
    t.velocity_score = std::stoi(item);

    // double
    std::getline(stream, item, ',');
    t.geo_anomaly_score = std::stod(item);

    std::getline(stream, t.payment_channel, ',');
    std::getline(stream, t.ip_address, ',');
    std::getline(stream, t.device_hash, ',');

    return t;
}

int main()
{
    std::string filename{"financial_fraud_detection_dataset.csv"}; // csv file
    std::ifstream input{filename};

    // cannot read file
    if (!input.is_open())
    {
        std::cerr << "Couldn't read file: " << filename << "\n";
        return 1;
    }

    ArrayStorage arrayStorage;

    std::string line;
    std::getline(input, line); // skip header

    Transaction transaction[test_size];
    int count = 0;

    while (std::getline(input, line)) {
        Transaction t = parseTransaction(line);
        arrayStorage.addTransaction(t);

        if (++count % 100000 == 0) {
            std::cout << count << " rows loaded...\n";
        }
    }

    std::cout << "Total transactions stored: " << arrayStorage.getSize() << "\n";

    // print out result to see if it works
    for (int i = 0; i < std::min(10, arrayStorage.getSize()); ++i) {
        arrayStorage.getTransaction(i).print();
    }
}