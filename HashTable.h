#pragma once

#include <iostream>

/* Интерфейс хеш-таблицы */

template <typename K, typename T>
class HashTable {
public:
	virtual void Insert(const K& key, const T& value) = 0; // добавление значения по ключу
	virtual bool Remove(const K& key) = 0; // удаление по ключу
	virtual bool Find(const K& key) const = 0; // поиск по ключу

	virtual void Clear() = 0; // очистка таблицы

	virtual int GetSize() const = 0; // получение числа элементов
	virtual bool IsEmpty() const = 0; // проверка на пустоту
	virtual T Get(const K& key) const = 0; // получение значения по ключу

	virtual void Print() const = 0; // вывод таблицы
};