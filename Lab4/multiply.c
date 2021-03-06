//
// multiply.c - compute product of two NxN matrices (and compute CPE)
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "clock.h"
#define CMIN 40000000.0

//
// naive version -- base version, leave alone
//
void multiply_matrix_base(double *a, double *b, double *c, int N)
{
	int i, j, k;

	for (i=0; i<N; i++)
      for (j=0; j<N; j++)
        c[i*N+j]=0.0;

	for (k=0; k<N; k++)
      for (j=0; j<N; j++)
	    for (i=0; i<N; i++)
          c[i*N+j] += a[i*N+k]*b[k*N+j];
	return;
}

//
// slightly optimized version
//
void multiply_matrix_optimized(double *a, double *b, double *c, int N)
{
	int i, j, k;
    int kN;

	for (i=0; i<N; i++)
      for (j=0; j<N; j++)
        c[i*N+j]=0.0;

    kN=0;
	for (k=0; k<N; k++)
    {
      for (i=0; i<N; i++)
      {
        int iN = i*N;
	for (j=0; j<N; j++)
        {
          c[iN+j] += a[iN+k]*b[kN+j];
        }
      }
      kN+=N;
    }
	return;
}

int main(int argc, char *argv[])
{
  double cycles, Mhz;
  int cnt = 1;
  double cmeas = 0;
  double bmeas = 0;
  double cycles_naive, cycles_optimized;
  int N, N2;
  int i;

  Mhz = mhz(1);

  if (argc<2)
  {
    fprintf(stderr, "Usage: matMult <N>\n");
    exit(1);
  }
  N = atoi(argv[1]);

  double *A = malloc(N*N*sizeof(double));
  double *B = malloc(N*N*sizeof(double));
  double *C1 = malloc(N*N*sizeof(double));
  double *C2 = malloc(N*N*sizeof(double));

  // load random data into A and B;
  N2 = N*N;
  srand(time(NULL));
  for (i=0; i<N2; i++)
  {
    A[i] = ((double) (rand()%1000)/10.0 + 1.0);
    B[i] = ((double) (rand()%2000)/10.0 + 1.0);
  }

  // base run
  start_counter();
  do {
    int c = cnt;
    printf("cnt = %d\n", cnt);
    // Warm up cache
    multiply_matrix_base(A, B, C1, N);
    bmeas = get_counter();
    while (c-- > 0)
      multiply_matrix_base(A, B, C1, N);
    cmeas = get_counter();
    cycles = (cmeas-bmeas);
    cnt += cnt;
  } while ((cmeas-bmeas) < CMIN);  /* Make sure have enough */
  printf("Naive cnt = %d\n", cnt);
  printf("Naive cycles = %lf, MHz = %lf, cycles/Mhz = %lf\n", cycles, Mhz, cycles/Mhz);
  printf("Naive elapsed time per run = %lf seconds \n", (cycles/cnt)/(1.0e6*Mhz));
  cycles_naive = cycles/cnt;
  // Compute CPE - cycles per element = cycles_naive/n
  printf("Naive CPE = %lf cycles \n", cycles_naive/((double)N2));

  cnt=1;
  // optimized run
  start_counter();
  do {
    int c = cnt;
    printf("cnt = %d\n", cnt);
    // Warm up cache
    multiply_matrix_optimized(A, B, C2, N);
    bmeas = get_counter();
    while (c-- > 0)
      multiply_matrix_optimized(A, B, C2, N);
    cmeas = get_counter();
    cycles = (cmeas-bmeas);
    cnt += cnt;
  } while ((cmeas-bmeas) < CMIN);  /* Make sure have enough */
  printf("Optimized cnt = %d\n", cnt);
  printf("Optimized cycles = %lf, MHz = %lf, cycles/Mhz = %lf\n", cycles, Mhz, cycles/Mhz);
  printf("Optimized elapsed time per run = %16.12f seconds \n", (cycles/cnt)/(1.0e6*Mhz));
  cycles_optimized = cycles/cnt;
  // Compute CPE - cycles per element = cycles_optimized/n
  printf("Optimized CPE = %lf cycles \n", cycles_optimized/((double)N2));
  // Compute Speedup
  printf("Speedup = %12.8f\n", cycles_naive / (double) cycles_optimized);
  // Check computed values
  for (i=0; i<N2; i++)
  {
    if (C1[i]!=C2[i])
    {
      printf("Output differs: C1[%d] = %lf and C2[%d] = %lf\n", i, C1[i], i, C2[i]);
	  return(1);
    }
  }

  free(A);
  free(B);
  free(C1);
  free(C2);

  return(0);
}
