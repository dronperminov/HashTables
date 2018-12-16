#pragma once

#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

/*
	Хеш таблица на основе метода цепочек
*/

template <typename K, typename T>
class SeparateChainingTable : public HashTable<K, T> {
    struct Node {
    	K key; // значение ключа элемента
    	T value; // значение элемента
    	Node *next; // указатель на следующий элемент
    };

    int capacity; // ёмкость таблицы
    Node **cells; // массив ячеек (списков)

    int (*h)(K); // указатель на хеш-функцию

public:
    SeparateChainingTable(int size, int (*h)(K)); // конструктор из размера и хеш-функции
    SeparateChainingTable(const SeparateChainingTable& table); // конструктор копирования

    void Insert(const K& key, const T& value); // добавление значения по ключу
    bool Remove(const K& key); // удаление по ключу
    bool Find(const K& key) const; // поиск по ключу

    void Clear(); // очистка таблицы

    int GetSize() const; // получение размера
    bool IsEmpty() const; // проверка на пустоту

    T Get(const K& key) const; // получение значения по ключу

    void Print() const; // вывод таблицы

    ~SeparateChainingTable(); // деструктор (освобождение памяти)
};

// конструктор из размера и хеш-функции
template <typename K, typename T>
SeparateChainingTable<K, T>::SeparateChainingTable(int size, int (*h)(K)) {
	capacity = size; // запоминаем в ёмкости переданный размер
	cells = new Node*[size]; // выделяем память под массив списков

	// обнуляем все списки
	for (int i = 0; i < size; i++)
		cells[i] = nullptr;

	this->h = h; // запоминаем указатель на хеш-функцию
}

// конструктор копирования
template <typename K, typename T>
SeparateChainingTable<K, T>::SeparateChainingTable(const SeparateChainingTable& table) {
	capacity = table.capacity;
	cells = new Node*[capacity];

	h = table.h; // копируем указатель на функцию

	// проходимся по всем ячейкам таблицы
	for (int i = 0; i < capacity; i++) {
		Node *prev = nullptr;

		// проходимся по всему списку каждой ячейки
		for (Node *elem = table.cells[i]; elem != nullptr; elem = elem->next) {
			Node *node = new Node; // создаём новый элемент

			node->key = elem->key; // сохраняем ключ
			node->value = elem->value; // сохраняем значение
			node->next = nullptr;

			if (prev == nullptr) { // если нет предыдущего
				cells[i] = node; // то этот элемент первый в списке
			}
			else {
				prev->next = node; // иначе предыдущий указывает на следующий
			}

			prev = node; // обновляем указатель на предыдущий элемент
		}
	}
}

// // добавление значения по ключу
template <typename K, typename T>
void SeparateChainingTable<K, T>::Insert(const K& key, const T& value) {
	int index = h(key); // получаем индекс для вставки

	Node *node = new Node; // создаём новый элемент

	node->key = key; // сохраняем ключ
	node->value = value; // сохраняем значение
	node->next = cells[index]; // следующий элемент будет первый в списке

	cells[index] = node; // вставляем в начало списка для быстродействия
}

// удаление по ключу
template <typename K, typename T>
bool SeparateChainingTable<K, T>::Remove(const K& key) {
	int index = h(key); // получаем индекс списка по ключу

	Node *node = cells[index]; // первый элемент списка
	Node *prev = nullptr; // предыдущий элемент

	// ищем элемент в списке
	while (node && node->key != key) {
		prev = node; // запоминаем предыдущий
		node = node->next; // переходим на следующий
	}

	// если не нашли элемент, то возвращаем ложь
	if (node == nullptr)
		return false;

	// если нет предыдущего, значит элемент - первый
	if (prev == nullptr) {
		cells[index] = node->next; // делаем первым второй
	}
	else {
		prev->next = node->next; // иначе перебрасываем указатель предыдущего на следующий
	}

	delete node; // удаляем элемент списка из памяти

	return true; // удалили, возвращаем истину
}

// поиск по ключу
template <typename K, typename T>
bool SeparateChainingTable<K, T>::Find(const K& key) const {
	int index = h(key); // получаем индекс ячейки по ключу

	Node *node = cells[index]; // запоминаем элемент списка

	// ищем элемент
	while (node && node->key != key)
		node = node->next;

	return node != nullptr; // если не дошли до конца, значит нашли, иначе нет
}

template <typename K, typename T>
void SeparateChainingTable<K, T>::Clear() {
	for (int i = 0; i < capacity; i++) {
		while (cells[i]) {
			Node *node = cells[i]; // запоминаем текущий элемент
			cells[i] = cells[i]->next; // переходим на следующий

			delete node; // удаляем элемент
		}
	}
}

// получение размера
template <typename K, typename T>
int SeparateChainingTable<K, T>::GetSize() const {
	int size = 0; // обнуляем размер

	// проходимся по всем ячейкам
	for (int i = 0; i < capacity; i++) {
		Node *node = cells[i]; // получаем указатель на начало списка

		// проходимся по всему списку
		while (node) {
			size++; // увеличиваем размер
			node = node->next; // переходим к следующему элементу
		}
	}

	return size; // возвращаем найденный размер
}

// проверка на пустоту
template <typename K, typename T>
bool SeparateChainingTable<K, T>::IsEmpty() const {
	for (int i = 0; i < capacity; i++)
		if (cells[i])
			return false; // если хотя бы один список не пуст, значит таблица не пуста

	return true; // таблица пуста
}

// получение значения по ключу
template <typename K, typename T>
T SeparateChainingTable<K, T>::Get(const K& key) const {
	int index = h(key); // получаем индекс по ключу

	Node *node = cells[index];

	// ищем элемент с таким ключом
	while (node && node->key != key)
		node = node->next;

	// если не нашли элемент с таким ключом
	if (node == nullptr)
		throw string("No value with this key"); // бросаем исключение

	return node->value; // возвращаем значение
}

// деструктор (освобождения памяти)
template <typename K, typename T>
SeparateChainingTable<K, T>::~SeparateChainingTable() {
	Clear(); // удаляем все элементы

	delete[] cells; // удаляем массив ячеек
}

// оператор вывода в поток
template <typename K, typename T>
void SeparateChainingTable<K, T>::Print() const {
    for (int i = 0; i < capacity; i++) {
		if (cells[i] == nullptr)
			continue; // если нет списка, то переходим к следующему элементу

		cout << "[" << i << "]: "; // выводим номер ячейки

		Node *node = cells[i];

		// проходимся по всему списку
		while (node) {
			cout << node->value << "(" << node->key << ") ";
			node = node->next;
		}

		cout << endl;
	}
}
