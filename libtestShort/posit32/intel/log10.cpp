#include "LibTestHelper.h"
posit32_t dMlibTest(posit32_t x) {
    double result = log10(convertP32ToDouble(x));
    return convertDoubleToP32(result);
}

posit32_t rlibmTest(posit32_t x) {
    return rlibm_log10(x);
}

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTest(1000000, "Posit32 - Log10(x)", argv[1]);
    return 0;
}
