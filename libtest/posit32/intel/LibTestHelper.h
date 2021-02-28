#include "posit32_math.h"
#include "softposit.h"
#include "stdio.h"
#include "mathimf.h"

posit32_t dMlibTest(posit32_t x);
posit32_t rlibmTest(posit32_t x);

void RunCorrectnessTest(char const* FunctionName, char* resFileName) {
    unsigned long wrongDMlibCount = 0;
    unsigned long count = 0;

    posit32_t x;
    for (count = 0x0; count < 0x100000000; count++) {
        x.v = count;
        
        posit32_t bres = rlibmTest(x);
        posit32_t bdy = dMlibTest(x);
        
        if (!p32_eq(bdy,bres)) wrongDMlibCount++;
    }
    
    FILE* f = fopen(resFileName, "w");
    
    if (wrongDMlibCount == 0) {
        fprintf(f, "Intel's double library returns correct result for all inputs\n");
    } else {
        fprintf(f, "Intel's double library: Found %lu/%lu inputs with wrong result\n", wrongDMlibCount, count);
    }
    
    fclose(f);
}
