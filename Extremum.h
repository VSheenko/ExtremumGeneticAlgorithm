#ifndef EXTREMUMGENETICALGORITHM_EXTREMUM_H
#define EXTREMUMGENETICALGORITHM_EXTREMUM_H
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include <iostream>
#include <map>


class Extremum {
public:
    void GetExtremum(double (*function)(double, double));
private:
    static const int CHROMOSOME_SIGN_LENGTH = 1; // Знак числа
    static const int CHROMOSOME_INTEGER_PART = 6; // Целая часть числа
    static const int CHROMOSOME_FRACTIONAL_PART = 6; // Дробная часть числа

    // Общее кол-во генов для особи
    static const int GENE_LENGTH = (CHROMOSOME_SIGN_LENGTH + CHROMOSOME_INTEGER_PART + CHROMOSOME_FRACTIONAL_PART) * 2;

    static const int NUMBER_OF_GENERATION = 100000; // Максимальное кол-во поколений
    static const int INDIVIDUALS_NUMBER = 14; // Число особей в одном поколении

    double M_PI = 3.14159265358979323846;
    double LOCALE_RADIUS = 0.5; // Радиус для проверки на экспоненту
private:
    double (*function)(double, double);
    static std::vector<std::string> InitPopulation();
    double Fitness(std::string&);
    static std::vector<double> IndividualsToVec(std::string &individual);
    void SimulationOfLife(std::vector<std::string>&);
    void GetGenerationScore(std::vector<std::string>&, std::vector<double>&);
    static double SortPopulation(std::vector<std::string>&, std::vector<double>&);
    void SelectParent(std::vector<std::string>&, std::vector<double>&, std::vector<std::string>&);
    void CreateNewPopulation(std::vector<std::string>&, std::vector<std::string>&);
    std::string CrossParents(std::string&, std::string&);
    void mutation(std::vector<std::string>&);
    double ZeroFix(double);
};

#endif //EXTREMUMGENETICALGORITHM_EXTREMUM_H
