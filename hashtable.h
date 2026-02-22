/*
 * hashtable.h
 *
 * A basic hashtable implementation.  This hashtable uses vectors,
 * rather than linked lists, to implement chaining.
 * 
 * Author: <your name here>
 */

#ifndef _HASHTABLE_PROJECT_H
#define _HASHTABLE_PROJECT_H

#include <functional>   // for std::hash
#include <vector>
#include <algorithm>

using namespace std;

template <class T, class H = std::hash<T>>
class hashtable {
public:
    // constructor
    hashtable() {
        mTable.resize(4);
        mSizeTable = 4;
        mSizeValues = 0;

    }

    // basic hashset operations
    void insert(const T& key) {
        if (contains(key)) {
            return;
        }

        mSizeValues++;

        if (load_factor() >= 0.75 ) {
            mSizeTable = mSizeTable * 2;
            vector<vector<T>> tempTable(mSizeTable);
            for (size_t i = 0; i < mTable.size(); i++)
            {
                for (size_t j = 0; j < mTable.at(i).size(); j++)
                {
                    size_t hashLocation = hash(mTable.at(i).at(j)) % mSizeTable;
                    tempTable.at(hashLocation).push_back(mTable.at(i).at(j));
                }
                
            }

            mTable.swap(tempTable);
        }
        // Actually Insert
        size_t newHashLocation = hash(key) % mSizeTable;
        mTable.at(newHashLocation).push_back(key);

    }

    void remove(const T& key) {

        size_t index = hash(key) % mSizeTable;
        for (size_t i = 0; i < mTable.at(index).size(); i++)
        {
            if ( mTable.at(index).at(i) == key ) {
                mTable.at(index).erase(mTable.at(index).begin() + i);
                // return;
                mSizeValues--;
                break;
            }
        }
        return;
    }

    bool contains(const T& key) {
        size_t index = hash(key) % mSizeTable;

        for (size_t i = 0; i < mTable.at(index).size(); i++)
        {
            if (mTable.at(index).at(i) == key)
            {
                return true;
            }
            
        }
        return false;
        


        // for (size_t i = 0; i < mSizeTable; i++)
        // {
        //     if ( find(mTable.at(i).begin(), mTable.at(i).end(), key) != mTable.at(i).end()) {
        //         return true;
        //     }
        // }
        // return false;
    }

    int compares(const T& key) {
        size_t index = hash(key) % mSizeTable;
        int counter = 0;
        for (size_t i = 0; i < mTable.at(index).size(); i++)
        {
            counter++;
            if (mTable.at(index).at(i) == key)
            {
                return counter;
            }
            
        }
        return counter;

        // for (size_t i = 0; i < mSizeTable; i++)
        // {
        //     if ( find(mTable.at(i).begin(), mTable.at(i).end(), key) != mTable.at(i).end()) {
        //         return true;
        //     }
        // }
        // return false;
    }

    size_t size() {
        return mSizeValues;
    }

    // diagnostic functions
    double load_factor() {
        return double(mSizeValues) / mSizeTable;
    }

    // convenience method, invokes the "hash" template parameter
    // function object to get a hash code
    static size_t hash(const T &key) {
        H h;
        return h(key);
    }

private:
    vector<vector<T>> mTable;
    int mSizeTable;
    int mSizeValues;
 
};

#endif
