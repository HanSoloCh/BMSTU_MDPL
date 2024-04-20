#include "test.h"

#include <iostream>
#include <cstring>

#include "ASMfunc.h"

extern "C" {
    void _strncpy(char *dst, const char *src, size_t len);
}

int testLenASM(const char *str) {
    int rc = 0;
    std::cout << "Testing string \"" << str << "\": ";
    if (strlen(str) != strlenASM(str)) {
        rc = 1;
        std::cout << "FAILED\n";
    } else
        std::cout << "PASSED\n";
    return rc;
}

int testsLenASM() {
    int failedTests = 0;
    const char *tests[4]{ "", "S", "Some", "Something" };
    std::cout << "Asm len tests: \n";
    for (auto test : tests)
        failedTests += testLenASM(test);

    return failedTests;

}

int testStrncpyASM(char *dst, const char *src, size_t len) {
    int rc = 0;
    fprintf(stdout, "Testing data: dst - %s, src - %s, len - %zu - ", dst, src, len);
    _strncpy(dst, src, len);
    if (strncmp(dst, src, len) != 0) {
        rc = 1;
        std::cout << "FAILED\n";
    } else
        std::cout << "PASSED\n";
    return rc;
}

int testsStrncpyASM() {
    int failedTests = 0;
    std::cout << "Asm strncpy tests: \n";
    char dstArr[][10]{ "qwerty", "qwerty", "qwerty" };

    const char *src = "abcd";
    size_t lengths[]{ 1, 2, 4};
    for (int i = 0; i < 3; ++i) {
        failedTests += testStrncpyASM(dstArr[i], src, lengths[i]);
    }
    return failedTests;
}