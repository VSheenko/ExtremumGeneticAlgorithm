#include <cstdlib>
#include <ctime>
#include <vector>

class GeneticAlgorithm {
private:
public:
    double GetExtremum(double (*function)(double, double), bool=false);
};