#include "float_math.h"
#include <stdio.h>
#include <math.h>
#include <x86intrin.h>

float myLog2Test(float x, unsigned long long* time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    float result = mylog2v2(x);
    unsigned long long t2 = __rdtscp(&dummy);
    *time += (t2 - t1);
    return result;
}

float mlibLog2Test(float x, unsigned long long* time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    float result = log2f(x);
    unsigned long long t2 = __rdtscp(&dummy);
    *time += (t2 - t1);
    return result;
}

float doubleLog2Test(float x, unsigned long long* time) {
    unsigned int dummy;
    unsigned long long t1 = __rdtscp(&dummy);
    float result = log2((double)x);
    unsigned long long t2 = __rdtscp(&dummy);
    *time += (t2 - t1);
    return result;
}

int main(int argc, char** argv) {
    unsigned long long count = 0;
    unsigned long long myTime = 0;
    unsigned long long mlibTime = 0;
    unsigned long long doubleTime = 0;

    float x;
    floatX xbase;
    for (unsigned long long int i = 0; i < 0x100000000; i++) {
        xbase.x = i;
        x = xbase.f;
        float bres = myLog2Test(x, &myTime);
        float bfy = mlibLog2Test(x, &mlibTime);
        float bdy = doubleLog2Test(x, &doubleTime);
        if (i != 0 && i % 10000000 == 0) {
            printf("i = %lld\n", i);
            printf("My Average time = %llu cycles\n", myTime / i);
            printf("Fl Average time = %llu cycles\n", mlibTime / i);
            printf("Db Average time = %llu cycles\n", doubleTime / i);
            printf("Speedup compared to float: %.5e\n", (double)mlibTime / (double)myTime);
            printf("Speedup compared to double: %.5e\n", (double)doubleTime / (double)myTime);
        }
    }

    printf("My Average time = %llu cycles\n", myTime / 0x100000000);
    printf("Fl Average time = %llu cycles\n", mlibTime / 0x100000000);
    printf("Db Average time = %llu cycles\n", doubleTime / 0x100000000);
    printf("Speedup compared to float: %.5e\n", (double)mlibTime / (double)myTime);
    printf("Speedup compared to double: %.5e\n", (double)doubleTime / (double)myTime);
}
