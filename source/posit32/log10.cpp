#include "posit32_math.h"
#include "luts.h"
#include "posit32_headers/Log10.h"

posit32_t rlibm_log10(posit32_t x) {
    if (x.v >= 0x80000000) {
        return castP32(0x80000000);
    } else if (x.v == 0) {
        return castP32(0x80000000);
    } else if (x.v == 0x40000000) {
        return castP32(0x0);
    }
    
    doubleX fix, fit, dX;
    fix.d = convertP32ToDouble(x);

    int m = fix.x >> 52lu;
    m -= 1023lu;
    fix.x &= 0xFFFFFFFFFFFFFlu;
    fix.x |= 0x3FF0000000000000lu;
    
    fit.x = fix.x & 0xFE00000000000lu;
    int FIndex = fit.x >> 45lu;
    fit.x |= 0x3FF0000000000000lu;
    
    dX.d = fix.d - fit.d;
    dX.d *= log2OneByF[FIndex];
    
    // Figure out index. 7 bits are the same. 64 - (7 + 12) = 64 - 19 = 45
    unsigned long index = (dX.x & 0x01FFFFFFFFFFFFFFlu) >> 45;
    const double* coeff = log10coeffs[index];
    
    // Compute polynomial
    double y = coeff[2];
    y *= dX.d;
    y += coeff[1];
    y *= dX.d;
    y += coeff[0];
    y *= dX.d;
    
    // Output compensation
    y += m * LOG102LOW;
    y += log10Lut[FIndex];
    y += m * LOG102HIGH;
    return convertDoubleToP32(y);
}
