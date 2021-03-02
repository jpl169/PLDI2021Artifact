#include "LibTestHelper.h"

float fMlibTest(float x) {
    float result = logf(x);
    return result;
}

float dMlibTest(float x) {
    double dx = (double)x;
    double result = log(dx);
    float res = (float)result;
    if (result == dx) return x;
    return res;
}

float rlibmTest(float x) {
    float result = rlibm_log(x);
    return result;
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest(1000000, "Log(x)", argv[1]);
    return 0;
}
