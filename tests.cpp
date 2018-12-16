#include <iostream>
#include <string>
#include <cassert>

#include "SeparateChainingTable.hpp"
#include "LinearProbingTable.hpp"
#include "QuadraticProbingTable.hpp"
#include "DoubleHashingTable.hpp"

using namespace std;

// простейшая хеш-функция
int GetHash(int key) {
	return key % 100;
}

// вторая хеш функция для двойного хеширования
int GetHash2(int key) {
	return 7 - key % 7;
}

void InsertTests(HashTable<int, string> *table) {
	cout << "Insert tests: ";

	assert(table->GetSize() == 0);
	assert(table->IsEmpty());

	table->Insert(12345, "first");

	assert(table->GetSize() == 1);
	assert(!table->IsEmpty());

	table->Insert(5435, "second");
	table->Insert(3435, "third");
	table->Insert(3452, "fourth");
	table->Insert(135, "fifth");
	table->Insert(35, "sixth");

	assert(table->GetSize() == 6);
	assert(!table->IsEmpty());

	cout << "OK" << endl;
}

void FindTests(HashTable<int, string> *table) {
	cout << "Find tests: ";

	assert(table->GetSize() == 6);

	assert(table->Find(12345));
	assert(table->Find(5435));
	assert(table->Find(3435));
	assert(table->Find(3452));
	assert(table->Find(135));
	assert(table->Find(35));
	assert(!table->Find(0));
	assert(!table->Find(235));
	assert(!table->Find(2345));

	cout << "OK" << endl;
}

void RemoveTests(HashTable<int, string> *table) {
	cout << "Remove tests: ";

	assert(table->GetSize() == 6);

	assert(table->Remove(5435));
	assert(table->GetSize() == 5);

	assert(!table->Remove(0));
	assert(!table->Remove(235));

	assert(table->GetSize() == 5);
	assert(!table->Find(5435));
	assert(table->Find(12345));
	assert(table->Find(3435));
	assert(table->Find(3452));
	assert(table->Find(135));
	assert(table->Find(35));
	assert(!table->Find(0));
	assert(!table->Find(235));

	cout << "OK" << endl;
}

void GetTests(HashTable<int, string> *table) {
	cout << "Get tests: ";

	assert(table->GetSize() == 5);
	assert(table->Get(12345) == "first");
	assert(table->Get(3435) == "third");
	assert(table->Get(3452) == "fourth");
	assert(table->Get(135) == "fifth");
	assert(table->Get(35) == "sixth");

	bool excepted = false;

	try {
		table->Get(5435);
	}
	catch (string) {
		excepted = true;
	}

	assert(excepted);

	cout << "OK" << endl;
}

void ClearTest(HashTable<int, string> *table) {
	cout << "Clear test: ";

	assert(table->GetSize() == 5);
	assert(!table->IsEmpty());

	table->Clear();

	assert(table->GetSize() == 0);
	assert(table->IsEmpty());

	cout << "OK" << endl;
}

void Tests(HashTable<int, string> *table, string description) {
	cout << description << endl;

	InsertTests(table);
	FindTests(table);
	RemoveTests(table);
	GetTests(table);
	ClearTest(table);

	cout << endl;
}

int main() {
	HashTable<int, string> *chaining = new SeparateChainingTable<int, string>(100, GetHash);
	HashTable<int, string> *linear = new LinearProbingTable<int, string>(100, GetHash);
	HashTable<int, string> *quadratic = new QuadraticProbingTable<int, string>(100, GetHash);
	HashTable<int, string> *doubleHashing = new DoubleHashingTable<int, string>(100, GetHash, GetHash2);

	Tests(chaining, "Tests for table with separate chaining method");
	Tests(linear, "Tests for table with linear probing method");
	Tests(quadratic, "Tests for table with quadratic probing method");
	Tests(doubleHashing, "Tests for table with double hashing method");
}