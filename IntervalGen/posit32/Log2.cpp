#include "IntervalGen/IntGenForPosit32OneApprox.h"
#include "luts.h"
#include "math.h"

posit32 IntervalGenerator::MpfrCalculateFunction(posit32 x) {
    mpfr_set_d(mval, x.toDouble(), MPFR_RNDN);
    mpfr_log2(mval, mval, MPFR_RNDN);
    return FromMPFR(mval);
    
    // If you want to make it run faster, you can try the below code. Run it at
    // your own risk.
    
    /*
    posit32 res;
    switch (x.value) {
        case 568702550 :
            res.value = 2973394919;
            return res;
        case 641115013 :
            res.value = 3008435553;
            return res;
        case 670753592 :
            res.value = 3019777961;
            return res;
        case 702920278 :
            res.value = 3040503783;
            return res;
        case 775332741 :
            res.value = 3075544417;
            return res;
        case 804971320 :
            res.value = 3086886825;
            return res;
        case 922225493 :
            res.value = 3208326949;
            return res;
        case 976676364 :
            res.value = 3315859519;
            return res;
        case 1018414065 :
            res.value = 3445104647;
            return res;
        case 1036152005 :
            res.value = 3524399939;
            return res;
        case 1106429268 :
            res.value = 839909535;
            return res;
        case 1324878677 :
            res.value = 1195061029;
            return res;
        case 1374008918 :
            res.value = 1228564455;
            return res;
        case 1446421381 :
            res.value = 1263605089;
            return res;
        case 1476059960 :
            res.value = 1274947497;
            return res;
        case 1508226646 :
            res.value = 1295673319;
            return res;
        case 1580639109 :
            res.value = 1330713953;
            return res;
        case 1610277688 :
            res.value = 1342056361;
            return res;
        default :
            res = log2(x.toDouble());
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
    
    return yp + (log2Lut[FIndex] + m);
}

void IntervalGenerator::GuessInitialLbUb(double x,
                                         double roundingLb, double roundingUb,
                                         double xp, double& lb, double& ub) {
    // Take a guess of yp that will end up in roundingLb, roundingUb.
    //printf("roundingLb : %.100e\n", roundingLb);
    //printf("roundingUb : %.100e\n", roundingUb);
    doubleX tempYp;
    tempYp.d = log1p(xp) / log(2);
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
