#include "mpfr.h"
#include "float_math.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

mpfr_t mval;

float MpfrCalculate(float x);
float fMlibTest(float x);
float dMlibTest(float x);
float rlibmTest(float x);

float ToMPFR(mpfr_t mval) {
    double retVal = mpfr_get_d(mval, MPFR_RNDN);

    if (retVal == 0) return 0.0f;
    if (retVal != retVal) {
        return retVal;
    }
    
    if (mpfr_cmp_d(mval, pow(2, -150)) <= 0 && mpfr_cmp_d(mval, -pow(2, -150)) >= 0) {
        return 0.0f;
    }

    long exp;
    double fr = mpfr_get_d_2exp(&exp, mval, MPFR_RNDN);
    fr *= 2;
    exp--;
    
    if (mpfr_cmp_d(mval, 0.0) > 0) {
        if (mpfr_cmp_d(mval, 1.5 * pow(2, -149)) < 0) return pow(2, -149);
        if (mpfr_cmp_d(mval, pow(2, -148)) < 0) return pow(2, -148);

    } else {
        if (mpfr_cmp_d(mval, -1.5 * pow(2, -149)) > 0) return -pow(2, -149);
        if (mpfr_cmp_d(mval, -pow(2, -148)) > 0) return -pow(2, -148);
    }
    
    if (exp >= -148 && exp <= -127) {
        int prec = 150 + exp;
        mpfr_t r;
        mpfr_init2(r, prec);
        mpfr_set(r, mval, MPFR_RNDN);
        retVal = mpfr_get_d(r, MPFR_RNDN);
        mpfr_clear(r);
        return retVal;
    } else {
        mpfr_t r;
        mpfr_init2(r, 24);
        mpfr_set(r, mval, MPFR_RNDN);
        retVal = mpfr_get_d(r, MPFR_RNDN);
        mpfr_clear(r);
        return retVal;
    }
}

unsigned int m_ulpf(float x, float y) {
  if (x == 0)
    x = 0; // -0 == 0
  if (y == 0)
    y = 0; // -0 == 0

  if (x != x && y != y) return 0;

  if (x != x)
    return UINT_MAX - 1; // Maximum error
  if (y != y)
    return UINT_MAX - 1; // Maximum error

  int xx = *((int *)&x);
  xx = xx < 0 ? INT_MAX - xx : xx;

  int yy = *((int *)&y);
  yy = yy < 0 ? INT_MAX - yy : yy;
  return xx >= yy ? xx - yy : yy - xx;
}

void RunCorrectnessTest(unsigned numTest, char const* FunctionName, char* resFileName) {
    mpfr_init2(mval, MPFR_PREC);

    unsigned long wrongRlibmCount = 0;
    unsigned long wrongFMlibCount = 0;
    unsigned long wrongDMlibCount = 0;
    unsigned long count = 0;

    unsigned int maxUlpRlibm = 0;
    unsigned int maxUlpFMlib = 0;
    unsigned int maxUlpDMlib = 0;
    float maxXRlibm = 0;
    float maxXFMlib = 0;
    float maxXDMlib = 0;

    float x;
    floatX xbase;
    
    unsigned long long step = 0x100000000llu / (unsigned long long)numTest;
    for (count = 0; count < numTest; count++) {
        xbase.x = count * step;
        x = xbase.f;
        
        float bmy = MpfrCalculate(x);
        float bres = rlibmTest(x);
        float bfy = fMlibTest(x);
        float bdy = dMlibTest(x);
        
        // if bres is nan and bmy is nan, continue
        if (bres != bres && bmy != bmy && bfy != bfy && bdy != bdy) continue;
        
        // Otherwise check if the output is correct
        if (bres != bmy) {
            wrongRlibmCount++;
            unsigned int error = m_ulpf(bres, bmy);
            if (error > maxUlpRlibm) {
                maxUlpRlibm = error;
                maxXRlibm = x;
            }
        }
        
        if (bfy != bmy) {
            wrongFMlibCount++;
            unsigned int error = m_ulpf(bfy, bmy);
            if (error > maxUlpFMlib) {
                maxUlpFMlib = error;
                maxXFMlib = x;
            }
        }
        
        if (bdy != bmy) {
            wrongDMlibCount++;
            unsigned int error = m_ulpf(bdy, bmy);
            if (error > maxUlpDMlib) {
                maxUlpDMlib = error;
                maxXDMlib = x;
            }
        }
    }
    
    FILE* f = fopen(resFileName, "w");
    
    fprintf(f, "%s TEST RESULT:\n", FunctionName);
    if (wrongRlibmCount == 0) {
        fprintf(f, "PWLIBM returns correct result for all inputs\n");
    } else {
        fprintf(f, "PWLIBM: Found %lu/%lu inputs with wrong result\n", wrongRlibmCount, count);
    }
    
    if (wrongFMlibCount == 0) {
        fprintf(f, "GLibc's float library returns correct result for all inputs\n");
    } else {
        fprintf(f, "GLibc's float library: Found %lu/%lu inputs with wrong result\n", wrongFMlibCount, count);
    }
    
    if (wrongDMlibCount == 0) {
        fprintf(f, "Glibc's double library returns correct result for all inputs\n");
    } else {
        fprintf(f, "Glibc's double library: Found %lu/%lu inputs with wrong result\n", wrongDMlibCount, count);
    }
    
    fclose(f);
    mpfr_clear(mval);
}

void RunCorrectnessTestForPIs(unsigned numTest, char const* FunctionName, char* resFileName) {
    mpfr_init2(mval, MPFR_PREC);

    unsigned long wrongRlibmCount = 0;
    unsigned long wrongFMlibCount = 0;
    unsigned long wrongDMlibCount = 0;
    unsigned long count = 0;

    unsigned int maxUlpRlibm = 0;
    unsigned int maxUlpFMlib = 0;
    unsigned int maxUlpDMlib = 0;
    float maxXRlibm = 0;
    float maxXFMlib = 0;
    float maxXDMlib = 0;

    float x;
    floatX xbase;
    
    unsigned long long step = 0x100000000llu / (unsigned long long)numTest;
    for (count = 0; count < numTest; count++) {
        xbase.x = count * step;
        x = xbase.f;
        
        float bmy = MpfrCalculate(x);
        float bres = rlibmTest(x);
        
        // if bres is nan and bmy is nan, continue
        if (bres != bres && bmy != bmy) continue;
        
        // Otherwise check if the output is correct
        if (bres != bmy) {
            wrongRlibmCount++;
            unsigned int error = m_ulpf(bres, bmy);
            if (error > maxUlpRlibm) {
                maxUlpRlibm = error;
                maxXRlibm = x;
            }
        }
    }
    
    FILE* f = fopen(resFileName, "w");
    
    fprintf(f, "%s TEST RESULT:\n", FunctionName);
    if (wrongRlibmCount == 0) {
        fprintf(f, "PWLIBM returns correct result for all inputs\n");
    } else {
        fprintf(f, "PWLIBM: Found %lu/%lu inputs with wrong result\n", wrongRlibmCount, count);
    }
    
    fclose(f);
    mpfr_clear(mval);
}

