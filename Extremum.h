//
// Created by vovan on 20.11.2023.
//

#ifndef EXTREMUMGENETICALGORITHM_EXTREMUM_H
#define EXTREMUMGENETICALGORITHM_EXTREMUM_H
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include <iostream>


class Extremum {
public:
    double GetExtremum(double (*function)(double, double), bool = false);
private:
    static const int GENE_LENGTH = 20;
    static const int CHROMOSOME_SIGN_LENGTH = 1;
    static const int CHROMOSOME_INTEGER_PART = 3;
    static const int CHROMOSOME_FRACTIONAL_PART = 6;

    static const int NUMBER_OF_GENERATION = 100000;
    static const int INDIVIDUALS_NUMBER = 14;

    double M_PI = 3.14159265358979323846;
    double LOCALE_RADIUS = 0.2;
private:
    double (*function)(double, double);
    static std::vector<std::string> InitPopulation();
    double Fitness(std::string&);
    static std::vector<double> IndividualsToVec(std::string &individual);
    void SimulationOfLife(std::vector<std::string>&);
    void GetGenerationScore(std::vector<std::string>&, std::vector<double>&);
    static void SortPopulation(std::vector<std::string>&, std::vector<double>&);
    void SelectParent(std::vector<std::string>&, std::vector<double>&, std::vector<std::string>&);
    void CreateNewPopulation(std::vector<std::string>&, std::vector<std::string>&);
    std::string CrossParents(std::string&, std::string&);
    std::string CrossParents2(std::string&, std::string&);
    void mutation(std::vector<std::string>&);


};


#endif //EXTREMUMGENETICALGORITHM_EXTREMUM_H
