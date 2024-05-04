#include <math.h>

#include <iostream>
#include <iomanip>

double getAsmPi() {
    double pi;
    __asm__(
        "fldpi\n"
        "fstp %0\n"
        : "=m"(pi));
    return pi;
}

double asmSin(double x) {
    double res;
    __asm__(
        "fld %1\n"
        "fsin\n"
        "fstp %0\n"
        : "=m"(res)
        : "m"(x));
    return res;
}

const double PI = 3.14;
const double B_PI = 3.141596;
const double ASM_PI = getAsmPi();

void measureDefaultSin() {
    std::cout << std::setprecision(20);
    std::cout << "| Compile version of sin(PI) (should be 0) |\n";
    std::cout << "|------------------------------------------|\n";
    std::cout << "| 3.14     | " << std::sin(PI) << "      |\n";
    std::cout << "| 3.141596 | " << std::sin(B_PI) << "    |\n";
    std::cout << "| ASM PI   | " << std::sin(ASM_PI) << "     |\n" << std::endl;
    std::cout << "| Compile version of sin(PI / 2) (should be 1) |\n";
    std::cout << "|----------------------------------------------|\n";
    std::cout << "| 3.14 / 2     | " << std::sin(PI / 2) << "        |\n";
    std::cout << "| 3.141596 / 2 | " << std::sin(B_PI / 2) << "        |\n";
    std::cout << "| ASM PI / 2   | " << std::sin(ASM_PI / 2) << "                             |\n";
    std::cout << std::endl;
    std::cout << std::defaultfloat;
}

void measureAsmSin() {
    std::cout << std::setprecision(20);
    std::cout << "| Preproc version of sin(PI) (should be 0) |\n";
    std::cout << "|------------------------------------------|\n";
    std::cout << "| 3.14     | " << asmSin(PI) << "      |\n";
    std::cout << "| 3.141596 | " << asmSin(B_PI) << "    |\n";
    std::cout << "| ASM PI   | " << asmSin(ASM_PI) << "     |\n" << std::endl;
    std::cout << "| Preproc version of sin(PI / 2) (should be 1) |\n";
    std::cout << "|----------------------------------------------|\n";
    std::cout << "| 3.14 / 2     | " << asmSin(PI / 2) << "        |\n";
    std::cout << "| 3.141596 / 2 | " << asmSin(B_PI / 2) << "        |\n";
    std::cout << "| ASM PI / 2   | " << asmSin(ASM_PI / 2) << "                             |\n";
    std::cout << std::endl;
    std::cout << std::defaultfloat;
}

int main() {
    measureDefaultSin();
    measureAsmSin();
    return 0;
}