#include <cassert>
#include <cmath>
#include <iostream>

const double EPS = 1e-9;

double func(double x) { return 2 * std::sin(x * x - 5); }

double findRoot(double start, double stop, int count) {
    double fStart = func(start), fStop = func(stop);
    double mid, fMid;
    assert(fStart * fStop <= 0);

    for (int i = 0; i < count; ++i) {
        mid = (start + stop) / 2.0;

        fMid = func(mid);

        // Если нашли корень
        if (fabs(fMid) < EPS)
            return mid;

        if (fStart * fMid < 0) {
            stop = mid;
        } else {
            start = mid;
            fStart = fMid;
        }
    }

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

double findRootAsm(double start, double stop, int count) {
    const int two = 2.0;
    for (int i = 0; i < count; ++i) {
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
        if (fabs(fMid) < EPS)
            return mid;
        __asm__(
            "fld %2\n"  // Загружаем fStart
            "fld %5\n"  // Загрузить fMid
            "fmulp\n"   // Умножаем fStart и fMid
            "fldz\n"    // Загрузить ноль
            "fcom\n"    // Сравнить результат с нулем
            "fstsw ax\n"    // Загрузить маску в AX
            "sahf\n"    // Применить маску из AX к флагам

            "ja greater\n"  // Если флаг C1 установлен в 0, перейти к метке greater

            "less:\n"
            "fstp %0\n" // Обновляем start
            "fstp %1\n" // Обновляем stop
            "fld %4\n"  // Загрузить значение mid
            "fstp %0\n" // Сохранить mid в start
            "fld %5\n"  // Загрузить значение fMid
            "fstp %2\n" // Сохранить в fStart
            "fld %7\n"
            "fstp %1\n"
            "jmp end\n" // Перейти к концу

            "greater:\n"
            "fstp %0\n"  // Обновляем start
            "fstp %1\n"  // Обновляем stop
            "fld %4\n"   // Загрузить значение mid
            "fstp %1\n"  // Сохранить mid в stop
            "fld %5\n"   // Загрузить значение fMid
            "fstp %3\n"  // Сохранить в fStop
            "fld %6\n"
            "fstp %0\n"

            "end:\n"
            : "=m"(start), "=m"(stop), "=m"(fStart), "=m"(fStop)
            : "m"(mid), "m"(fMid), "m"(a_s), "m"(b_s)
            : "%ax"  // Указываем, что мы используем AX
        );
    }
    return (stop + start) / 2.0;
}

const double START = 1.;
const double STOP = 1.5;
const int COUNT = 10;

int main() {
    std::cout << "Root by default func: " << findRoot(START, STOP, COUNT) << std::endl;
    std::cout << "Root by asm func: " << findRootAsm(START, STOP, COUNT) << std::endl;
    return 0;
}