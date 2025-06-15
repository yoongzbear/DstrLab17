// main file to connect the other files heheh

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "arrayStorage.hpp"
#include <algorithm>
#include "csvReader.hpp"

// generate json file from the collected data here?

// file structure from chatgpt idk if want or not (.h is .hpp)
/**
/project-root
│
├── main.cpp                         // Drives the program
├── Transaction.h                   // Defines Transaction struct
├── CsvReader.cpp / .h             // Reads and parses the CSV
├── arrayStorage.cpp / .h          // Implements array-based structure + functions
├── linkedListStorage.cpp / .h     // Implements linked list-based structure + functions
├── SortAlgorithms.cpp / .h        // Sorting algorithms (mergesort)
├── SearchAlgorithms.cpp / .h      // Searching algorithms (binary search)
├── JsonExporter.cpp / .h          // Uses nlohmann/json to export final data
├── PerformanceUtils.cpp / .h      // For timing (clock_t)
 */

int main()
{

    std::string filename{"financial_fraud_detection_dataset.csv"}; // csv file

    //-----------------------------------Array Storage----------------------------------------------
    // array definitions
    ArrayStorage arrayStorage(1000000); // 1 million capacity for overall array storage
    ArrayStorage cardArray, achArray, wireArray, upiArray, otherArray; // initialize array storages

    // load csv into array
    readCsvArray(filename, arrayStorage, cardArray, achArray, wireArray, upiArray, otherArray);

    // check if array is empty
    if (arrayStorage.getSize() == 0)
    {
        std::cout << "No transactions were loaded. Please check the CSV content.\n";
    }

    // debugging message to see size
    std::cout << "Total transactions stored: " << arrayStorage.getSize() << "\n";

    // print out result to see if it works for array
    for (int i = 0; i < std::min(10, arrayStorage.getSize()); ++i)
    {
        arrayStorage.getTransaction(i).print();
    }

    std::cout << "Total card transactions: " << cardArray.getSize() << "\n";
    std::cout << "Total ACH transactions: " << achArray.getSize() << "\n";
    std::cout << "Total wire transactions: " << wireArray.getSize() << "\n";
    std::cout << "Total UPI transactions: " << upiArray.getSize() << "\n";
    std::cout << "Total unidentified transactions: " << otherArray.getSize() << "\n";

    return 0;
}