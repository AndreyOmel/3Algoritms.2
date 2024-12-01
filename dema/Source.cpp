#include<iostream>
double my_power(double val, int p) {
    if (p < 0) {
        return my_power(1 / val, -p); 
    }
    if (p == 0) {
        return 1;
    }
    if (p % 2 == 0) {
        return my_power(val * val, p / 2); 
    }
    else {
        return val * my_power(val * val, (p - 1) / 2); 
    }
}
int main() {

	return 0;
}