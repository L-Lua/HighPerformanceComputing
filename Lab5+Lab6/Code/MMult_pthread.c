/* Create macros so that the matrices are stored in column-major order */

#define A(i,j) a[ (j)*lda + (i) ]
#define B(i,j) b[ (j)*ldb + (i) ]
#define C(i,j) c[ (j)*ldc + (i) ]
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "common_threads.h"

typedef struct {
    int lrangeX; int lrangeY; int rrangeX; int rrangeY;
    int m; int n; int k;
    double *a; int lda; double *b; int ldb; double *c; int ldc;
} myarg_t;

void dgemm(int m, int n, int k, int beta,
          double* a, double *b, double *c, int lda,int ldb,int ldc,int lrangeX, int lrangeY, int rrangeX, int rrangeY){
    for(int i=lrangeX; i<= rrangeX;i++){    //C[i]
        for(int j=lrangeY; j<=rrangeY; j++){  //C[i][j]
            C(i,j) = beta*C(i,j);
            for(int p=0; p< k; p++){
                C(i,j) += A(i,p) * B(p,j);
             }
        }
    }
}

void *mythread(void *arg) {
    myarg_t *args = (myarg_t *) arg;
    dgemm(args->m,args->n,args->k,1,args->a,args->b,args->c,args->lda,args->ldb,args->ldc,args->lrangeX, args->lrangeY, args->rrangeX, args->rrangeY);
    return NULL;
}


void MY_MMult( int m, int n, int k, double *a, int lda,double *b, int ldb,
                                    double *c, int ldc ){
    pthread_t p1,p2,p3,p4;
    myarg_t args1 = { 0, 0 , m/2-1 , n/2-1,m,n,k,a,lda,b,ldb,c,ldc};
    myarg_t args2 = { 0, n/2 , m/2-1 , n-1,m,n,k,a,lda,b,ldb,c,ldc};
    myarg_t args3 = { m/2, 0 , m-1 , n/2-1,m,n,k,a,lda,b,ldb,c,ldc};
    myarg_t args4 = { m/2, n/2 , m-1 , n-1,m,n,k,a,lda,b,ldb,c,ldc};
    Pthread_create(&p1, NULL, mythread, &args1);
    Pthread_create(&p2, NULL, mythread, &args2);
    Pthread_create(&p3, NULL, mythread, &args3);
    Pthread_create(&p4, NULL, mythread, &args4);
    Pthread_join(p1, NULL); Pthread_join(p2, NULL);
    Pthread_join(p3, NULL); Pthread_join(p4, NULL);
   //print_row_matrix(m,n,c,ldc);
}
