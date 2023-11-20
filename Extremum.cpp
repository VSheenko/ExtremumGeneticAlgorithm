//
// Created by vovan on 20.11.2023.
//

#include "Extremum.h"
#include <cmath>


/**
 *Самое начало алгоритма
 * @param function функция вида F(x, y), у которой необходим найти экстремум
 * @param progressDisplayFlag отображение дополнительных сообщений о поколениях
 * @return один из экстремум данной функции
 */
double Extremum::GetExtremum(double (*function)(double, double), bool progressDisplayFlag) {
    this->function = function;
    return 0;
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
    std::vector<double> coords = individualsToVec(individual);

    double x = coords[0];
    double y = coords[1];
    double z = function(x, y);

    double greatestCount = 0;
    double smallestCount = 0;

    double dx, dy, dz; // Координаты точки, лежащей на той самой окружности.

    // Точка выбирает с помощью угла a (тип альфа:3)
    double rad; // Представление угла в радианах
    for (int a = 0; a < 360; a++) {
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

    greatestCount /= 360;
    smallestCount /= 360;

    return std::max(greatestCount, smallestCount);
}

/**
 * Преобразует двоичную запись особи в ее десятичные эквиваленты
 * @param individual
 * @return Возвращает вектор с координатами {x, y}
 */
std::vector<double> Extremum::individualsToVec(std::string& individual) {
    double x = 0, y = 0;

    int indY; // индекс для цифр, принадлежащих хромосоме, которая определяет координату y
    int indX; // индекс для цифр, принадлежащих хромосоме, которая определяет координату x

    // целая часть абсолютного значения координат
    for (int i = 0; i <CHROMOSOME_INTEGER_PART; i++){
        indX = i + CHROMOSOME_SIGN_LENGTH;
        indY = indX + CHROMOSOME_SIGN_LENGTH + CHROMOSOME_INTEGER_PART + 1;

        x += (individual[indX] - '0') * pow(2, CHROMOSOME_INTEGER_PART - i);
        y += (individual[indY] - '0') * pow(2, CHROMOSOME_INTEGER_PART - i);
    }

    // Дробная часть абсолютного значения координат
    for (int i = 0; indX < CHROMOSOME_FRACTIONAL_PART; i++){
        indX = i + CHROMOSOME_SIGN_LENGTH + CHROMOSOME_INTEGER_PART;
        indY = indX + CHROMOSOME_SIGN_LENGTH + CHROMOSOME_INTEGER_PART + 1;

        x += 1 / ((individual[indX] - '0') * pow(2, CHROMOSOME_FRACTIONAL_PART - i));
        y += 1 / ((individual[indY] - '0') * pow(2, CHROMOSOME_FRACTIONAL_PART - i));
    }

    return {x, y};
}
