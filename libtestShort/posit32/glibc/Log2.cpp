#define MPFR_PREC 200
#include "LibTestHelper.h"

posit32_t MpfrCalculate(posit32_t x) {
    mpfr_set_d(mval, convertP32ToDouble(x), MPFR_RNDN);
    mpfr_log2(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
}

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
    
    RunCorrectnessTest(1000000, "Posit32 - Log2(x)", argv[1]);
    
    return 0;
}
