#pragma once

#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

/*
	Хеш таблица на основе линейного пробирования
*/

template <typename K, typename T>
class LinearProbingTable : public HashTable<K, T> {
	const int FREE = 0; // свободная ячейка
	const int BUSY = 1; // занятая ячейка
	const int REMOVED = 2; // удалённая ячейка

    struct HashNode {
    	K key; // значение ключа элемента
    	T value; // значение элемента
    	int state; // состояние ячейки
    };

    int capacity; // ёмкость таблицы
    int size; // число элементов в таблице
    int q; // шаг пробирования

    HashNode *cells; // массив ячеек

    int (*h)(K); // указатель на хеш-функцию

public:
    LinearProbingTable(int tableSize, int (*h)(K), int q = 1); // конструктор из размера, хеш-функции и шага пробирования
    LinearProbingTable(const LinearProbingTable& table); // конструктор копирования

    void Insert(const K& key, const T& value); // добавление значения по ключу
    bool Remove(const K& key); // удаление по ключу
    bool Find(const K& key) const; // поиск по ключу

    void Clear(); // очистка таблицы

    int GetSize() const; // получение размера
    bool IsEmpty() const; // проверка на пустоту

    T Get(const K& key) const; // получение значения по ключу

    void Print() const; // вывод таблицы

    ~LinearProbingTable(); // деструктор (освобождение памяти)
};

// конструктор из размера, хеш-функции и шага пробирования
template <typename K, typename T>
LinearProbingTable<K, T>::LinearProbingTable(int tableSize, int (*h)(K), int q) {
	this->capacity = tableSize; // запоминаем в ёмкости переданный размер
	this->size = 0; // изначально нет элементов
	this->q = q;

	this->cells = new HashNode[tableSize]; // выделяем память под ячейки

	// делаем все ячейки свободными
	for (int i = 0; i < tableSize; i++)
		cells[i].state = FREE;

	this->h = h; // запоминаем указатель на функцию
}

// конструктор копирования
template <typename K, typename T>
LinearProbingTable<K, T>::LinearProbingTable(const LinearProbingTable& table) {
	capacity = table.capacity; // копируем ёмкость
	size = table.size; // копируем количество элементов
	q = table.q; // копируем шаг пробирования

	cells = new HashNode[capacity]; // выделяем память под массив

	h = table.h; // копируем указатель на функцию

	// проходимся по всем ячейкам таблицы и копируем их содержимое
	for (int i = 0; i < capacity; i++) {
		cells[i].value = table.cells[i].value;
		cells[i].key = table.cells[i].key;
		cells[i].state = table.cells[i].state;
	}
}

// добавление значения по ключу
template <typename K, typename T>
void LinearProbingTable<K, T>::Insert(const K& key, const T& value) {
	int sequenceLength = 0; // начальная длина пробной последовательности равна нулю
	int hash = h(key); // получаем хеш от ключа

	while (sequenceLength < capacity) {
		int index = (hash + sequenceLength * q) % capacity;

		if (cells[index].state != BUSY) { // если нашли незанятую ячейку
			cells[index].key = key; // сохраняем ключ
			cells[index].value = value; // сохраняем значение
			cells[index].state = BUSY; // ячейка становится занятой

			size++; // увеличиваем счётчик числа элементов
			return; // выходим
		}

		sequenceLength++; // увеличиваем длину пробной последовательности
	}

	// прошли всю таблицу
	throw string("Unable to insert value with this key"); // бросаем исключение
}

// удаление по ключу
template <typename K, typename T>
bool LinearProbingTable<K, T>::Remove(const K& key) {
	int sequenceLength = 0; // начальная длина пробной последовательности равна нулю
	int hash = h(key); // получаем хеш от ключа

	while (sequenceLength < capacity) {
		int index = (hash + sequenceLength * q) % capacity;

		// если нашли занятую нужным ключом ячейку
		if (cells[index].state == BUSY && cells[index].key == key) {
			cells[index].state = REMOVED; // помечаем её как удалённую
			size--; // уменьшаем счётчик числа элементов

			return true; // возвращаем истину
		}

		// если нашли свободную ячейку
		if (cells[index].state == FREE)
			return false; // возвращаем ложь

		sequenceLength++; // увеличиваем длину пробной последовательности
	}

	return false; // не нашли во всей таблице, возвращаем ложь
}

// поиск по ключу
template <typename K, typename T>
bool LinearProbingTable<K, T>::Find(const K& key) const {
	int sequenceLength = 0; // начальная длина пробной последовательности равна нулю
	int hash = h(key); // получаем хеш от ключа

	while (sequenceLength < capacity) {
		int index = (hash + sequenceLength * q) % capacity; // ищем индекс элемента

		// если нашли занятую клетку с нужным ключом
		if (cells[index].state == BUSY && cells[index].key == key)
			return true; // значит нашли

		// если нашли свободную ячейку
		if (cells[index].state == FREE)
			return false; // значит нет элемента

		sequenceLength++; // увеличиваем длину пробной последовательности
	}

	return false; // не нашли во всей таблице
}

template <typename K, typename T>
void LinearProbingTable<K, T>::Clear() {
	for (int i = 0; i < capacity; i++)
		cells[i].state = FREE;

	size = 0; // обнуляем счётчик числа элементов
}

template <typename K, typename T>
int LinearProbingTable<K, T>::GetSize() const {
	return size; // возвращаем размер
}

template <typename K, typename T>
bool LinearProbingTable<K, T>::IsEmpty() const {
	return size == 0; // таблица пуста, если нет элементов
}

// получение значения по ключу
template <typename K, typename T>
T LinearProbingTable<K, T>::Get(const K& key) const {
	int sequenceLength = 0;
	int hash = h(key); // получаем хеш от ключа

	while (sequenceLength < capacity) {
		int index = (hash + sequenceLength * q) % capacity; // ищем индекс элемента

		// если нашли занятую клетку с нужным ключом
		if (cells[index].state == BUSY && cells[index].key == key)
			return cells[index].value; // значит нашли

		// если нашли свободную ячейку, значит нет такого элемента
		if (cells[index].state == FREE)
			throw string("No value with this key"); // бросаем исключение

		sequenceLength++; // увеличиваем длину пробной последовательности
	}

	// обошли всю таблицу
	throw string("No value with this key"); // бросаем исключение
}

// деструктор (освобождения памяти)
template <typename K, typename T>
LinearProbingTable<K, T>::~LinearProbingTable() {
	delete[] cells; // удаляем массив ячеек
}

// оператор вывода в поток
template <typename K, typename T>
void LinearProbingTable<K, T>::Print() const {
    for (int i = 0; i < capacity; i++) {
		if (cells[i].state != BUSY)
			continue; // если ячейка не занята, то переходим к следующему элементу

		cout << "[" << i << "]: "; // выводим номер ячейки
		cout << cells[i].value << "(" << cells[i].key << ") "; // выводим содержимое ячейки
		cout << endl; // переходим на новую строку
	}
}
