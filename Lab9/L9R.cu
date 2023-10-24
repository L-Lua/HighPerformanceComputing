//Compile the code and run it with a parameter
//For example
//     ./L9 1024
//means the size of the matrices is 1024

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <sys/time.h>
#include <string.h>
#define LENB 16

__global__ void My_MMult(double *A, double *B, double *C, int m, int n, int k) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < m && col < n) {
        double sum = C[row * n + col];
        for (int i = 0; i < k; ++i) 
            sum += A[row * k + i] * B[i * n + col];
        C[row * n + col] = sum;
    }
}


double TIME() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return ((double)t.tv_sec + (double)t.tv_usec * 1e-6);
}

int main(int argc, char**argv) {
    int m=1, n=1, k=1;
    m = atoi(argv[1]);
    n = atoi(argv[1]);
    k = atoi(argv[1]);
    double *A, *B, *C, *a, *b, *c;
    A = (double *)malloc(m * k * sizeof(double));
    B = (double *)malloc(k * n * sizeof(double));
    C = (double *)malloc(m * n * sizeof(double));
    cudaMalloc((void **)&a, m * k * sizeof(double));
    cudaMalloc((void **)&b, k * n * sizeof(double));
    cudaMalloc((void **)&c, m * n * sizeof(double));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < k;j++)
            A[i*k+j]=1;
    for (int i = 0; i < k; i++)
        for (int j = 0; j < n;j++)
            B[i*n+j]=1;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n;j++)
            C[i*n+j]=1;
    cudaMemcpy(a, A, m * k * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(b, B, k * n * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(c, C, m * n * sizeof(double), cudaMemcpyHostToDevice);
    dim3 blockSize(LENB, LENB);
    dim3 gridSize((n + LENB - 1) / LENB, (m + LENB - 1) / LENB);

    double st= TIME();
    My_MMult<<<gridSize, blockSize>>>(a, b, c, m, n, k);
    cudaDeviceSynchronize();
    double et = TIME();

    double gflops = 2.0 * m * k * n * 1e-9;
    gflops /= et - st;

    printf("%d ",m);
    printf("%le\n", gflops);
    
    cudaMemcpy(C, c, m * n * sizeof(double), cudaMemcpyDeviceToHost);
/*
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n;j++)
            printf("%.0lf", C[i * n + j]);
        printf("\n");
    }
*/
    free(A);free(B);free(C);
    cudaFree(a);cudaFree(b);cudaFree(c);
    return 0;
}
