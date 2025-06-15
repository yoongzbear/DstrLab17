// header for transaction csv

#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <iostream>

// struct

struct Transaction
{
    std::string transaction_id;
    std::string timestamp;
    std::string sender_account;
    std::string receiver_account;
    double amount;
    std::string transaction_type;
    std::string merchant_category;
    std::string location;
    std::string device_used;
    bool is_fraud;
    std::string fraud_type;
    std::string time_since_last_transaction;
    double spending_deviation_score;
    int velocity_score;
    double geo_anomaly_score;
    std::string payment_channel;
    std::string ip_address;
    std::string device_hash;

    void print() const
    {
        std::cout << transaction_id << " | "
                  << timestamp << " | "
                  << sender_account << " | "
                  << receiver_account << " | "
                  << amount << " | "
                  << transaction_type << " | "
                  << merchant_category << " | "
                  << location << " | "
                  << device_used << " | "
                  << (is_fraud ? "FRAUD" : "LEGIT") << " | "
                  << fraud_type << " | "
                  << time_since_last_transaction << " | "
                  << spending_deviation_score << " | "
                  << velocity_score << " | "
                  << geo_anomaly_score << " | "
                  << payment_channel << " | "
                  << ip_address << " | "
                  << device_hash << "\n";
    }
};

#endif