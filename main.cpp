#pragma ide diagnostic ignored "cert-msc51-cpp"

#include <iostream>
#include <cmath>
#include "Extremum.h"

double function (double x, double y) {
    return std::pow(x, 3) + 3*x*std::pow(y, 2) - 15*x - 12*y;
}

double function2(double x, double y) {
    return std::pow(x, 2) + x*y + 2*std::pow(y, 2) - x - 4*y;
}

double function3(double x, double y) { // не работает
    return std::pow(x - 1, 4) - std::pow(y + 2, 4);
}

double function4(double x, double y){
    return std::pow(x, 2)*std::pow(y, 2)*(1 - x - y);
}
int main() {
    std::srand(std::time(NULL));
    Extremum extremum;


    extremum.GetExtremum(function);
    std::cout << "The End!" << std::endl;
    return 0;
}

