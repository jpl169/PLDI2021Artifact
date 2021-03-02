#include "posit32_math.h"
#include "softposit.h"
#include "stdio.h"
#include "mathimf.h"
#include <x86intrin.h>
#include "stdlib.h"

posit32_t dMlibTest(posit32_t x, unsigned long* time);
posit32_t rlibmTest(posit32_t x, unsigned long* time);

void RunTest(unsigned numTest, char* FileName) {
    unsigned long count = 0;
    unsigned long rlibmTime = 0;
    unsigned long dMlibTime = 0;
    unsigned long increment = 0;

    posit32_t x;
    
    unsigned long step = 0x100000000llu / (unsigned long)numTest;
    for (count = 0x0; count < numTest; count++) {
        x.v = count * step;
        
        posit32_t bres = rlibmTest(x, &rlibmTime);
        posit32_t bdy = dMlibTest(x, &dMlibTime);
        
        if (!p32_eq(bres, bdy)) increment++;
    }
    
    FILE* f = fopen(FileName, "w");
    if (increment) {
        fprintf(f, "%.5f\n", 1.0 * dMlibTime / rlibmTime);
    } else {
        fprintf(f, "%.5f\n", 1.0 * dMlibTime / rlibmTime);
    }
    fclose(f);
}
