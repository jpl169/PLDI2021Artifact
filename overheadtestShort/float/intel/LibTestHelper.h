#include "float_math.h"
#include "stdio.h"
#include "mathimf.h"
#include <x86intrin.h>
#include "stdlib.h"

float fMlibTest(float x, unsigned long* time);
float dMlibTest(float x, unsigned long* time);
float rlibmTest(float x, unsigned long* time);

void RunTest(unsigned numTest, char* FileName) {
    unsigned long count = 0;
    unsigned long rlibmTime = 0;
    unsigned long fMlibTime = 0;
    unsigned long dMlibTime = 0;
    unsigned long increment = 0;

    float x;
    floatX xbase;
    
    unsigned long step = 0x100000000llu / (unsigned long)numTest;
    for (count = 0x0; count < numTest; count++) {
        xbase.x = count * step;
        x = xbase.f;
        
        float bres = rlibmTest(x, &rlibmTime);
        float bfy = fMlibTest(x, &fMlibTime);
        float bdy = dMlibTest(x, &dMlibTime);
        
        // if bres is nan and bmy is nan, continue
        if (bres != bres && bfy != bfy && bdy != bdy) continue;
        
        // Otherwise check if the output is correct
        if (bres != bfy || bres != bdy) increment++;
    }
    
    FILE* f = fopen(FileName, "w");
    if (increment) {
        fprintf(f, "%.5f, ", 1.0 * fMlibTime / rlibmTime);
        fprintf(f, "%.5f\n", 1.0 * dMlibTime / rlibmTime);
    } else {
        fprintf(f, "%.5f, ", 1.0 * fMlibTime / rlibmTime);
        fprintf(f, "%.5f\n", 1.0 * dMlibTime / rlibmTime);
    }
    fclose(f);
}
