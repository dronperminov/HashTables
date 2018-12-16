#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

#include "HashTable.h"
#include "SeparateChainingTable.hpp"
#include "LinearProbingTable.hpp"
#include "QuadraticProbingTable.hpp"
#include "DoubleHashingTable.hpp"

const int size = 100003;
const int limit = 100000;
const int n = size / 2;

int GetHash(int key) {
	return key % size;
}

int GetHash2(int key) {
	return 7 - (key % 7);
}

void InsertTests(vector<int> &keys, HashTable<int, int> *table, string headline) {
	cout << headline;
	
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (size_t i = 0; i < keys.size(); i++)
		table->Insert(keys[i], i);
	
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto millis = duration_cast<microseconds>(t2 - t1).count() / (double) keys.size();

	cout << ": " << millis << " us" << endl;
}

void FindTests(vector<int>& keys, HashTable<int, int> *table, string headline) {
	cout << headline;
	
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (size_t i = 0; i < limit; i++)
		table->Find(i);
	
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto millis = duration_cast<microseconds>(t2 - t1).count() / (double) limit;

	cout << ": " << millis << " us" << endl;
}

void RemoveTests(vector<int> &keys, HashTable<int, int> *table, string headline) {
	cout << headline;
	
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	for (size_t i = 0; i < keys.size(); i++)
		table->Remove(keys[i]);
	
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto us = duration_cast<microseconds>(t2 - t1).count() / (double) keys.size();

	cout << ": " << us << " us" << endl;
}

int main() {
	HashTable<int, int> *chaining = new SeparateChainingTable<int, int>(size, GetHash);
	HashTable<int, int> *linear = new LinearProbingTable<int, int>(size, GetHash);
	HashTable<int, int> *quadratic = new QuadraticProbingTable<int, int>(size, GetHash);
	HashTable<int, int> *doubleHash = new DoubleHashingTable<int, int>(size, GetHash, GetHash2);

	vector<int> keys;

	for (int i = 0; i < n; i++)
		keys.push_back(rand() % limit);

	InsertTests(keys, chaining, "Separate chaining method (insert)");
	InsertTests(keys, quadratic, "Quadratic probing method (insert)");
	InsertTests(keys, doubleHash, "Doubly hashing method (insert)");
	InsertTests(keys, linear, "Linear probing method (insert)");

	cout << endl;

	FindTests(keys, chaining, "Separate chaining method (find)");
	FindTests(keys, quadratic, "Quadratic probing method (find)");
	FindTests(keys, doubleHash, "Double hashing method (find)");
	FindTests(keys, linear, "Linear probing method (find)");

	cout << endl;

	RemoveTests(keys, chaining, "Separate chaining method (remove)");
	RemoveTests(keys, quadratic, "Quadratic probing method (remove)");
	RemoveTests(keys, doubleHash, "Doubly hashing method (remove)");
	RemoveTests(keys, linear, "Linear probing method (remove)");
}