#include "LibTestHelper.h"

posit32_t dMlibTest(posit32_t x) {
    double result = log2(convertP32ToDouble(x));
    return convertDoubleToP32(result);
}

posit32_t rlibmTest(posit32_t x) {
    return rlibm_log2(x);
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest("Posit32 - Log2(x)", argv[1]);
    
    return 0;
}
