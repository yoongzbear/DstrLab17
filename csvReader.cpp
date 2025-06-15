// read the csv file
// https://cppbyexample.com/parse_csv.html - use vector, cannot dy

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "arrayStorage.hpp"
#include <algorithm>

const int test_size = 10; // for testing to see if array works

// parse transaction csv to be more neat
Transaction parseTransaction(const std::string &line)
{
    std::stringstream stream(line);
    std::string item;
    Transaction t;

    std::getline(stream, t.transaction_id, ',');
    std::getline(stream, t.timestamp, ',');
    std::getline(stream, t.sender_account, ',');
    std::getline(stream, t.receiver_account, ',');

    if (std::getline(stream, item, ',') && !item.empty())
    {
        try
        {
            t.amount = std::stod(item);
        }
        catch (...)
        {
            t.amount = 0.0;
        }
    }
    else
    {
        t.amount = 0.0;
    }

    std::getline(stream, t.transaction_type, ',');
    std::getline(stream, t.merchant_category, ',');
    std::getline(stream, t.location, ',');
    std::getline(stream, t.device_used, ',');

    std::getline(stream, item, ',');
    t.is_fraud = (item == "TRUE");

    std::getline(stream, t.fraud_type, ',');
    std::getline(stream, t.time_since_last_transaction, ',');

    if (std::getline(stream, item, ',') && !item.empty())
    {
        try
        {
            t.spending_deviation_score = std::stod(item);
        }
        catch (...)
        {
            t.spending_deviation_score = 0.0;
        }
    }
    else
    {
        t.spending_deviation_score = 0.0;
    }

    if (std::getline(stream, item, ',') && !item.empty())
    {
        try
        {
            t.velocity_score = std::stoi(item);
        }
        catch (...)
        {
            t.velocity_score = 0;
        }
    }
    else
    {
        t.velocity_score = 0;
    }

    if (std::getline(stream, item, ',') && !item.empty())
    {
        try
        {
            t.geo_anomaly_score = std::stod(item);
        }
        catch (...)
        {
            t.geo_anomaly_score = 0.0;
        }
    }
    else
    {
        t.geo_anomaly_score = 0.0;
    }

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

    ArrayStorage arrayStorage(1000000);

    std::string line;
    int lineNum = 1;           // since header is line 1
    std::getline(input, line); // skip header

    Transaction transaction[test_size];
    int limit = 1000;
    int count = 0;

    while (std::getline(input, line) && count < limit)
    {
        Transaction t = parseTransaction(line);
        arrayStorage.addTransaction(t);
        // can add error handling
    }

    if (arrayStorage.getSize() == 0)
    {
        std::cout << "No transactions were loaded. Please check the CSV content.\n";
    }

    std::cout << "Finished loading " << count << " rows.\n"; // error is here

    std::cout << "Total transactions stored: " << arrayStorage.getSize() << "\n";

    // print out result to see if it works
    for (int i = 0; i < std::min(10, arrayStorage.getSize()); ++i)
    {
        arrayStorage.getTransaction(i).print();
    }
}