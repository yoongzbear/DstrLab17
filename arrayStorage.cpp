// array

#include "arrayStorage.hpp"
#include <iostream>

// set initial capacity
const int INITIAL_CAPACITY = 2000000;

// initialize array constructor
ArrayStorage::ArrayStorage()
{
    this->transaction_data = new Transaction[this->capacity];
    this->capacity = INITIAL_CAPACITY;
    this->size = 0;
}

// array destuctor
ArrayStorage::~ArrayStorage()
{
    delete[] this->transaction_data;
}

void ArrayStorage::resize()
{
    // double the capacity once array reaches its limit
    int newCapacity = capacity * 2;
    Transaction *newData = new Transaction[newCapacity];

    for (int i = 0; i < size; ++i)
    {
        newData[i] = transaction_data[i]; // copy old data
    }

    delete[] transaction_data; // free old memory
    transaction_data = newData; //  point to new memory
    capacity = newCapacity;
}

// add row into array
void ArrayStorage::addTransaction(Transaction transaction) {
    if (size == capacity)
    {
        resize();
    }
    transaction_data[size++] = transaction; // add the row into array
}

// get size
int ArrayStorage::getSize() {
    return size;
}

// get specific row
Transaction ArrayStorage::getTransaction(int index) {
    if (index >= 0 && index < size) {
        return transaction_data[index];
    }
    throw std::out_of_range("Index out of range");
}