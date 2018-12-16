#include <iostream>
#include <cstdlib>
#include <string>

#include "HashTable.h"
#include "SeparateChainingTable.hpp"
#include "LinearProbingTable.hpp"
#include "QuadraticProbingTable.hpp"
#include "DoubleHashingTable.hpp"

using namespace std;

int GetHash(int key) {
    return key % 29;
}

int GetHash2(int key) {
    return 7 - key % 7;
}

void Print(HashTable<int, string> *table) {
    table->Print();
}

void Insert(HashTable<int, string> *table) {
    int key;
    string value;

    cout << "Enter key and value: ";
    cin >> key >> value;

    table->Insert(key, value);
    cout << "Inserted!" << endl;
}

void Remove(HashTable<int, string> *table) {
    int key;

    cout << "Enter key: ";
    cin >> key;

    if (table->Remove(key)) {
        cout << "Removed!" << endl;
    }
    else {
        cout << "No value with this key";
    }
}

void Find(HashTable<int, string> *table) {
    int key;

    cout << "Enter key: ";
    cin >> key;

    if (table->Find(key)) {
        cout << "Find!" << endl;
    }
    else {
        cout << "No value with this key";
    }
}

void Get(HashTable<int, string> *table) {
    int key;

    cout << "Enter key: ";
    cin >> key;

    string value = table->Get(key);
    
    cout << "Value: " << value << endl;
}

void Clear(HashTable<int, string> *table) {
    table->Clear();
    cout << "Cleared!" << endl;
}

void GetSize(HashTable<int, string> *table) {
    cout << "Size: " << table->GetSize() << endl;
}

int main() {
    string type;

    cout << "Select type of table (1 - separate chaining, 2 - linear probing, 3 - quadratic probing, 4 - double hashing): ";
    cin >> type;

    while (type != "1" && type != "2" && type != "3" && type != "4") {
        cout << "Incorrect type. Try again: ";
        cin >> type;
    }

    int size;

    cout << "Enter size: ";
    cin >> size;

    while (size < 2) {
        cout << "Incorrect size. Try again: ";
        cin >> size;
    }

    HashTable<int, string> *table;

    if (type == "1") {
        table = new SeparateChainingTable<int, string>(size, GetHash);
    }
    else if (type == "2") {
        table = new LinearProbingTable<int, string>(size, GetHash);   
    }
    else if (type == "3") {
        table = new QuadraticProbingTable<int, string>(size, GetHash);
    }
    else {
        table = new DoubleHashingTable<int, string>(size, GetHash, GetHash2);
    }

    int item; // выбираемый пункт меню

    do {
        system("cls"); // очищаем экран
        // выводим меню
        cout << "What do you want to do?" << endl;
        cout << "1. Print" << endl;
        cout << "2. Insert" << endl;
        cout << "3. Remove" << endl;
        cout << "4. Find" << endl;
        cout << "5. Get" << endl;
        cout << "6. Clear" << endl;
        cout << "7. Get size" << endl;
        cout << "8. Quit" << endl;
        cout << ">";
        cin >> item; // считываем пункт меню

        // обрабатываем некорректный ввод
        while (item < 1 || item > 8) {
            cout << "Incorrect item. Try again: ";
            cin >> item; // считываем пункт меню заново
        }

        // в зависимости от выбранного пункта выполняем действие
        switch (item) {
            case 1:
                Print(table);
                break;

            case 2:
                Insert(table);
                break;

            case 3:
                Remove(table);
                break;

            case 4:
                Find(table);
                break;

            case 5:
                Get(table);
                break;

            case 6:
                Clear(table);
                break;

            case 7:
                GetSize(table);
                break;
        }

        if (item != 8) {
            system("pause"); // задерживаем экран
        }
    } while (item != 8); // повторяем, пока не решим выйти

    return 0;
}