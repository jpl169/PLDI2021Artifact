#pragma once
#include "math.h"
#include <cstdint>

typedef union {
    double d;
    uint64_t x;
} doubleX;

typedef union {
    float f;
    unsigned int x;
} floatX;

float rlibm_log(float);
float rlibm_log2(float);
float rlibm_log10(float);
float rlibm_exp(float);
float rlibm_exp2(float);
float rlibm_exp10(float);
float rlibm_sinh(float);
float rlibm_cosh(float);
float rlibm_sinpi(float);
float rlibm_cospi(float);

