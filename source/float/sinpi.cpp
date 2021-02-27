#include "float_math.h"
#include "float_headers/Sinpi.h"
#include "float_headers/Cospi.h"
#include "luts.h"

float rlibm_sinpi(float x) {
    floatX fX;
    fX.f = x;
    unsigned s = fX.x & 0x80000000;
    fX.x &= 0x7FFFFFFF;
    
    // Special cases:
    if (fX.x <= 0x33fc1537) {
        return PI * (double)x;
    }
    
    if (fX.x >= 0x4b000000) {
        if (fX.x >= 0x7F800000) {
            return 0.0f/0.0f;
        }
        return 0.0f;
    }
    
    double xp = fX.f * 512;
    unsigned N = (unsigned)xp;
    unsigned N2 = N & 0xFF;
    unsigned I = N >> 8;
    double R;
    
    if (I & 0x1) {
        N2 = 255 - N2;
        R = (N + 1) * 0.001953125 - fX.f;
    } else R = fX.f - N * 0.001953125;
    
    if (I & 0x2) s ^= 0x80000000;
    
    double R2 = R * R;
    
    double cospiR, sinpiR;
    sinpiR = SinpiCoeffs[0][2];
    sinpiR *= R2;
    sinpiR += SinpiCoeffs[0][1];
    sinpiR *= R2;
    sinpiR += SinpiCoeffs[0][0];
    sinpiR *= R;
    
    cospiR = CospiCoeffs[0][2];
    cospiR *= R2;
    cospiR += CospiCoeffs[0][1];
    cospiR *= R2;
    cospiR += CospiCoeffs[0][0];
        
    fX.f = sinpiMBy512[N2] * cospiR + cospiMBy512[N2] * sinpiR;
    fX.x ^= s;
    
    return fX.f;
}
