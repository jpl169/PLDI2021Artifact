#include "float_math.h"
#include "stdio.h"
#include "mathimf.h"
#include "stdlib.h"

float fMlibTest(float x);
float dMlibTest(float x);
float rlibmTest(float x);

void RunCorrectnessTest(char const* FunctionName, char* resFileName) {
    unsigned long wrongFMlibCount = 0;
    unsigned long wrongDMlibCount = 0;
    unsigned long count = 0;

    unsigned int maxUlpFMlib = 0;
    unsigned int maxUlpDMlib = 0;
    float maxXFMlib = 0;
    float maxXDMlib = 0;

    float x;
    floatX xbase;
    for (count = 0x0; count < 0x100000000; count++) {
        xbase.x = count;
        x = xbase.f;
        
        float bres = rlibmTest(x);
        float bfy = fMlibTest(x);
        float bdy = dMlibTest(x);
        
        // if bres is nan and bmy is nan, continue
        if (bres != bres && bfy != bfy && bdy != bdy) continue;
        
        if (bfy != bres) wrongFMlibCount++;
        if (bdy != bres) wrongDMlibCount++;
    }
    
    FILE* f = fopen(resFileName, "w");
    
    fprintf(f, "%s TEST RESULT:\n", FunctionName);
    if (wrongFMlibCount == 0) {
        fprintf(f, "Intel's float library correct result for all inputs\n");
    } else {
        fprintf(f, "Intel's float library: Found %lu/%lu inputs with wrong result\n", wrongFMlibCount, count);
    }
    
    if (wrongDMlibCount == 0) {
        fprintf(f, "Intel's double library returns correct result for all inputs\n");
    } else {
        fprintf(f, "Intel's double library: Found %lu/%lu inputs with wrong result\n", wrongDMlibCount, count);
    }
    
    fclose(f);
}
