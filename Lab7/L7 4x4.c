#include <stdio.h>
#include <malloc.h>
#include "mpi.h"


int main(int argc, char** argv)

{
double A[16]={
-1.000000e+00, -2.707955e-01, 5.350056e-02, 8.634630e-01, 
-9.980292e-01, -8.173388e-01, -9.113315e-02, 1.361192e-01, 
-9.167380e-01, -8.154047e-01, -5.336431e-01, 1.121887e-01, 
-6.467147e-01, -2.556555e-02, 6.625836e-01, -8.983362e-01, 
};

double B[16]={
5.341023e-01, 7.519617e-01, 6.208589e-01, -8.464509e-01, 
-9.621704e-01, 6.311373e-02, -6.231595e-01, 6.305478e-01, 
-4.952805e-01, 8.405219e-01, 7.726289e-01, 9.697820e-01, 
-4.036057e-01, 3.086230e-02, 1.412280e-01, -7.632966e-01, 
};

double C[16]={
-6.485472e-01, -6.974358e-01, -2.888289e-01, 6.850692e-02, 
2.435674e-01, -8.744635e-01, -1.614912e-01, 1.371329e-01, 
5.139494e-01, -1.185891e+00, -4.575017e-01, -3.413287e-01, 
-2.864046e-01, 4.127302e-02, -5.262187e-04, 1.859551e+00, 
};

double D[16];

    int m = 4,n = 4,k = 4;///////////////////////////////////////
    int thread_num, thread_id, source;
    MPI_Status  status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&thread_id);
    MPI_Comm_size(MPI_COMM_WORLD,&thread_num);
    int pblocks = m/(thread_num-1);
        if(thread_id == 0)
        {
            for(int i=0;i<thread_num-1;i++)
            {
                int row_s= i * pblocks;
                int row_e= row_s + pblocks;
                MPI_Send(&A[row_s*k],k*pblocks, MPI_DOUBLE, i+1, 1, MPI_COMM_WORLD);
                MPI_Send(B, n*k, MPI_DOUBLE, i+1, 2, MPI_COMM_WORLD);
                MPI_Send(&C[row_s*n], pblocks*n, MPI_DOUBLE, i+1, 3, MPI_COMM_WORLD);
            }
            for(int i=0;i<thread_num-1;i++)
            {
                MPI_Recv(&D[i*pblocks*n],pblocks*n,MPI_DOUBLE,i+1,4,MPI_COMM_WORLD,&status);
            }
            for (int i = 0;i<m;i++)
    		{
                for (int j = 0;j<n;j++)
    		        printf("%lf ",D[i*n+j]);
                printf("\n");}
        	}
        else
        {
                double* a= (double*) malloc(sizeof(double)*k*pblocks);
                double* b= (double*) malloc(sizeof(double)*k*n);
                double* c= (double*) malloc(sizeof(double)*pblocks*n);
                MPI_Recv(a,k*pblocks,MPI_DOUBLE,0,1,MPI_COMM_WORLD,&status);
                MPI_Recv(b,k*n,MPI_DOUBLE,0,2,MPI_COMM_WORLD,&status);
                MPI_Recv(c,pblocks*n,MPI_DOUBLE,0,3,MPI_COMM_WORLD,&status);
                for (int i=0;i<1;i++)
                for (int row = 0 ;row< pblocks;row++)
                    for(int col = 0;col<n;col++)
                        for (int ind = 0;ind<k;ind++)
                            c[row*n+col]+=a[row*k+ind]*b[ind*n+col];
                MPI_Send(c,pblocks*n,MPI_DOUBLE,0,4,MPI_COMM_WORLD);
        }
    MPI_Finalize();
}
