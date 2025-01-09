#include "Header.h"

Polynom::Polynom(unsigned int number) : number(number)
{
	size_t power = GetPower();

	for (size_t i = 0; i < power + 1; i++)
	{
		koef.push_back(number / static_cast<unsigned int>(std::pow(10, power - i)));
		number %= static_cast<unsigned int>(std::pow(10, power - i));
	}
}

std::string Polynom::ToString()
{
	std::stringstream buffer;

	for (size_t i = 0; i < koef.size(); i++)
	{
		buffer << koef[i] << "x^" << (koef.size() - i - 1);
		if (i != koef.size() - 1)
		{
			buffer << " + ";
		}
	}
	return buffer.str();
}

size_t Polynom::GetPower()
{
	std::ostringstream len;
	len << number;

	return len.str().size() - 1;
}

size_t Polynom::GetSize()
{
	return koef.size();
}

std::vector<unsigned int> Polynom::GetKoef()
{
	return koef;
}

Polynom Polynom::operator*(const Polynom& other)
{
	size_t resultPower = GetPower() * 2;
	Polynom result(0);

	result.koef.resize(resultPower + 1, 0);

	for (size_t i = 0; i < koef.size(); i++)
	{
		for (size_t j = 0; j < other.koef.size(); j++)
		{
			result.koef[i + j] += koef[i] * other.koef[j];
		}
	}

	return result;
}

Polynom Polynom::operator+(const Polynom& other)
{
	Polynom result(0);
	result.koef.resize(GetPower() + 1, 0);

	for (size_t i = 0; i < koef.size(); i++)
	{
		result.koef[i] = koef[i] + other.koef[i];
	}

	return result;
}

unsigned int Polynom::InDot(const unsigned int dot)
{
	unsigned int result = 0;

	for (size_t i = 0; i < koef.size(); i++)
	{
		result += koef[i] * pow(dot, koef.size() - i - 1);
	}

	return result;
}

std::vector<unsigned int> Polynom::Reverse()
{
	std::reverse(koef.begin(), koef.end());
	return koef;
}

std::ostream& operator<<(std::ostream& os, Polynom& polynom)
{
	os << polynom.ToString();
	return os;
}
