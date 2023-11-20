//
// Created by vovan on 20.11.2023.
//

#ifndef EXTREMUMGENETICALGORITHM_EXTREMUM_H
#define EXTREMUMGENETICALGORITHM_EXTREMUM_H
#include <vector>
#include <string>

#define GENE_LENGTH 20
#define CHROMOSOME_SIGN_LENGTH 1
#define CHROMOSOME_INTEGER_PART 3
#define CHROMOSOME_FRACTIONAL_PART 6

#define INDIVIDUALS_NUMBER 14

#define M_PI 3.14159265358979323846
#define LOCALE_RADIUS 0.5

class Extremum {
public:
    double GetExtremum(double (*function)(double, double), bool = false);
private:
    double (*function)(double, double);
    std::vector<std::string> InitPopulation();
    double Fitness(std::string&);
    static std::vector<double> individualsToVec(std::string &individual);
};


#endif //EXTREMUMGENETICALGORITHM_EXTREMUM_H
