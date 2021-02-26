#include "softposit.h"
#include <cstdint>
#include "math.h"

typedef union {
    double d;
    unsigned long long x;
} doubleX;

posit32_t rlibm_log2(posit32_t x);
posit32_t rlibm_log(posit32_t x);
posit32_t rlibm_log10(posit32_t x);
