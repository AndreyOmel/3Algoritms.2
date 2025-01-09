#include <iostream>
#include <random>
using namespace std;

long long mod_pow(long long base, int exp, int mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
bool miller_rabin(int n) {
    int b[4] = { 3,5,7,11 };
    bool simple = true;
    // Представление n-1 = 2^s * d
    int s = 0;
    int r = n - 1;
    while (r % 2 == 0) {
        r /= 2;
        s++;

    }
    for (size_t i = 0; i < 4; i++) {
        int y = mod_pow(b[i], r, n);
        if (y % n != 1 and y % n != n - 1) {
            int j = 1;
            while (j < s and y % n != n - 1) {
                y = mod_pow(y, 2, n);
                if (y == 1) { 
                    simple = false; 
                    break;
                }
                j++;
            }
            if (y % n != n - 1) {
                simple = false;
            }
        }
    }
    return simple;
}
int jacobi(int a, int n) {
    if (n <= 0 || n % 2 == 0) return 0;
    a %= n;
    if (a == 0) return n == 1 ? 1 : 0;

    int result = 1;
    while (a != 0) {
        while (a % 2 == 0) {
            a /= 2;
            if (n % 8 == 3 || n % 8 == 5) {
                result = -result;
            }
        }

        swap(a, n);
        if (a % 4 == 3 && n % 4 == 3) {
            result = -result;
        }
        a %= n;
    }

    return n == 1 ? result : 0;
}
bool Ferma(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> uniformIntDistribution(2, n - 2);

    bool simple = true;
    for (size_t i = 0; i < 5; i++) {
        int b = uniformIntDistribution(gen);
        if (mod_pow(b, n - 1, n) != 1) {
            simple = false;

        }
    }
    return simple;
}
bool Sol_SHT(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> uniformIntDistribution(2, n - 2);

    bool simple = true;
    for (size_t i = 0; i < 5; i++) {
        int b = uniformIntDistribution(gen);
        int r = mod_pow(b, (n - 1) / 2, n);
        if (r != 1 && r != n - 1) {
            simple = false;

        }

        int s = jacobi(b, n);
        if (s == -1) {
            s = n - 1;
        }

        if (r != s) {
            simple = false;
            break;
        }
    }
    return simple;
}
int main() {
    int n = 127;
    // Метод Ферма
    cout << "Method Ferma: " << "Chislo " << n << " simple=" << Ferma(n)   << endl;

    // Метод Соловея-Штрассена
    cout << "Method Solovey: " << "Chislo " << n << " simple=" <<Sol_SHT(n)  << endl;
        
    //miller-rabin
    cout << "Method Miller-Rabin: " << "Chislo " << n << " simple=" << miller_rabin(n) << endl;
    return 0;
}
