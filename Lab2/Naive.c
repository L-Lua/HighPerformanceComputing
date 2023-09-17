#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#define M 20
#define N 20
#define K 20

int A[M][K];
int L[M][N];
int R[N][K];
int C[M][K];
int main()
{
    struct timeval start , end;
    srand(time(NULL));
    for (int i = 0; i < M; i++)
        for (int j = 0; j< N;j++)
            L[i][j] = rand()%10;
    for (int i = 0; i < N; i++)
        for (int j = 0; j< K;j++)
            R[i][j] = rand()%10;
    for (int i = 0; i < M; i++)
        for (int j = 0; j< K;j++)
            C[i][j] = rand()%10;
    gettimeofday(&start, NULL);
    for (int i = 0; i < M; i++)
        for (int j = 0; j< N;j++)
            for (int k = 0; k < K; k++)
                A[i][k]+= L[i][j]*R[j][k];
    for (int i = 0;i < M;i++)
        for(int j = 0; j < K; j++)
            A[i][j]= 3 * A[i][j]+ 2 * C[i][j];
    gettimeofday(&end, NULL);
    printf("Start: %ld s %d us\n",start.tv_sec,start.tv_usec);
    printf("E n d: %ld s %d us\n",end.tv_sec,end.tv_usec);
    printf("%d us\n",(end.tv_sec - start.tv_sec)*1000000+(end.tv_usec-start.tv_usec));
    double duration = ((double)(end.tv_sec-start.tv_sec)*1000000 + (double)(end.tv_usec-start.tv_usec)) / 1000000;
    double gflops = 2.0*M*N*K;
    gflops = gflops/duration*1.0e-6/1000;
    /////
    FILE *fp;
    fp = fopen("timeNaiveDGEMM.txt", "a");
    fprintf(fp, "%dx%dx%d\t%lf s\t%lf GFLOPS\n", M, N, K, duration, gflops);
    fclose(fp);
    return 0;
}