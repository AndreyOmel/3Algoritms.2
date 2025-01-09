#include "..\Polynom\Header.h"
#include<algorithm>
#include<complex>

/**
* @brief ���������.
* @param n ����� �� ����.
* @return ��������� �����.
*/
int fact(int n);

/**
* @brief ������� ��� ���������� ������� �������� �������� � �����.
* @param p �������.
* @param k �������� �����.
* @param i �������� ������.
* @return ������� ��������.
*/
size_t Delta(Polynom p, unsigned int k, size_t i);

/**
* @brief ������ �������������� �����.
* @param poly ����������� ��������.
* @param invert ��������.
*/
void fft(std::vector<std::complex<double>>& poly, bool invert);

/**
* @brief ����� � �������� ��������.
* @param num �������� �����.
* @return ������ �������� ����� � 2-� �������.
*/
std::vector<unsigned int> IntToBinary(unsigned int num);

/**
* @brief �������� ����� � ����������.
* @param binary �������� ����� � 2-� �������.
* @return �������� ����� � 10-� �������.
*/
unsigned int BinaryToInt(const std::vector<unsigned int>& binary);

/**
* @brief ��������� ���������.
* @param u ������������ �������� u.
* @param v ������������ �������� v.
* @return ������������ ����������� ��������.
*/
std::vector<std::complex<double>> Multiply(const std::vector<std::complex<double>>& u, std::vector<std::complex<double>>& v);

/**
* @brief ����� � �������.
* @param num ����� � ���� �������.
* @return ������ ���������� �������������.
*/
std::vector<std::complex<double>> NumberToPoly(const std::vector<unsigned int>& num);

/**
* @brief �������������� �������� � �����.
* @param poly ������ ������������� ��������.
* @return ����� � ���� �������.
*/
std::vector<unsigned int> PolyToNumber(const std::vector<std::complex<double>>& poly);

/**
* @brief ����� ��������.
* @param a ������ �����.
* @param b ������ �����.
* @return ������������ �����.
*/
size_t methodKarazuba(const unsigned int a, const unsigned int b);

/**
* @brief ����� �����-����.
* @param u ������ �����.
* @param v ������ �����.
* @return ������������ �����.
*/
size_t methodToomKuk(const unsigned int u, const unsigned int v);

/**
* @brief ����� �������-���������.
* @param u ������ �����.
* @param v ������ �����.
* @return ������������ �����.
*/
size_t methodSchonhageStrassen(const unsigned int u, const unsigned int v);


int main()
{
	setlocale(LC_ALL, "Rus");

	int a = 11;
	int b = 36;

	std::cout << "�����: " << a << " " << b << std::endl;
	std::cout << "����� ��������: " << methodKarazuba(a, b) << std::endl;
	std::cout << "����� �����-����: " << methodToomKuk(a, b) << std::endl;
	std::cout << "����� �������-���������: " << methodSchonhageStrassen(a, b) << std::endl;

	return 0;
}

int fact(int n)
{
	if (n < 0)
		return 0;
	if (n == 0)
		return 1;
	if (n > 0)
		return n * fact(n - 1);
}

size_t Delta(Polynom p, unsigned int k, size_t i)
{
	if ((k == 0))
		return p.InDot(0);
	if (i == 0)
		return p.InDot(k) - p.InDot(k - 1);

	return Delta(p, k, i - 1) - Delta(p, k - 1, i - 1);
}

void fft(std::vector<std::complex<double>>& poly, bool invert)
{
	int n = poly.size();
	if (n <= 1)
		return;
	std::vector<std::complex<double>> a0(n / 2), a1(n / 2);

	for (size_t i = 0; 2 * i < n; i++)
	{
		a0[i] = poly[2 * i];
		a1[i] = poly[2 * i + 1];
	}

	fft(a0, invert);
	fft(a1, invert);

	double ang = 2 * 3.14 / n * (invert ? -1 : 1);
	std::complex<double> w(1), wn(cos(ang), sin(ang));

	for (size_t i = 0; 2 * i < n; i++)
	{
		poly[i] = a0[i] + w * a1[i];
		poly[i + n / 2] = a0[i] - w * a1[i];
		if (invert)
		{
			poly[i] /= 2;
			poly[i + n / 2] /= 2;
		}
		w *= wn;
	}
}

std::vector<unsigned int> IntToBinary(unsigned int num)
{

	std::vector<unsigned int> binary;

	if (num == 0)
	{
		binary.push_back(0);
	}
	else
	{
		while (num > 0)
		{
			binary.push_back(num % 2);
			num /= 2;
		}
	}


	reverse(binary.begin(), binary.end());

	return binary;

}

unsigned int BinaryToInt(const std::vector<unsigned int>& binary)
{
	int decimal = 0;
	int power = 1;


	for (int i = binary.size() - 1; i >= 0; i--)
	{
		if (binary[i] == 1)
		{
			decimal += power;
		}
		power *= 2;
	}

	return decimal;
}

std::vector<std::complex<double>> Multiply(const std::vector<std::complex<double>>& u, std::vector<std::complex<double>>& v)
{
	std::vector<std::complex<double>> fa(u.begin(), u.end()), fb(v.begin(), v.end());
	size_t n = 1;

	while (n < u.size() + v.size()) n <<= 1;
	fa.resize(n);
	fb.resize(n);

	fft(fa, false);
	fft(fb, false);

	for (size_t i = 0; i < n; i++)
	{
		fa[i] *= fb[i];
	}

	fft(fa, true);

	return fa;
}

std::vector<std::complex<double>> NumberToPoly(const std::vector<unsigned int>& num)
{
	std::vector<std::complex<double>> result(num.size());
	for (size_t i = 0; i < num.size(); ++i)
	{
		result[i] = num[num.size() - 1 - i];
	}
	return result;
}

std::vector<unsigned int> PolyToNumber(const std::vector<std::complex<double>>& poly)
{
	std::vector<unsigned int> result(poly.size());
	for (size_t i = 0; i < poly.size(); ++i)
	{
		result[i] = round(poly[i].real());
	}


	for (size_t i = 0; i < result.size(); ++i)
	{
		if (result[i] >= 2)
		{
			if (i + 1 == result.size()) result.push_back(0);
			result[i + 1] += result[i] / 2;
			result[i] %= 2;
		}
	}


	while (result.size() > 1 && result.back() == 0)
	{
		result.pop_back();
	}

	reverse(result.begin(), result.end());
	return result;
}

size_t methodKarazuba(const unsigned int a, const unsigned int b)
{
	Polynom pol1(a);
	Polynom pol2(b);

	Polynom result = pol1 * pol2;

	return result.InDot(10);
}

size_t methodToomKuk(const unsigned int u, const unsigned int v)
{
	Polynom ux(u);
	Polynom vx(v);
	Polynom wx = ux * vx;

	std::vector<unsigned int> res;
	res.resize(ux.GetSize() * 2, 0);

	for (size_t i = 0; i < res.size(); i++)
	{
		res[i] = Delta(wx, i, i - 1) / fact(i);
	}

	unsigned int result = 0;

	for (size_t i = 0; i < res.size(); i++)
	{
		unsigned int term = res[i];

		for (size_t j = 0; j < i; j++)
		{
			term *= (10 - j);
		}

		result += term;
	}

	return result;
}

size_t methodSchonhageStrassen(const unsigned int u, const unsigned int v)
{
	std::vector<unsigned int> ub = IntToBinary(u), vb = IntToBinary(v);
	std::vector<std::complex<double>> polyU = NumberToPoly(ub), polyV = NumberToPoly(vb);
	std::vector<std::complex<double>> resultPoly = Multiply(polyU, polyV);

	unsigned int result = BinaryToInt(PolyToNumber(resultPoly));

	return result;
}