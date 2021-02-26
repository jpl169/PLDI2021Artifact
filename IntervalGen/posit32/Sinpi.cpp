#include "IntervalGen/IntGenForPosit32TwoApprox.h"
#include "luts.h"
#include "math.h"

posit32 IntervalGenerator2::MpfrCalculateFunction(double x) {
    mpfr_const_pi(mval, MPFR_RNDN);
    mpfr_mul_d(mval, mval, x, MPFR_RNDN);
    mpfr_sin(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
}

bool IntervalGenerator2::ComputeSpecialCase(posit32 x, posit32& res) {
    // For generating intervals, we do not worry about negative signs. We also
    // don't have to worry about any value greater than 0.5. However, when we
    // actually implement it, we need to worry about signs.
    
    // If x in [0, a] then res = x * pi
    if (x.value <= 25416792) {
        res = x.toDouble() * PI;
        return true;
    }
    
    // If x is greater than
    // then x will always be an integer. In this case, sinpi(integer) = 0
    // 0111 1110 1000 0000 0000 0000 0000 0000
    // 0x7E800000
    // 2^(4 * 5 + 2) = 2^22
    if (x.value >= 0x7E800000) {
        res.value = 0;
        return true;
    }
    
    return false;
}

double IntervalGenerator2::RangeReduction(double x) {
    doubleX fX;
    fX.d = x;
    fX.x &= 0x7FFFFFFFFFFFFFFF;
    
    double xp = fX.d * 512.0;
    unsigned long N = (unsigned long)xp;
    unsigned long N2 = N & 0xFFlu;
    unsigned long I = N >> 8lu;
    double R;
    
    if (I & 0x1lu) {
        N2 = 255lu - N2;
        R = (N + 1lu) * 0.001953125 - fX.d;
    } else R = fX.d - N * 0.001953125;
    
    return R;
}

double IntervalGenerator2::OutputCompensation(double x,
                                              double sinpip,
                                              double cospip) {
    doubleX fX;
    fX.d = x;
    unsigned s = fX.x & 0x8000000000000000;
    fX.x &= 0x7FFFFFFFFFFFFFFF;
    
    double xp = fX.d * 512;
    unsigned long N = (unsigned long)xp;
    unsigned long N2 = N & 0xFFlu;
    unsigned long I = N >> 8lu;
    double R;
    
    if (I & 0x1lu) {
        N2 = 255lu - N2;
        R = (N + 1lu) * 0.001953125 - fX.d;
    } else R = fX.d - N * 0.001953125;
    
    if (I & 0x2lu) s ^= 0x8000000000000000;
    
    fX.d = cospiMBy512[N2] * sinpip + sinpiMBy512[N2] * cospip;
    fX.x ^= s;
    
    return fX.d;
}

void IntervalGenerator2::
SpecCaseRedInt(double x,
               double sinhLbGuess, bool& sinhLbSpec, double& sinhLB,
               double sinhUbGuess, bool& sinhUbSpec, double& sinhUB,
               double coshLbGuess, bool& coshLbSpec, double& coshLB,
               double coshUbGuess, bool& coshUbSpec, double& coshUB) {
    return;
}

bool IntervalGenerator2::GuessInitialLbUb(double x,
                                          double totalLB, double totalUB,
                                          double R,
                                          double& sinpiLB, double& sinpiUB,
                                          double& cospiLB, double& cospiUB) {
    doubleX dx, dx1, dx2;
    doubleX fX;
    fX.d = x;
    unsigned s = fX.x & 0x8000000000000000;
    fX.x &= 0x7FFFFFFFFFFFFFFF;
    
    double xp = fX.d * 512;
    unsigned long N = (unsigned)xp;
    unsigned long N2 = N & 0xFF;
    unsigned long I = N >> 8;
    
    if (I & 0x1) {
        N2 = 255 - N2;
    }
    
    if (I & 0x2) s ^= 0x8000000000000000;

    double cospiM = cospiMBy512[N2];
    double sinpiM = sinpiMBy512[N2];
    double SINPIR = sin(R * PI);
    double COSPIR = cos(R * PI);
    
    double M1 = totalLB / (cospiM * SINPIR + sinpiM * COSPIR);
    double M2 = totalUB / (cospiM * SINPIR + sinpiM * COSPIR);

    if (cospiM == 0) {
        sinpiLB = -1.0e300;
        sinpiUB = 1.0e300;
    } else if (SINPIR == 0) {
        sinpiLB = 0;
        sinpiUB = 0;
    } else {
        sinpiLB = SINPIR * M1;
        sinpiUB = SINPIR * M2;
    }

    if (sinpiM == 0) {
        cospiLB = -1.0e300;
        cospiUB = 1.0e300;
    } else if (COSPIR == 0) {
        cospiLB = 0;
        cospiUB = 0;
    } else {
        cospiLB = COSPIR * M1;
        cospiUB = COSPIR * M2;
    }

    if (cospiM * SINPIR + sinpiM * COSPIR == 0) {
        return true;
    }

    
    // If the signs are the same, we have to restrict sinpiLB and cospiLB, then
    // sinpiUB and cospiUB
    
    // Reconstruct sinpi(x) using sinpiHM * cospiLB + cospiHM * sinpiLB and make
    // sure that sinpiLB and cospiLB makes larger than totalLB.
    double recon = sinpiM * cospiLB + cospiM * sinpiLB;

    while (recon < totalLB) {
        if (sinpiM != 0 && cospiLB != 0) {
            dx.d = cospiLB;
            if (dx.d >= 0) dx.x += 1000000;
            else dx.x -= 1000000;
            cospiLB = dx.d;
        }
        if (cospiM != 0 && sinpiLB != 0) {
            dx.d = sinpiLB;
            if (dx.d >= 0) dx.x += 1000000;
            else dx.x -= 1000000;
            sinpiLB = dx.d;
        }
        recon = sinpiM * cospiLB + cospiM * sinpiLB;
    }
    
    // Reconstruct sinpi(x) using sinpiHM * cospiLB + cospiHM * sinpiLB and make
    // sure that we find the smallest sinpiLB and cospiLB boundary.
    unsigned long step = 0x100000000000;
    while (step > 0) {
        dx1.d = cospiLB;
        dx2.d = sinpiLB;
        
        if (sinpiM != 0 && cospiLB != 0) {
            if (dx1.d >= 0) dx1.x -= step;
            else dx1.x += step;
        }
        
        if (cospiM != 0 && sinpiLB != 0) {
            if (dx2.d >= 0) dx2.x -= step;
            else dx2.x += step;
        }
        
        double recon = sinpiM * dx1.d + cospiM * dx2.d;
        
        if (recon >= totalLB) {
            cospiLB = dx1.d;
            sinpiLB = dx2.d;
        } else if (step > 0) {
            step /= 2;
        }
    }
    
    // Reconstruct sinpi(x) using sinpiHM * cospiLB + cospiHM * sinpiLB and make
    // sure that sinpiLB and cospiLB makes smaller than totalUB.
    recon = sinpiM * cospiUB + cospiM * sinpiUB;

    while (recon > totalUB) {
        if (sinpiM != 0 && cospiUB != 0) {
            dx.d = cospiUB;
            if (dx.d >= 0) dx.x -= 1000000;
            else dx.x += 1000000;
            cospiUB = dx.d;
        }
        if (cospiM != 0 && sinpiUB != 0) {
            dx.d = sinpiUB;
            if (dx.d >= 0) dx.x -= 1000000;
            else dx.x += 1000000;
            sinpiUB = dx.d;
        }
        recon = sinpiM * cospiUB + cospiM * sinpiUB;
    }
    
    // Reconstruct sinpi(x) using sinpiHM * cospiUB + cospiHM * sinpiUB and make
    // sure that we find the largest sinpiUB and cospiUB boundary.
    step = 0x100000000000;
    while (step > 0) {
        dx1.d = cospiUB;
        dx2.d = sinpiUB;
        
        if (sinpiM != 0 && cospiUB != 0) {
            if (dx1.d >= 0) dx1.x += step;
            else dx1.x -= step;
        }
        
        if (cospiM != 0 && sinpiUB != 0) {
            if (dx2.d >= 0) dx2.x += step;
            else dx2.x -= step;
        }
        
        double recon = sinpiM * dx1.d + cospiM * dx2.d;
        
        if (recon <= totalUB) {
            cospiUB = dx1.d;
            sinpiUB = dx2.d;
        } else if (step > 0) {
            step /= 2;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    mpfr_init2(mval, 500);
    
    if (argc != 3) {
        printf("Usage: %s <reduced sinpi file> <reduced cospi file>\n", argv[0]);
        exit(0);
    }
    
    IntervalGenerator2 SinpiIntGen;
    // Only need to calculate between 0 to 0.5.
    // All other values are reduced to this range, and reduces cleanly.
    SinpiIntGen.CreateReducedIntervalFile(0x0, 0x38000000, argv[1], argv[2]);
    
    return 0;
}
