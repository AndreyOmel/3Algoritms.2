#include<iostream> 
#include<random> 
#include<exception>

/**
* @brief ��������� �����.
* @param a ������ �����.
* @param b ������ �����.
* @param mod ������.
* @return ������������ �� ������.
*/
unsigned long Mul(unsigned long a, unsigned long b, unsigned long mod);

/**
* @brief ���������� � ������� �� ������.
* @param a ������ �����.
* @param b ������ �����.
* @param mod ������.
* @return ����� � ������� �� ������.
*/
unsigned long Pow(unsigned long a, unsigned long b, unsigned long mod);

/**
* @brief ���������� ����.
* @param a ������ �����.
* @param b ������ �����.
* @return ���.
*/
unsigned long GSD(unsigned long a, unsigned long b);

/**
* @brief ����� ����� �����.
* @param x �����.
* @return ����� �����.
*/
unsigned long Len(unsigned long x);

/**
* @brief ���� ����� �� ��������.
* @param n �����.
* @return True or False.
*/
bool TestFerma(unsigned long n);

/**
* @brief ��������� ������� ����� �� �����.
* @param t ����� ������ �����.
* @param q ������� �����.
* @return ������� ����� ������� �����.
*/
unsigned long Gost(unsigned long t, unsigned long q);

int main()
{
    setlocale(LC_ALL, "Rus");
    try
    {
        unsigned long t, q;
        std::cout << "������� ����� �����: ";
        std::cin >> t;
        std::cout << "������� ������� ����� � ������ " << t / 2 << ": ";
        std::cin >> q;

        unsigned long p = Gost(t, q);
        std::cout << "������� ������� �����: " << p;
        if (TestFerma(p))
            std::cout << " - ������� �����" << std::endl;
    }
    catch (std::exception& error)
    {
        std::cerr << error.what();
        return 1;
    }

    return 0;
}

unsigned long Mul(unsigned long a, unsigned long b, unsigned long mod)
{
    if (b == 1)
        return a;
    if (b % 2 == 0)
    {
        unsigned long t = Mul(a, b / 2, mod);
        return (2 * t) % mod;
    }
    return (Mul(a, b - 1, mod) + a) % mod;
}

unsigned long Pow(unsigned long a, unsigned long b, unsigned long mod)
{
    if (b == 0)
        return 1;
    if (b % 2 == 0)
    {
        unsigned long t = Pow(a, b / 2, mod);
        return Mul(t, t, mod) % mod;
    }
    return (Mul(Pow(a, b - 1, mod), a, mod)) % mod;
}

unsigned long GSD(unsigned long a, unsigned long b)
{
    if (b == 0)
        return a;
    return GSD(b, a % b);
}

unsigned long Len(unsigned long x)
{
    unsigned long len = 0;
    if (x == 0)
        return 1;
    while (x)
    {
        len++;
        x /= 10;
    }
    return len;
}

bool TestFerma(unsigned long n)
{
    if (n <= 3)
        throw std::logic_error("����� ������ ���� ������ 3");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long> uniformIntDistrubution(2, n - 2);

    if (n == 2)
        return true;

    for (size_t i = 0; i < 100; i++)
    {
        unsigned long a = uniformIntDistrubution(gen);
        if (GSD(a, n) != 1)
            return false;
        if (Pow(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

unsigned long Gost(unsigned long t, unsigned long q)
{
    if (!TestFerma(q))
        throw std::logic_error("������ ���� �������");
    if (t / 2 != Len(q))
        throw std::logic_error("�� �� ����� �����");

    unsigned long N = pow(10, t - 1) / q + (Pow(10, t - 1, q) ? 1 : 0);
    if (N % 2 == 0)
        ++N;

    unsigned long u = 0;
    while (true)
    {
        unsigned long p = q * (N + u) + 1;
        if (p >= pow(10, t))
        {
            ++N;
            u = 0;
            continue;
        }

        if (TestFerma(p))
        {
            unsigned long pow2modp = 1;
            for (unsigned long i = 0; i < (p - 1); ++i)
            {
                pow2modp = (pow2modp * 2) % p;
            }
            if (pow2modp == 1)
            {
                unsigned long powerMod = 1;
                for (unsigned long i = 0; i < (N + u); ++i)
                {
                    powerMod = (powerMod * 2) % p;
                }
                if (powerMod != 1)
                {
                    return p;
                }
            }
        }
        u += 2;
    }
}
