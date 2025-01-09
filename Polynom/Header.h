#pragma once
#include<iostream>
#include<vector>
#include<sstream>

/**
* @brief ����� ���������.
*/
class Polynom
{
public:

	/**
	* @brief ����������� ������.
	* @param number ����� �� ����.
	* @return ������� �� �����.
	*/
	Polynom(unsigned int number);

	/**
	* @brief ����� �������������� � ������.
	* @return ������� � ������.
	*/
	std::string ToString();

	/**
	* @brief ������ ��� ������� �������.
	* @return ������� ��������.
	*/
	size_t GetPower();

	/**
	* @brief ������ ��� �������.
	* @return ������ ��������.
	*/
	size_t GetSize();

	/**
	* @brief ������ ��� ������� �������������.
	* @return ������ �������������.
	*/
	std::vector<unsigned int> GetKoef();

	/**
	* @brief ��������������� ���������.
	* @param other �������.
	* @return ������������ ���������.
	*/
	Polynom operator*(const Polynom& other);

	/**
	* @brief �������������� ��������.
	* @param other �������.
	* @return ����� ���������.
	*/
	Polynom operator+(const Polynom& other);

	/**
	* @brief ����� ���������� �������� � �����.
	* @param dot �����.
	* @return �������� � �����.
	*/
	unsigned int InDot(const unsigned int dot);

	/**
	* @brief ����� ��� ���������� ������������� ��������.
	* @return ������������ ������� � �������� �������.
	*/
	std::vector<unsigned int> Reverse();

	/**
	* @brief �������������� ��������� ������.
	* @param os ����� ������.
	* @param polynom �������.
	* @return ����� � �������.
	*/
	friend std::ostream& operator<<(std::ostream& os, Polynom& polynom);
private:
	unsigned int number;
	std::vector<unsigned int> koef;
};