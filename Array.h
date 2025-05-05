#pragma once
#include <exception>
#include <iostream>
#include <stdint.h>
#include "DataManager.h"

#define SIZE 10
#define RESIZEAMOUNT 5
#define MAX_SIZE INT32_MAX/4

template <typename T> class Array : public DataManager<T>
{
public:

	Array();
	~Array();
	Array(unsigned int);
	Array(const Array& other);
	Array(Array&&) noexcept;
	Array& operator=(Array&&);
	
	std::unique_ptr<DataManager<T>> clone() const override;
	void add(T&&);
	bool isFull();
	bool isEmpty();
	T& get(unsigned int i);
	T& operator[](unsigned int i);
	const T& operator[](unsigned int i) const;
	Array<T>& operator=(const Array<T>& other);
	unsigned int getSize() const;
	void resize();
	void show();
	void deleteAt(unsigned int i);
	unsigned int getCount() const;

private:

	unsigned int _count;
	unsigned int _size;
	T** _data;

	void clear();
	void moveElementsLeft(unsigned int);
};

template <typename T>
Array<T>::Array()
{
	_count = 0;
	_size = SIZE;
	_data = new T* [_size];
	for (unsigned int i = 0; i < _size; i++)
	{
		_data[i] = nullptr;
	}
}

template <typename T>
Array<T>::Array(unsigned int size)
{
	_count = 0;
	_size = size;
	if (size > MAX_SIZE) throw std::exception("Constructor failure:");
	_data = new T* [_size];
	for (unsigned int i = 0; i < _size; i++)
	{
		_data[i] = nullptr;
	}
}

template <typename T>
Array<T>::Array(const Array& other)
{
	for (unsigned int i = 0; i < _size; i++) if (_data[i]) delete _data[i];
	delete[] _data;
	_count = other._count;
	_size = other.getSize();
	_data = new T* [_size];
	for (unsigned int i = 0; i < _count; i++)
	{
		if (other._data[i])
		{
			_data[i] = new T(*other._data[i]);
		}
		else
		{
			_data[i] = nullptr;
		}
			
	}
	
}

template<typename T>
Array<T>::Array(Array&& other) noexcept
{
	_size = other._size;
	_count = other._count;
	_data = other._data;
	other._data = nullptr;
	other._size = 0;
	other._count = 0;
}

template <typename T>
Array<T>::~Array()
{
	for (unsigned int i = 0; i < _count; i++)
	{
		if (_data[i]) delete _data[i];
	}
	delete[] _data;
}

template<typename T>
std::unique_ptr<DataManager<T>> Array<T>::clone() const
{
		return std::make_unique<Array<T>>(*this);
}

template <typename T>
void Array<T>::add(T&& x) //add to first empty place
{
	if (isFull())
	{
		resize();
	}

	_data[_count] = new T(std::forward<T>(x));
	_count++;
}

template <typename T>
bool Array<T>::isFull()
{
	return (_count == _size) ? true : false;
}

template <typename T>
bool Array<T>::isEmpty()
{
	return (_count) ? false : true;
}

template <typename T>
T& Array<T>::get(unsigned int i)
{
	if (i > _count - 1) throw std::exception("Get failure: i > _count");
	return *_data[i];
}

template<typename T>
unsigned int Array<T>::getCount() const
{
	return _count;
}

template <typename T>
T& Array<T>::operator[](unsigned int i)
{
	if (i > _count - 1) throw std::exception("Get failure:");
	return *_data[i];
}

template<typename T>
 const T& Array<T>::operator[](unsigned int i) const
{
	if (i > _count - 1) throw std::exception("Get failure:");
	return *_data[i];
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (this != &other) {

		for (unsigned int i = 0; i < _size; ++i) {
			delete _data[i];
		}
		delete[] _data;

		_size = other._size;
		_count = other._count;
		_data = new T * [_size];

		for (unsigned int i = 0; i < _size; ++i) {
			if (i < other._count && other._data[i]) {
				_data[i] = new T(*other._data[i]);
			}
			else {
				_data[i] = nullptr;
			}
		}
	}
	return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& other)
{
	for (unsigned int i = 0; i < _size; i++)
	{
		if (_data[i])
		delete _data[i];
	}
	if (_data) delete[] _data;
	_size = other._size;
	_count = other._count;
	_data = other._data;
	other._data = nullptr;
	return *this;
}

template <typename T>
void Array<T>::clear()
{
	for (unsigned int i = 0; i < _count; ++i) {
		delete _data[i];
		_data[i] = nullptr;
	}
	_count = 0;
}

template <typename T>
void Array<T>::moveElementsLeft(unsigned int pos)
{
	if (pos < 1 || pos >= _count) throw std::exception("MoveElementsLeft failure: ");
	for (unsigned int i = pos; i < _size; i++)
	{
			_data[i - 1] = _data[i];
	}
}

template <typename T>
unsigned int Array<T>::getSize() const
{
	return _size;
}

template <typename T>
void Array<T>::resize()
{
	if (_size + RESIZEAMOUNT > MAX_SIZE) throw std::exception("Resize failure");

	unsigned int newSize = _size + RESIZEAMOUNT;
	T** newData = new T * [newSize] { nullptr };

	for (unsigned int i = 0; i < _count; ++i) {
		newData[i] = _data[i];
	}

	delete[] _data;

	_data = newData;
	_size = newSize;
}

template <typename T>
void Array<T>::show()
{
	if (isEmpty())
	{
		std::cout << "Array is empty!" << std::endl;
		return;
	}
	for (unsigned int i = 0; i < _count; i++)
	{
		std::cout << "Element " << i << " : " << *_data[i] << std::endl;
	}
}

template <typename T>
void Array<T>::deleteAt(unsigned int i)
{
	if (i >= _count) throw std::exception("Delete failure");

	delete _data[i];

	for (unsigned int j = i; j < _count - 1; ++j) {
		_data[j] = _data[j + 1];
	}

	_data[_count - 1] = nullptr;
	_count--;
}

template <typename T>
bool find(Array<T> arr, T item, int& idx)
{
	for (int i = 0; i < arr.getCount(); i++)
	{
		if (arr.get(i) == item)
		{
			idx = i;
			return true;
		}
	}
	return false;
}
