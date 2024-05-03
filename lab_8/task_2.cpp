#include <math.h>

#include <iostream>

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
    std::cout << "Compile version of sin(PI) (should be 0):\n";
    std::cout << "For " << PI << " res - " << std::sin(PI) << std::endl;
    std::cout << "For " << B_PI << " res - " << std::sin(B_PI) << std::endl;
    std::cout << "For " << ASM_PI << " res - " << std::sin(ASM_PI) << std::endl;
    std::cout << "Compile version of sin(PI / 2) (should be 1):\n";
    std::cout << "For " << PI / 2 << " res - " << std::sin(PI / 2) << std::endl;
    std::cout << "For " << B_PI / 2 << " res - " << std::sin(B_PI / 2) << std::endl;
    std::cout << "For " << ASM_PI / 2 << " res - " << std::sin(ASM_PI / 2) << std::endl;
    std::cout << std::endl;
}

void measureAsmSin() {
    std::cout << "Preproc version of sin(PI) (should be 0):\n";
    std::cout << "For " << PI << " res - " << asmSin(PI) << std::endl;
    std::cout << "For " << B_PI << " res - " << asmSin(B_PI) << std::endl;
    std::cout << "For " << ASM_PI << " res - " << asmSin(ASM_PI) << std::endl;
    std::cout << "Preproc version of sin(PI / 2) (should be 1):\n";
    std::cout << "For " << PI / 2 << " res - " << asmSin(PI / 2) << std::endl;
    std::cout << "For " << B_PI / 2 << " res - " << asmSin(B_PI / 2) << std::endl;
    std::cout << "For " << ASM_PI / 2 << " res - " << asmSin(ASM_PI / 2) << std::endl;
    std::cout << std::endl;
}

int main() {
    measureDefaultSin();
    measureDefaultSin();
    return 0;
}