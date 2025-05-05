#pragma once
#include <memory>

template <typename T>
class DataManager // Абстрактный класс, чтобы было удобно выбрать какой способ сохранения мы используем
{
public:
	virtual void add(T&&) = 0;
	virtual void deleteAt(unsigned int i) = 0;
	virtual T& get(unsigned int i) = 0;
	virtual unsigned int getCount() const = 0;
	virtual ~DataManager() = default;
	virtual std::unique_ptr<DataManager<T>>clone() const = 0;
};