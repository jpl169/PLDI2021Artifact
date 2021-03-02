#include "LibTestHelper.h"

posit32_t dMlibTest(posit32_t x, unsigned long* time) {
    unsigned int dummy;
    unsigned long t1 = __rdtscp(&dummy);
    double dx = convertP32ToDouble(x);
    double result = log2(dx);
    posit32_t res = convertDoubleToP32(result);
    unsigned long t2 = __rdtscp(&dummy);
    *time += (t2 - t1);
    
    return res;
}

posit32_t rlibmTest(posit32_t x, unsigned long* time) {
    unsigned int dummy;
    unsigned long t1 = __rdtscp(&dummy);
    posit32_t result = rlibm_log2(x);
    unsigned long t2 = __rdtscp(&dummy);
    *time += (t2 - t1);
    
    return result;
}

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("UsageL %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunTest(1000000, argv[1]);
    return 0;
}
