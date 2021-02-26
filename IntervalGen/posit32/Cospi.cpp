#include "IntervalGen/IntGenForPosit32TwoApprox.h"
#include "luts.h"
#include "math.h"

posit32 IntervalGenerator2::MpfrCalculateFunction(double x) {
    mpfr_const_pi(mval, MPFR_RNDN);
    mpfr_mul_d(mval, mval, x, MPFR_RNDN);
    mpfr_cos(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
}

bool IntervalGenerator2::ComputeSpecialCase(posit32 x, posit32& res) {
    // For generating intervals, we do not worry about negative signs. We also
    // don't have to worry about any value greater than 0.5. However, when we
    // actually implement it, we need to worry about signs.
    
    // If x in [0, a] then res = x * pi
    if (x.value <= 71693062) {
        res.value = 0x40000000;
        return true;
    }
    
    // If x is greater than
    // then x will always be an integer. In this case, cospi(even) = 1 or
    // cospi(odd) = -1
    // Case 1:
    // 0111 1110 1000 0000 0000 0000 0000 0000
    // 0x7E800000
    // 2^(4 * 5 + 2) = 2^22
    // even of
    
    // 0111 1110 1100 0000 0000 0000 0000 0000
    // 0x7ec00000
    // always even (1.0)
    
    if (x.value >= 0x7E800000) {
        if (x.value >= 0x7EC00000) {
            res.value = 0x40000000;
            return true;
        }
        
        if ((x.value & 0x1) == 0) {
            res.value = 0x40000000;
            return true;
        }
        
        res.value = 0xC0000000;
        return true;
    }
    
    return false;
}

double IntervalGenerator2::RangeReduction(double x) {
    doubleX fX;
    fX.d = x;
    fX.x &= 0x7FFFFFFFFFFFFFFF;
    
    // Range Reduction
    double xp = fX.d * 512.0;
    unsigned long N = (unsigned long)xp;
    unsigned long N2 = N & 0xFFl;
    unsigned long I = (N >> 8l) + 1l;
    double R, cospiM, sinpiM;
    unsigned long sign = (I & 0x2l) ? 0x8000000000000000 : 0;
    
    if (I & 1l) {
        if (N2 == 0) R = fX.d - N * 0.001953125;
        else {
            N2++;
            R = (N + 1l) * 0.001953125 - fX.d;
        }
    } else R = fX.d - N * 0.001953125;
    
    return R;
}

double IntervalGenerator2::OutputCompensation(double x,
                                              double sinpip,
                                              double cospip) {
    doubleX fX;
    fX.d = x;
    fX.x &= 0x7FFFFFFFFFFFFFFF;
    
    // Range Reduction
    double xp = fX.d * 512.0;
    unsigned long N = (unsigned long)xp;
    unsigned long N2 = N & 0xFFl;
    unsigned long I = (N >> 8l) + 1l;
    double R, cospiM, sinpiM;
    unsigned long sign = (I & 0x2l) ? 0x8000000000000000 : 0;
    
    if (I & 1l) {
      if (N2 == 0l) {
        R = fX.d - N * 0.001953125;
        cospiM = 1.0;
        sinpiM = 0.0;
      }
      else {
        N2++;
        R = (N + 1l) * 0.001953125 - fX.d;
        cospiM = sinpiMBy512[256l - N2];
        sinpiM = cospiMBy512[256l - N2];
      }
    } else {
      R = fX.d - N * 0.001953125;
      cospiM = sinpiMBy512[N2];
      sinpiM = cospiMBy512[N2];
    }
    
    fX.d = cospiM * cospip + sinpiM * sinpip;
    fX.x ^= sign;
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
    fX.x &= 0x7FFFFFFFFFFFFFFF;
    
    // Range Reduction
    double xp = fX.d * 512.0;
    unsigned N = (unsigned)xp;
    unsigned N2 = N & 0xFF;
    unsigned I = (N >> 8) + 1;
    double cospiM, sinpiM;
    unsigned sign = (I & 0x2) ? 0x8000000000000000 : 0;
    
    if (I & 1) {
        if (N2 == 0) {
            cospiM = 1.0;
            sinpiM = 0.0;
        }
        else {
            N2++;
            cospiM = sinpiMBy512[256 - N2];
            sinpiM = cospiMBy512[256 - N2];
        }
    } else {
        cospiM = sinpiMBy512[N2];
        sinpiM = cospiMBy512[N2];
    }

    double cospiR = cos(R * PI);
    double sinpiR = sin(R * PI);
    double M1 = totalLB / (cospiM * cospiR + sinpiM * sinpiR);
    double M2 = totalUB / (cospiM * cospiR + sinpiM * sinpiR);
    
    if (cospiM == 0) {
        cospiLB = -1.0e300;
        cospiUB = 1.0e300;
    } else if (cospiR == 0) {
        cospiLB = 0.0;
        cospiUB = 0.0;
    } else {
        cospiLB = cospiR * M1;
        cospiUB = cospiR * M2;
    }
    
    if (sinpiM == 0) {
        sinpiLB = -1.0e300;
        sinpiUB = 1.0e300;
    } else if (sinpiR == 0) {
        sinpiLB = 0.0;
        sinpiUB = 0.0;
    } else {
        sinpiLB = sinpiR * M1;
        sinpiUB = sinpiR * M2;
    }

    if (cospiM * cospiR + sinpiM * sinpiR == 0) {
        return true;
    }
      
    // Reconstruct sinpi(x) using sinpiHM * cospiLB + cospiHM * sinpiLB and make
    // sure that sinpiLB and cospiLB makes larger than totalLB.
    double recon = sinpiM * sinpiLB + cospiM * cospiLB;

    while (recon < totalLB) {
        //printf("hm1\n");
        if (cospiM != 0 && cospiLB != 0) {
            dx.d = cospiLB;
            if (dx.d >= 0) dx.x += 1000000;
            else dx.x -= 1000000;
            cospiLB = dx.d;
        }
        if (sinpiM != 0 && sinpiLB != 0) {
            dx.d = sinpiLB;
            if (dx.d >= 0) dx.x += 1000000;
            else dx.x -= 1000000;
            sinpiLB = dx.d;
        }
        recon = sinpiM * sinpiLB + cospiM * cospiLB;
    }
      
    // Reconstruct sinpi(x) using sinpiHM * cospiLB + cospiHM * sinpiLB and make
    // sure that we find the smallest sinpiLB and cospiLB boundary.
    unsigned long step = 0x100000000000;
    while (step > 0) {
        //printf("hm2\n");
        dx1.d = cospiLB;
        dx2.d = sinpiLB;
        
        if (cospiM != 0 && cospiLB != 0) {
            if (dx1.d >= 0) dx1.x -= step;
            else dx1.x += step;
        }
          
        if (sinpiM != 0 && sinpiLB != 0) {
            if (dx2.d >= 0) dx2.x -= step;
            else dx2.x += step;
        }
          
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
          
        if (recon >= totalLB) {
            cospiLB = dx1.d;
            sinpiLB = dx2.d;
        } else if (step > 0) {
            step /= 2;
        }
    }

    // I should try to make cospiLB and sinpiLB lower individually.
    step = 0x100000000000;
    while (step > 0) {
        //printf("hm2\n");
        dx1.d = cospiLB;
          
        if (cospiM != 0 && cospiLB != 0) {
            if (dx1.d >= 0) dx1.x -= step;
            else dx1.x += step;
        }
          
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
          
        if (recon >= totalLB) {
            cospiLB = dx1.d;
        }
        else if (step > 0) step /= 2;
    }

    step = 0x100000000000;
    while (step > 0) {
        dx2.d = sinpiLB;
        
        if (sinpiM != 0 && sinpiLB != 0) {
            if (dx2.d >= 0) dx2.x -= step;
            else dx2.x += step;
        }
        
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
        
        if (recon >= totalLB) {
            sinpiLB = dx2.d;
        } else if (step > 0) step /= 2;
    }

    // Reconstruct cospi(x) using sinpiM * sinpiUB + cospiM * cospiUB and make
    // sure that sinpiLB and cospiLB makes smaller than totalUB.
    recon = sinpiM * sinpiUB + cospiM * cospiUB;

    while (recon > totalUB) {
        //printf("hm3\n");
        if (cospiM != 0 && cospiUB != 0) {
            dx.d = cospiUB;
            if (dx.d >= 0) dx.x -= 1000000;
            else dx.x += 1000000;
            cospiUB = dx.d;
        }
        if (sinpiM != 0 && sinpiUB != 0) {
            dx.d = sinpiUB;
            if (dx.d >= 0) dx.x -= 1000000;
            else dx.x += 1000000;
            sinpiUB = dx.d;
        }
        recon = sinpiM * sinpiUB + cospiM * cospiUB;
    }
      
    // Reconstruct sinpi(x) using sinpiHM * cospiUB + cospiHM * sinpiUB and make
    // sure that we find the largest sinpiUB and cospiUB boundary.
    step = 0x100000000000;
    while (step > 0) {
        dx1.d = cospiUB;
        dx2.d = sinpiUB;
        
        if (cospiM != 0 && cospiUB != 0) {
            if (dx1.d >= 0) dx1.x += step;
            else dx1.x -= step;
        }
        
        if (sinpiM != 0 && sinpiUB != 0) {
            if (dx2.d >= 0) dx2.x += step;
            else dx2.x -= step;
        }
        
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
        
        if (recon <= totalUB) {
            cospiUB = dx1.d;
            sinpiUB = dx2.d;
        } else if (step > 0) {
            step /= 2;
        }
    }

    // I should try to make CospiUB and sinpiUB larger individually
    step = 0x100000000000;
    while (step > 0) {
        dx1.d = cospiUB;
        
        if (cospiM != 0 && cospiUB != 0) {
            if (dx1.d >= 0) dx1.x += step;
            else dx1.x -= step;
        }
        
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
        
        if (recon <= totalUB) {
            cospiUB = dx1.d;
        }
        else if (step > 0) step /= 2;
    }

    step = 0x100000000000;
    while (step > 0) {
        dx2.d = sinpiUB;
        
        if (sinpiM != 0 && sinpiUB != 0) {
            if (dx2.d >= 0) dx2.x += step;
            else dx2.x -= step;
        }
          
        double recon = sinpiM * dx2.d + cospiM * dx1.d;
          
        if (recon <= totalUB) {
            sinpiUB = dx2.d;
        }
        else if (step > 0) step /= 2;
    }
    
    return true;
    
}

int main(int argc, char** argv) {
    mpfr_init2(mval, 500);
    
    if (argc != 3) {
        printf("Usage: %s <reduced sinpi file> <reduced cospi file>\n", argv[0]);
        exit(0);
    }
    
    IntervalGenerator2 CospiIntGen;
    // Only need to calculate between 0 to 0.5.
    // All other values are reduced to this range, and reduces cleanly.
    CospiIntGen.CreateReducedIntervalFile(0x0, 0x38000000, argv[1], argv[2]);
    
    return 0;
}
