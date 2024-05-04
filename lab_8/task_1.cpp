#include <ctime>
#include <iostream>

const size_t EX_COUNT = 1000000;

template <typename T>
clock_t timeMeasureSum(T a, T b) {
    clock_t diff = 0;
    T res;
    clock_t start = clock();
    res = a + b;
    clock_t end = clock();
    (void)res;
    diff = end - start;
    return diff;
}

template <typename T>
clock_t timeMeasureMul(T a, T b) {
    clock_t diff = 0;
    T res;
    clock_t start = clock();
    res = a * b;
    clock_t end = clock();
    (void)res;
    diff = end - start;
    return diff;
}

template <typename T>
clock_t timeMeasureSumASM(T a, T b) {
    T res;
    clock_t start = clock();
    __asm__(
        "fld %1\n"  // Загрузить
        "fld %2\n"
        "faddp\n"
        "fstp %0\n"  // Выгрузить
        : "=m"(res)
        : "m"(a), "m"(b));
    clock_t end = clock();
    return end - start;
}

template <typename T>
clock_t timeMeasureMulASM(T a, T b) {
    T res;
    clock_t start = clock();
    __asm__(
        "fld %1\n"
        "fld %2\n"
        "fmulp\n"
        "fstp %0\n"
        : "=m"(res)
        : "m"(a), "m"(b));
    clock_t end = clock();
    return end - start;
}

template <typename T>
void measureExperiment(size_t count = 1000) {
    clock_t sumTime = 0.0, mulTime = 0.0, sumTimeASM = 0.0, mulTimeASM = 0.0;
    T first = 2627.3672, second = 8210.3417;
    for (size_t i = 0; i < count; ++i) {
        sumTime += timeMeasureSum(first, second);
        mulTime += timeMeasureMul(first, second);
        sumTimeASM += timeMeasureSumASM(first, second);
        mulTimeASM += timeMeasureMulASM(first, second);
    }
    std::cout << "Def: Sum time: " << sumTime << " Mul time: " << mulTime << std::endl;
    std::cout << "Asm: Sum time: " << sumTimeASM << " Mul time: " << mulTimeASM << std::endl;
}

int main() {
    std::cout << "float: " << std::endl;
    measureExperiment<double>(EX_COUNT);
    std::cout << "double: " << std::endl;
    measureExperiment<float>(EX_COUNT);
    return 0;
}