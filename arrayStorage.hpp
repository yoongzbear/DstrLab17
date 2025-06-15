// header for array 

#ifndef ARRAY_STORAGE_HPP
#define ARRAY_STORAGE_HPP

#include "transaction.hpp"

class ArrayStorage { 
    private:
        Transaction* transaction_data; 
        int capacity; // for memory capacity
        int size;

        void  resize(); // resizing capacity

    public: 
        ArrayStorage(); // constructor
        ~ArrayStorage(); // destructor
        void addTransaction(Transaction transaction); // add row to array
        int getSize(); // get size of array
        Transaction getTransaction(int index);
};

#endif