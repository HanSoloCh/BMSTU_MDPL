#include "test.h"

int main() {
    int rc = testsLenASM();
    rc += testsStrncpyASM();
    return rc;
}