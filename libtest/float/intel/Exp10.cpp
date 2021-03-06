#include "LibTestHelper.h"

#ifdef __APPLE__
#define exp10fFunc __exp10f
#else
#define exp10fFunc exp10f
#endif

#ifdef __APPLE__
#define exp10Func __exp10
#else
#define exp10Func exp10
#endif

float fMlibTest(float x) {
    float result = exp10fFunc(x);
    return result;
}

float dMlibTest(float x) {
    double dx = (double)x;
    double result = exp10Func(dx);
    float res = (float)result;
    if (result == dx) return x;
    return res;
}

float rlibmTest(float x) {
    float result = rlibm_exp10(x);
    return result;
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest("Exp10(x)", argv[1]);
    return 0;
}
