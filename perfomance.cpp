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
const int n = size / 3 * 2;

int GetHash(int key) {
	/*int hash = 0;

	while (key) {
		hash |= key & 0xff;
		key >>= 2;
	}

	return hash;*/
	return key;
}

int GetHash2(int key) {
	return (key % 7) + 1;
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

	for (size_t i = 0; i < keys.size(); i++)
		if (!table->Find(keys[i]))
			throw "";
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
	HashTable<int, int> *linear2 = new LinearProbingTable<int, int>(size, GetHash, 2);
	HashTable<int, int> *linear4 = new LinearProbingTable<int, int>(size, GetHash, 4);
	HashTable<int, int> *linear8 = new LinearProbingTable<int, int>(size, GetHash, 8);
	HashTable<int, int> *linear64 = new LinearProbingTable<int, int>(size, GetHash, 64);
	HashTable<int, int> *linear256 = new LinearProbingTable<int, int>(size, GetHash, 256);
	HashTable<int, int> *linear1024 = new LinearProbingTable<int, int>(size, GetHash, 1024);
	HashTable<int, int> *quadratic = new QuadraticProbingTable<int, int>(size, GetHash);
	HashTable<int, int> *doubleHash = new DoubleHashingTable<int, int>(size, GetHash, GetHash2);

	vector<int> keys;

	for (int i = 0; i < n; i++)
		keys.push_back(rand() % limit);

	InsertTests(keys, chaining, "Separate chaining method (insert)");
	InsertTests(keys, quadratic, "Quadratic probing method (insert)");
	InsertTests(keys, doubleHash, "Doubly hashing method (insert)");
	InsertTests(keys, linear1024, "Linear probing method q = 1024 (insert)");
	InsertTests(keys, linear256, "Linear probing method q = 256 (insert)");
	InsertTests(keys, linear64, "Linear probing method q = 64 (insert)");
	InsertTests(keys, linear8, "Linear probing method q = 8 (insert)");
	InsertTests(keys, linear4, "Linear probing method q = 4 (insert)");
	InsertTests(keys, linear2, "Linear probing method q = 2 (insert)");
	InsertTests(keys, linear, "Linear probing method q = 1 (insert)");

	cout << endl;

	FindTests(keys, chaining, "Separate chaining method (find)");
	FindTests(keys, quadratic, "Quadratic probing method (find)");
	FindTests(keys, doubleHash, "Double hashing method (find)");
	FindTests(keys, linear1024, "Linear probing method q = 1024 (find)");
	FindTests(keys, linear256, "Linear probing method q = 256 (find)");
	FindTests(keys, linear64, "Linear probing method q = 64 (find)");
	FindTests(keys, linear8, "Linear probing method q = 8 (find)");
	FindTests(keys, linear4, "Linear probing method q = 4 (find)");
	FindTests(keys, linear2, "Linear probing method q = 2 (find)");
	FindTests(keys, linear, "Linear probing method q = 1 (find)");

	cout << endl;

	RemoveTests(keys, chaining, "Separate chaining method (remove)");
	RemoveTests(keys, quadratic, "Quadratic probing method (remove)");
	RemoveTests(keys, doubleHash, "Doubly hashing method (remove)");
	RemoveTests(keys, linear1024, "Linear probing method q = 1024 (remove)");
	RemoveTests(keys, linear256, "Linear probing method q = 256 (remove)");
	RemoveTests(keys, linear64, "Linear probing method q = 64 (remove)");
	RemoveTests(keys, linear8, "Linear probing method q = 8 (remove)");
	RemoveTests(keys, linear4, "Linear probing method q = 4 (remove)");
	RemoveTests(keys, linear2, "Linear probing method q = 2 (remove)");
	RemoveTests(keys, linear, "Linear probing method q = 1 (remove)");
}