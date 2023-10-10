/* Create macros so that the matrices are stored in column-major order */
#include <omp.h>
#define A(i,j) a[ (j)*lda + (i) ]
#define B(i,j) b[ (j)*ldb + (i) ]
#define C(i,j) c[ (j)*ldc + (i) ]

/* Routine for computing C = A * B + C */
// void print_row_matrix( int m, int n, double *a, int lda );
// void print_matrix( int m, int n, double *a, int lda );

void MY_MMult( int m, int n, int k, double *a, int lda, 
                                    double *b, int ldb,
                                    double *c, int ldc )
{
  // print_row_matrix(m,k,a,lda);
  // print_row_matrix(k,n,b,ldb);

    #pragma omp parallel for
    for(int i=0; i< m;i++){    //C[i] 
        for(int j=0; j<n ;j++){  //C[i][j]
            for(int p=0; p< k; p++){  
                C( i,j ) += A( i,p ) * B( p,j ); 
             }
        }
    }
  // print_row_matrix(m,n,c,ldc);
}


  
