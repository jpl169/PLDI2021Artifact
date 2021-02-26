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
        case 0xa4e2dc9 :
            res.value = 3003147415;
            return res;
            
        case 0xbdb3911 :
            res.value = 3018141655;
            return res;
            
        case 0x1441f36a :
            res.value = 3081632121;
            return res;
            
        case 0x1ab5f525 :
            res.value = 3143182227;
            return res;
            
        case 0x1c917912 :
            res.value = 3161168439;
            return res;
            
        case 0x1d56798a :
            res.value = 3170243093;
            return res;
            
        case 0x1e57f687 :
            res.value = 3180306003;
            return res;
            
        case 0x27fd88b7 :
            res.value = 3247169349;
            return res;
            
        case 0x28b4e219 :
            res.value = 3257106533;
            return res;
            
        case 0x344c3d12 :
            res.value = 3400904189;
            return res;
            
        case 0x36291fd6 :
            res.value = 3433790365;
            return res;
            
        case 0x3b69e0d4 :
            res.value = 3600580783;
            return res;
            
        case 0x428aeecf :
            res.value = 660055141;
            return res;
            
        case 0x512de8f7 :
            res.value = 982951925;
            return res;
            
        case 0x54423a4a :
            res.value = 1016676335;
            return res;
            
        case 0x5488e746 :
            res.value = 1019272695;
            return res;
            
        case 0x5514d795 :
            res.value = 1024248959;
            return res;
            
        case 0x58bead0e :
            res.value = 1058105801;
            return res;
            
        case 0x60b2f5b1 :
            res.value = 1110527027;
            return res;
            
        case 0x63afa01f :
            res.value = 1139208193;
            return res;
            
        case 0x6995490e :
            res.value = 1201382745;
            return res;
            
        case 0x719304ba :
            res.value = 1252278237;
            return res;
            
        case 0x79bdb836 :
            res.value = 1347351765;
            return res;
            
        default :
            res = log10(x.toDouble());
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
    
    return yp + m * LOG102LOW + log10Lut[FIndex] + m * LOG102HIGH;
}

void IntervalGenerator::GuessInitialLbUb(double x,
                                         double roundingLb, double roundingUb,
                                         double xp, double& lb, double& ub) {
    // Take a guess of yp that will end up in roundingLb, roundingUb.
    //printf("roundingLb : %.100e\n", roundingLb);
    //printf("roundingUb : %.100e\n", roundingUb);
    doubleX tempYp;
    tempYp.d = log1p(xp) / log(10);
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
