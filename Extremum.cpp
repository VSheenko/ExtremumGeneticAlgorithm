#include "Extremum.h"

/**
 *Самое начало алгоритма
 * @param function функция вида F(x, y), у которой необходим найти экстремум
 * @param progressDisplayFlag отображение дополнительных сообщений о поколениях
 * @return один из экстремум данной функции
 */
void Extremum::GetExtremum(double (*function)(double, double)) {
    this->function = function;

    std::vector<std::string> population = InitPopulation();
    SimulationOfLife(population);
}

/**
 * Случайным образом создает создает первую популяцию, состоящую из определенного числа особей
 * @return вектор, состоящий из особей со случайным набором генов
 */
std::vector<std::string> Extremum::InitPopulation() {
    std::vector<std::string> population(INDIVIDUALS_NUMBER);

    std::string individual;
    for (int i = 0; i < INDIVIDUALS_NUMBER; i++) {
        individual.clear();

        for (int j = 0; j < GENE_LENGTH; j++) {
            individual += std::to_string(std::rand() % 2);
        }

        population[i] = individual;
    }

    return population;
}

/**
 * Фитнес-функция, которая определяет меру приспособленности особи.
 * Рисуем окружность вокруг координаты особи и смотрим какие точки больше, какие меньше.
 * Возвращаем наибольшую долю (либо т. максимума, либо т. минимума).
 * @param individual конкретная особь
 */
double Extremum::Fitness(std::string& individual) {
    std::vector<double> coords = IndividualsToVec(individual);

    double x = coords[0];
    double y = coords[1];
    double z = function(x, y);

    double greatestCount = 0;
    double smallestCount = 0;

    double dx, dy, dz; // Координаты точки, лежащей на той самой окружности.

    // Точка выбирает с помощью угла a (тип альфа:3)
    double rad; // Представление угла в радианах
    for (int a = 0; a < 360; a+=3) {
        rad = a * (M_PI / 180);
        dx = x + std::sin(rad) * LOCALE_RADIUS;
        dy = y + std::cos(rad) * LOCALE_RADIUS;
        dz = function(dx, dy);

        if (z == dz) {
            greatestCount++;
            smallestCount++;
        }
        else if (z > dz) greatestCount++;
        else if (z < dz) smallestCount++;
    }

    greatestCount /= 120;
    smallestCount /= 120;

    return std::max(greatestCount, smallestCount);
}

/**
 * Преобразует двоичную запись особи в ее десятичные эквиваленты
 * @param individual
 * @return Возвращает вектор с координатами {x, y}
 */
std::vector<double> Extremum::IndividualsToVec(std::string& individual) {
    double x = 0, y = 0;

    int indY; // индекс для цифр, принадлежащих хромосоме, которая определяет координату y
    int indX; // индекс для цифр, принадлежащих хромосоме, которая определяет координату x

    // целая часть абсолютного значения координат
    for (int i = 0; i <CHROMOSOME_INTEGER_PART; i++){
        indX = i + CHROMOSOME_SIGN_LENGTH;
        indY = indX + CHROMOSOME_INTEGER_PART + CHROMOSOME_FRACTIONAL_PART + CHROMOSOME_SIGN_LENGTH;

        x += (individual[indX] - '0') * pow(2, CHROMOSOME_INTEGER_PART - i - 1);
        y += (individual[indY] - '0') * pow(2, CHROMOSOME_INTEGER_PART - i - 1);
    }

    // Дробная часть абсолютного значения координат
    for (int i = 0; i < CHROMOSOME_FRACTIONAL_PART; i++){
        indX = i + CHROMOSOME_SIGN_LENGTH + CHROMOSOME_INTEGER_PART;
        indY = indX + CHROMOSOME_INTEGER_PART + CHROMOSOME_FRACTIONAL_PART + CHROMOSOME_SIGN_LENGTH;

        if (individual[indX] != '0')
            x += 1.0 / pow(2,  i + 1);
        if (individual[indY] != '0')
            y += 1.0 / pow(2, i + 1);
    }

    if (individual[0] == '1') x = -x;
    if (individual[CHROMOSOME_SIGN_LENGTH + CHROMOSOME_INTEGER_PART + CHROMOSOME_FRACTIONAL_PART] =='1') y = -y;

    return {x, y};
}

void Extremum::SimulationOfLife(std::vector<std::string>& curPopulation) {
    std::vector<double> generationScore(INDIVIDUALS_NUMBER);
    std::vector<std::string> parents(INDIVIDUALS_NUMBER / 2);
    std::map<std::string, int> alreadyFoundCoords;
    std::string key;
    std::vector<double> extremumCoords(2);

    double lastBest = -1;
    double curBest = 0;

    int repeatCount = 0;
    for (int i = 1; i <= NUMBER_OF_GENERATION; i++) {
        GetGenerationScore(curPopulation, generationScore);
        curBest = SortPopulation(curPopulation, generationScore);



        if (curBest == 1) {
            extremumCoords = IndividualsToVec(curPopulation[0]);
            extremumCoords[0] = round(std::abs(extremumCoords[0])) * (extremumCoords[0] < 0 ? -1 : 1);
            extremumCoords[1] = round(std::abs(extremumCoords[1])) * (extremumCoords[1] < 0 ? -1 : 1);

            key = std::to_string(extremumCoords[0]) + " " + std::to_string(extremumCoords[1]);
            if (alreadyFoundCoords.count(key) == 0) {
                alreadyFoundCoords[key] = 1;
                std::cout << key << '\n';
            }

            curPopulation = InitPopulation();
            curBest = 0;
            continue;
        }

        if (std::fabs(curBest - lastBest) < std::numeric_limits<double>::epsilon()) repeatCount += 1;
        else repeatCount = 0;

        if (repeatCount >= 3000) {
            curPopulation = InitPopulation();
            continue;
        }
        lastBest = curBest;

        SelectParent(curPopulation, generationScore, parents);
        CreateNewPopulation(parents, curPopulation);
        mutation(curPopulation);
    }
}

void Extremum::GetGenerationScore(std::vector<std::string> &population, std::vector<double>& generationScore) {
    for (int i = 0; i < population.size(); i++) {
        generationScore[i] = Fitness(population[i]);
    }
}

double Extremum::SortPopulation(std::vector<std::string> &population, std::vector<double> &generationScore) {
    assert(population.size() == generationScore.size() && "population.size() == generationScore.size()");
    double maxScore = generationScore[generationScore.size() - 1];

    for (int i = 0; i < generationScore.size() - 1; i++)
    {
        maxScore = std::max(maxScore, generationScore[i]);
        int max_index = i;

        for (int j = i + 1; j < generationScore.size(); j++)
        {
            if (generationScore[j] > generationScore[max_index])
            {
                max_index = j;
            }
        }
        if (max_index != i)
        {
            std::swap(generationScore[i], generationScore[max_index]);
            std::swap(population[i], population[max_index]);
        }
    }

    return round(maxScore * 100) / 100;
}

void Extremum::CreateNewPopulation(std::vector<std::string> &parents, std::vector<std::string> &newPopulation) {
    for (int i = 0; i < INDIVIDUALS_NUMBER / 2; i++) {
        int first = std::rand() % 7;
        int second = std::rand() % 7;

        std::string child1 = CrossParents(parents[first], parents[second]);
        std::string child2 = CrossParents(parents[second], parents[first]);


        newPopulation[2*i] = child1;
        newPopulation[2*i + 1] = child2;
    }
}

std::string Extremum::CrossParents(std::string &p1, std::string &p2) {
    int index = std::rand() % GENE_LENGTH;
    std::string child = p1.substr(0, index) + p2.substr(index, GENE_LENGTH - index);

    return child;
}

void Extremum::mutation(std::vector<std::string> &population) {
    int index = std::rand() % 5;
    int border1_of_mutation = std::rand() % GENE_LENGTH;
    int border2_of_mutation = std::rand() % GENE_LENGTH;

    if (border1_of_mutation - border2_of_mutation != 0 && abs(border1_of_mutation - border2_of_mutation) < 10) {
        for (int i = std::min(border1_of_mutation, border2_of_mutation); i < std::max(border1_of_mutation, border2_of_mutation); i++) {
            if (population[index][i] == '0') {
                population[index][i] = '1';
            }
            else {
                population[index][i] = '0';
            }
        }
    }
}

void Extremum::SelectParent(std::vector<std::string> &population, std::vector<double> &generationScore, std::vector<std::string> &parents) {
    assert(parents.size() == INDIVIDUALS_NUMBER / 2 && "parents.size() == INDIVIDUALS_NUMBER");

    for (int i = 0; i < INDIVIDUALS_NUMBER / 2; i++){
        parents[i] = population[i];
    }
}
