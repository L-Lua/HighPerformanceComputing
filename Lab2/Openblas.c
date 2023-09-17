#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include <cblas.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc < 4)
    {
        printf("Argument Error");
        return -1;
    }
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int k = atoi(argv[3]);
    double* L = malloc(m * n * sizeof(double));
    double* R = malloc(n * k * sizeof(double));
    double* C = malloc(m * k * sizeof(double));
    for(int i = 0; i < m * n; i++)
        L[i]=rand()%10;
    for(int i = 0; i < n * k; i++)
        R[i]=rand()%10;
    for(int i = 0; i < m * k; i++)
        C[i]=rand()%10;
    //Loaded
    struct timeval start, end;
    gettimeofday(&start,NULL);
    cblas_dgemm (CblasRowMajor,CblasNoTrans,CblasTrans,m,n,k,3,L,m,R,n,2,C,m);
    gettimeofday(&end,NULL);//
    /////
    double duration = ((double)(end.tv_sec-start.tv_sec)*1000000 + (double)(end.tv_usec-start.tv_usec)) / 1000000;
    double gflops = 2.0*m*n*k;
    gflops = gflops/duration*1.0e-6/1000;
    /////
    FILE *fp;
    fp = fopen("timeDGEMM.txt", "a");
    fprintf(fp, "%dx%dx%d\t%lf s\t%lf GFLOPS\n", m, n, k, duration, gflops);
    fclose(fp);
    /////
    free(L);free(R);free(C);
}
