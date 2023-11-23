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



int main() {
    std::srand(std::time(NULL));
    Extremum extremum;


    extremum.GetExtremum(function2);
    std::cout << "Алгоритм завершил работу" << std::endl;
    return 0;
}

