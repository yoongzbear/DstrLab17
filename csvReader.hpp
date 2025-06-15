// header for csvReader

#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include "arrayStorage.hpp"
#include "transaction.hpp"

Transaction parseTransaction(const std::string &line);

void readCsvArray(const std::string &filename,
                  ArrayStorage &arrayStorage,
                  ArrayStorage &cardArray,
                  ArrayStorage &achArray,
                  ArrayStorage &wireArray,
                  ArrayStorage &upiArray,
                  ArrayStorage &otherArray);

#endif