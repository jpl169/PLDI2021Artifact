#include "LibTestHelper.h"

float fMlibTest(float x, unsigned long* time) {
    unsigned int dummy;
    unsigned long t1 = __rdtscp(&dummy);
    
    float result = sinpif(x);
    
    unsigned long t2 = __rdtscp(&dummy);
    *time += (t2 - t1);
    
    return result;
}

float dMlibTest(float x, unsigned long* time) {
    unsigned int dummy;
    unsigned long t1 = __rdtscp(&dummy);
    
    double dx = (double)x;
    double result = sinpi(dx);
    float res = (float)result;
    
    unsigned long t2 = __rdtscp(&dummy);
    *time += (t2 - t1);
    
    if (result == dx) return x;
    return res;
}

float rlibmTest(float x, unsigned long* time) {
    unsigned int dummy;
    unsigned long t1 = __rdtscp(&dummy);
    
    float result = rlibm_sinpi(x);

    unsigned long t2 = __rdtscp(&dummy);
    *time += (t2 - t1);
    
    return result;
}

int main(int argc, char** argv) {

    if (argc != 2) {
        printf(1000000, "UsageL %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunTest(argv[1]);
    return 0;
}
