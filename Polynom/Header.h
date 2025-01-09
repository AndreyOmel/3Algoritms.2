#pragma once
#include<iostream>
#include<vector>
#include<sstream>

/**
* @brief Класс полиномов.
*/
class Polynom
{
public:

	/**
	* @brief Конструктор класса.
	* @param number Число на вход.
	* @return Полином из числа.
	*/
	Polynom(unsigned int number);

	/**
	* @brief Метод преобразования в строку.
	* @return Полином в строку.
	*/
	std::string ToString();

	/**
	* @brief Геттер для степени полинма.
	* @return Степень полинома.
	*/
	size_t GetPower();

	/**
	* @brief Геттер для размера.
	* @return Размер полинома.
	*/
	size_t GetSize();

	/**
	* @brief Геттер для вектора коэффициентов.
	* @return Вектор коэффициентов.
	*/
	std::vector<unsigned int> GetKoef();

	/**
	* @brief Переопределения умножения.
	* @param other Полином.
	* @return Произведение полиномов.
	*/
	Polynom operator*(const Polynom& other);

	/**
	* @brief Переопределние сложения.
	* @param other Полином.
	* @return Сумма полиномов.
	*/
	Polynom operator+(const Polynom& other);

	/**
	* @brief Метод нахождения значения в точке.
	* @param dot Точка.
	* @return Значение в точке.
	*/
	unsigned int InDot(const unsigned int dot);

	/**
	* @brief Метод для переворота коэффициентов полинома.
	* @return Коэффициенты полинма в обратном порядке.
	*/
	std::vector<unsigned int> Reverse();

	/**
	* @brief Переопредление оператора вывода.
	* @param os Поток вывода.
	* @param polynom Полином.
	* @return Вывод в консоль.
	*/
	friend std::ostream& operator<<(std::ostream& os, Polynom& polynom);
private:
	unsigned int number;
	std::vector<unsigned int> koef;
};