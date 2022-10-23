#include "stdio.h"
#include "stdlib.h"

void conv (float *a, int Na, float *b, int Nb, float *c)
{
    int Nc = Na + Nb - 1;
    for (int ib = 0; ib < Nb; ib++) {
        for (int ia = 0; ia < Na; ia++) {
            c[ib + ia] = c[ib + ia] + b[ib] * a[ia];
        };
    };
};

int main(int argc, char **argv)
{
    int N = 3;
    int Nc = 2*N - 1;
    float* a = (float*)malloc(N  * sizeof(float));
    float* b = (float*)malloc(N  * sizeof(float));
    float* c = (float*)malloc(Nc * sizeof(float));


    for (int i = 0; i < N; i++) {
        a[i] = i + 1;
        b[i] = N - i;
        printf("i = %d\n",i);
    };
    for (int i = 0; i < N; i++) {
        printf("a[%d] = %e\n",i,a[i]);
    };
    for (int i = 0; i < N; i++) {
        printf("b[%d] = %e\n",i,b[i]);
    };

    for (int i = 0; i < Nc; i++) {
        c[i] = 0;
    };

    conv(a, N, b, N, c);

    for (int i = 0; i < Nc; i++) {
        printf("c[%d] = %e\n",i, c[i]);
    };

    return 0;
};
