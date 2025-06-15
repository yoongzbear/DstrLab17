// read the csv file

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "arrayStorage.hpp"
#include <algorithm>

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
        catch (...) // add something
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
        catch (...) // add something here
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

void readCsvArray(const std::string &filename,
                  ArrayStorage &arrayStorage,
                  ArrayStorage &cardArray,
                  ArrayStorage &achArray,
                  ArrayStorage &wireArray,
                  ArrayStorage &upiArray,
                  ArrayStorage &otherArray)
{
    std::ifstream input{filename};

    // cannot read file
    if (!input.is_open())
    {
        std::cerr << "Couldn't read file: " << filename << "\n";
        return;
    }

    std::string line;
    std::getline(input, line); // skip header

    // add into array and linked list
    while (std::getline(input, line))
    {
        Transaction t = parseTransaction(line); // parse row
        arrayStorage.addTransaction(t); // add into overall array storage
        // can add error handling

        // separate arrays
        if (t.payment_channel == "card")
        {
            cardArray.addTransaction(t);
        }
        else if (t.payment_channel == "ACH")
        {
            achArray.addTransaction(t);
        }
        else if (t.payment_channel == "wire_transfer")
        {
            wireArray.addTransaction(t);
        }
        else if (t.payment_channel == "UPI")
        {
            upiArray.addTransaction(t);
        }
        else
        {
            otherArray.addTransaction(t); // unidentified channel
        }
    }

}