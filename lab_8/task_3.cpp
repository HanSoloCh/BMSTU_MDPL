#include <cassert>
#include <cmath>
#include <iostream>

const double EPS = 1e-9;

double func(double x) { return 2 * std::sin(x * x - 5); }

double findRoot(double start, double stop) {
    double fStart = func(start), fStop = func(stop);
    double mid, fMid;
    assert(fStart * fStop <= 0);

    do {
        mid = (start + stop) / 2.0;

        fMid = func(mid);

        if (fStart * fMid < 0) {
            stop = mid;
        } else {
            start = mid;
            fStart = fMid;
        }
    } while (fabs(stop - start) > EPS);

    return (start + stop) / 2.0;
}

double funcAsm(double x) {
    double res;
    const int addNum = 5;
    __asm__(
        "fld %1\n"  // Загружаем значение x
        "fld %1\n"  // Загружаем значение x
        "fmulp\n"   // x^2
        "fild %2\n" // Загружаем 5
        "fsubp\n"   // x^2 - 5
        "fsin\n"    // sin(x^2 - 5)
        "fstp %0\n" // Сохраняем результат в переменную res
        : "=m"(res) // Выходной параметр
        : "m"(x), "m"(addNum)   // Входные параметры
    );
    return res;
}

double findRootAsm(double start, double stop) {
    const int two = 2.0;
    do {
        double fStart = funcAsm(start), fStop = funcAsm(stop);
        double mid, fMid;
        double a_s = start, b_s = stop;
        __asm__(
            "fld %1\n"  // Загружаем start
            "fld %2\n"  // Загружаем stop
            "faddp\n"   // Сложить a и b
            "fild %3\n" // Загружаем 2
            "fdivp\n"   // (a + b) / 2
            "fstp %0\n" // Сохраняем результат в mid
            : "=m"(mid) // Выходное значение
            : "m"(start), "m"(stop), "m"(two)   // Выходные значения
        );

        fMid = funcAsm(mid);
        __asm__(
            "fld %2\n"  // Загружаем fStart
            "fld %5\n"  // Загрузить fMid
            "fmulp\n"   // Умножаем fStart и fMid
            "fldz\n"    // Загрузить ноль
            "fcom\n"    // Сравнить результат с нулем
            "fstsw ax\n"    // Сохранить регистр статуса FPU в AX
            "sahf\n"    // Применить флаги условия к регистру флагов процессора

            "ja greater\n"  // Если флаг C1 установлен в 0, перейти к метке greater

            "less:\n"
            "fstp %0\n" // Обновляем start
            "fstp %1\n" // Обновляем stop
            "fld %4\n"  // Загрузить значение mid
            "fstp %0\n" // Сохранить mid в start
            "fld %5\n"  // Загрузить значение fMid
            "fstp %2\n" // Сохранить в fStart
            "fld %7\n"  // tmp-выгруз в stop
            "fstp %1\n"
            "jmp end\n" // Перейти к концу

            "greater:\n"
            "fstp %0\n"  // Обновляем start
            "fstp %1\n"  // Обновляем stop
            "fld %4\n"   // Загрузить значение mid
            "fstp %1\n"  // Сохранить mid в stop
            "fld %5\n"   // Загрузить значение fMid
            "fstp %3\n"  // Сохранить в fStop
            "fld %6\n"   // tmp-выгруз в start
            "fstp %0\n"

            "end:\n"
            : "=m"(start), "=m"(stop), "=m"(fStart), "=m"(fStop)  // Выходные значения (a и b)
            : "m"(mid), "m"(fMid), "m"(a_s), "m"(b_s)      // Входные значения (c, fc)
            : "%ax"  // Указываем, что мы используем AX
        );
    } while (fabs(stop - start) > EPS);
    return (stop + start) / 2.0;
}

const double START = 0.;
const double STOP = 2.;

int main() {
    std::cout << "Root by default func: " << findRoot(START, STOP) << std::endl;
    std::cout << "Root by asm func: " << findRootAsm(START, STOP) << std::endl;
    return 0;
}