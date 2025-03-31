#pragma once
#include <exception>
#include <iostream>
#include <stdint.h>
#include "DataManager.h"

#define SIZE 10
#define RESIZEAMOUNT 5
#define MAX_SIZE INT32_MAX/4

template <typename T> class Array : public DataManager<T> //����� - ���� �� �������� �������� ������
{
public:
	Array();
	Array(int);
	Array(const Array& Array);
	~Array();

	void add(T&&);
	void pushAt(int, T&&);
	bool isFull();
	bool isEmpty();
	T get(int) const;
	T operator[](int at) const;
	int getSize() const;
	void resize(int);
	void show();
	void deleteAt(int);
	bool find(T&& x, int &index);

private:
	unsigned int _size;
	unsigned int _count;
	T* _data;

	void clear();
	void moveElementsLeft(int);
};

template <typename T>
Array<T>::Array()
{
	_count = 0;
	_size = SIZE;
	_data = new T [_size];
}

template <typename T>
Array<T>::Array(int size)
{
	_count = 0;
	if (size < 0 || size > MAX_SIZE) throw std::exception("Constructor failure: ������ ������ ����/������� �������");
	_size = size;
	_data = new T [_size];
}

template <typename T>
Array<T>::Array(const Array& Array)
{
	_count = Array._count;
	_size = Array.getSize();
	_data = new T [_size];
	for (int i = 0; i < _count; i++)
	{
			_data[i] = Array[i];
	}
	
}

template <typename T>
Array<T>::~Array()
{
	delete[] _data;
}

template <typename T>
void Array<T>::add(T&& x)
{
	if (_count == _size)
	{
		resize(RESIZEAMOUNT);
	}

	pushAt(_count, std::forward<T>(x));
}

template <typename T>
void Array<T>::pushAt(int i, T&& x)
{
	if (i < 0 || i >= _size) throw std::exception("Add failure: ������ ������ ����/������� �������");
	_data[i] = x;
	_count++;
}

template <typename T>
bool Array<T>::isFull()
{
	return (_count) ? true : false;
}

template <typename T>
bool Array<T>::isEmpty()
{
	return (_count) ? false : true;
}

template <typename T>
T Array<T>::get(int i) const
{
	if (i > _count - 1) throw std::exception("Get failure: ����� �� �������");
	return _data[i];
}

template <typename T>
T Array<T>::operator[](int i) const
{
	if (i > _count - 1) throw std::exception("Get failure: ����� �� �������");
	return _data[i];
}

template <typename T>
void Array<T>::clear()
{
	_count = 0;
}

template <typename T>
void Array<T>::moveElementsLeft(int pos) //�������� �������� �����, ������� � pos
{
	if (pos < 1 || pos >= _count) throw std::exception("MoveElementsLeft failure: ������� ������ 1 ��� ������, ��� ��������� �������");
	for (int i = pos; i < _size; i++)
	{
			_data[i - 1] = _data[i];
	}
}

template <typename T>
int Array<T>::getSize() const
{
	return _size;
}

template <typename T>
void Array<T>::resize(int slotsToAdd)
{
	if (_size + slotsToAdd > MAX_SIZE || slotsToAdd < 1) throw std::exception("Resize failure: ������� ������� ����� ������ �������/���������� 0 ��� �������������� ���-�� �����");

	T* arr = new T[_size];

	for (int i = 0; i < _size; i++)
	{
			arr[i] = T(_data[i]);
	}

	delete[] _data;

	_size += slotsToAdd;
	_data = new T[_size];
	
	for (int i = 0; i < _size; i++)
	{
		if (i < _size - slotsToAdd)
		{
			_data[i] = arr[i];
		}
	}
	delete[] arr;
}

template <typename T>
void Array<T>::show()
{
	if (isEmpty())
	{
		std::cout << "������ ������" << std::endl;
		return;
	}
	for (int i = 0; i < _count; i++)
	{
		std::cout << "������� " << i << " : " << _data[i] << std::endl;
	}
}

template <typename T>
void Array<T>::deleteAt(int i)
{
	if (i < 0 || i >= _size) throw std::exception("Delete failure: ����� �� ������� �������");
	if (i>_count-1) std::cout << "������ �������!" << std::endl;

	if (i<_size-2)
	moveElementsLeft(i+1);
	_count--;
}

template <typename T>
bool Array<T>::find(T&& x, int& index)
{
	for (int i = 0; i < _count; i++)
			if (_data[i] == x)
			{
				index = i;
				return true;
			}
	return false;
}

