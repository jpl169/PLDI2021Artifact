#define MPFR_PREC 500
#include "LibTestHelper.h"

float MpfrCalculate(float x) {
    mpfr_const_pi(mval, MPFR_RNDN);
    mpfr_mul_d(mval, mval, x, MPFR_RNDN);
    mpfr_sin(mval, mval, MPFR_RNDN);
    return ToMPFR(mval);
}

float fMlibTest(float x) {
    return 0.0;
}

float dMlibTest(float x) {
    return 0.0;
}

float rlibmTest(float x) {
    float result = rlibm_sinpi(x);
    return result;
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Usage: %s <output file>\n", argv[0]);
        exit(0);
    }
    
    RunCorrectnessTestForPIs(1000000, "Sinpi(x)", argv[1]);
    return 0;
}
