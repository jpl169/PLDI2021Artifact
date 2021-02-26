#include "IntervalGen/IntGenForPosit32OneApprox.h"
#include "luts.h"
#include "math.h"

posit32 IntervalGenerator::MpfrCalculateFunction(posit32 x) {
    mpfr_set_d(mval, x.toDouble(), MPFR_RNDN);
    mpfr_log(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
    
    // If you want to make it run faster, you can try the below code. Run it at
    // your own risk.
    
    /*
    posit32 res;
    switch (x.value) {
        case 0x17acd5b :
            res.value = 2696254747;
            return res;

        case 0x234ad55 :
            res.value = 2725991205;
            return res;

        case 0x10934c48:
            res.value = 2905452045;
            return res;

        case 0x210d8b5e :
            res.value = 3043457833;
            return res;

        case 0x21c28b8e :
            res.value = 3048504449;
            return res;

        case 0x23fb97a4 :
            res.value = 3062274139;
            return res;

        case 0x2eb63fcf :
            res.value = 3158112855;
            return res;

        case 0x332b6180 :
            res.value = 3214171935;
            return res;

        case 0x3bc8d09c :
            res.value = 3459698545;
            return res;

        case 0x3db4822b :
            res.value = 3591859805;
            return res;

        case 0x3f325bfa :
            res.value = 3781698575;
            return res;

        case 0x4550454d :
            res.value = 942031641;
            return res;

        case 0x47e1edaf :
            res.value = 989393609;
            return res;

        case 0x4a4417d8 :
            res.value = 1058318063;
            return res;

        case 0x56fa44e1 :
            res.value = 1208859447;
            return res;

        case 0x58d99b2e :
            res.value = 1220067345;
            return res;

        case 0x599d1171 :
            res.value = 1225620813;
            return res;

        case 0x5e4bf5bd :
            res.value = 1252253417;
            return res;

        case 0x72a52793 :
            res.value = 1426663971;
            return res;

        case 0x72f3c83a :
            res.value = 1430350045;
            return res;

        case 0x780bac42 :
            res.value = 1482474305;
            return res;

        case 0x78dc4bf5 :
            res.value = 1492142601;
            return res;
            
        default :
            res = log(x.toDouble());
            return res;
    }
     */
}

bool IntervalGenerator::ComputeSpecialCase(posit32 x, posit32& res) {
    if (x.value == 0) {
        res.value = 0x80000000;
        return true;
    } else if (x.value >= 0x80000000) {
        res.value = 0x80000000;
        return true;
    } else if (x.value == 0x40000000) {
        res.value = 0.0;
        return true;
    }
    
    return false;
}

double IntervalGenerator::RangeReduction(double x) {
    doubleX fix, fit;
    
    fix.d = x;
    
    int m = fix.x >> 52lu;
    m -= 1023lu;
    fix.x &= 0xFFFFFFFFFFFFFlu;
    fix.x |= 0x3FF0000000000000lu;
    
    fit.x = fix.x & 0xFE00000000000lu;
    int FIndex = fit.x >> 45lu;
    fit.x |= 0x3FF0000000000000lu;
    double F = fit.d;
    double f = fix.d - F;
    
    return f * log2OneByF[FIndex];
}
    
double IntervalGenerator::OutputCompensation(double x, double yp) {
    doubleX fix, fit;
    
    fix.d = x;
    
    int m = fix.x >> 52lu;
    m -= 1023lu;
    fix.x &= 0xFFFFFFFFFFFFFlu;
    fix.x |= 0x3FF0000000000000lu;
    
    fit.x = fix.x & 0xFE00000000000lu;
    int FIndex = fit.x >> 45lu;
    fit.x |= 0x3FF0000000000000lu;
    double F = fit.d;
    double f = fix.d - F;
    //printf("lut[88] = %.100e\n", lut[88]);
    
    return yp + m * LN2LOW + lnLutHIGH[FIndex] + m * LN2HIGH;
}

void IntervalGenerator::GuessInitialLbUb(double x,
                                         double roundingLb, double roundingUb,
                                         double xp, double& lb, double& ub) {
    // Take a guess of yp that will end up in roundingLb, roundingUb.
    //printf("roundingLb : %.100e\n", roundingLb);
    //printf("roundingUb : %.100e\n", roundingUb);
    doubleX tempYp;
    tempYp.d = log1p(xp);
    //printf("tempYp     : %.100e\n", tempYp.d);
    double tempY = OutputCompensation(x, tempYp.d);
    //printf("tempY      : %.100e\n", tempY);
    
    if (tempY < roundingLb) {
        // if tempY < roundingLb, then keep increasing tempYp until tempY is
        // >= roundingLb.
        do {
            tempYp.x++;
            tempY = OutputCompensation(x, tempYp.d);
        } while (tempY < roundingLb);
        
        // Then, it had better be that roundingLb <= tempY <= roundingUb.
        if (tempY > roundingUb) {
            printf("Error during GuessInitialLbUb: lb > ub.\n");
            printf("x = %.100e\n", x);
            exit(0);
        }
        lb = tempYp.d;
        ub = tempYp.d;
        return;
    }
    
    if (tempY > roundingUb) {
        // if tempY > roundingUb, then keep decreasing tempYp until tempY is
        // <= roundingUb.
        do {
            tempYp.x--;
            tempY = OutputCompensation(x, tempYp.d);
        } while (tempY > roundingLb);
        
        // Then, it had better be that roundingLb <= tempY <= roundingUb.
        if (tempY < roundingLb) {
            printf("Error during GuessInitialLbUb: lb > ub.\n");
            printf("x = %.100e\n", x);
            exit(0);
        }
        lb = tempYp.d;
        ub = tempYp.d;
        return;
    }
    
    lb = tempYp.d;
    ub = tempYp.d;
    return;
}

void IntervalGenerator::SpecCaseRedInt(double x,
                                       double glb, bool& blb, double& slb,
                                       double gub, bool& bub, double& sub) {
    blb = false;
    bub = false;
    return;
}

int main(int argc, char** argv) {
    mpfr_init2(mval, 200);
    
    if (argc != 2) {
        printf("Usage: %s <Name of File>\n", argv[0]);
        exit(0);
    }
    
    IntervalGenerator Log2IntGen;
    Log2IntGen.CreateReducedIntervalFile(argv[1]);
    
    mpfr_clear(mval);
    return 0;
}
