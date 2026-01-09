#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#include "../../include/pvi.h"

#undef PVI_CORPUS
#define PVI_CORPUS double _Complex

static double complex Psi[2];
static double complex alpha, beta;
static double t, D[4][4];
static FILE *arquivo;
static int exit_code;

#define dot_Psi(i, t, X) (\
   D[i][0]*(X)[0] + D[i][1]*(X)[1] + D[i][2]*(X)[2] + D[i][3]*(X)[3])

static bool escrever_arquivo(void);
#undef  PVI_FAC_ALIQUID
#define PVI_FAC_ALIQUID if(!escrever_arquivo()) break;

int main(void){

   exit_code = EXIT_SUCCESS;

   arquivo = fopen("dados.dat", "w");
   if(arquivo == NULL){
      fputs("Erro ao abrir arquivo", stderr);
      return EXIT_FAILURE;
   }

   alpha = CMPLX(0.0, 1.0);
   beta  = CMPLX(0.1, 0.3);

   // D[0][0] = alpha;        D[0][1] = beta;
   // D[1][0] = -conj(beta);  D[1][1] = -alpha;

   double complex z = alpha;
   D[0][0] = creal(z);  D[0][1] = -cimag(z);
   D[1][0] = cimag(z);  D[1][1] = creal(z);

   z = beta;
   D[0][2] = creal(z);  D[0][3] = -cimag(z);
   D[1][2] = cimag(z);  D[1][3] = creal(z);

   z = -conj(beta);
   D[2][0] = creal(z);  D[2][1] = -cimag(z);
   D[3][0] = cimag(z);  D[3][1] = creal(z);

   z = -alpha;
   D[2][2] = creal(z);  D[2][3] = -cimag(z);
   D[3][2] = cimag(z);  D[3][3] = creal(z);

   t = 0.0;
   Psi[0] = CMPLX(0.85, 0.0);
   Psi[1] = CMPLX(sqrt(1.0 - 0.85*0.85), 0.0);

   pvi_dimensio = 4;
   pvi_finalis = 10.0;
   pvi_h = 1.0e-4;

   PVI_INTEGRATOR_EULER_SYMPLECTICUS_IMPLICITUS(t, (double*)Psi, dot_Psi);

   fclose(arquivo);

   return exit_code;
}

static bool escrever_arquivo(void){
   double norma, aux[2];
   aux[0] = cabs(Psi[0]);
   aux[0] *= aux[0];
   norma = aux[0];
   aux[1] = cabs(Psi[1]);
   aux[1] *= aux[1];
   norma += aux[1];
   if(fabs(norma - 1.0) > 1.0e-2){
      fputs("Erro: A norma nao estah conservando.\n", stderr);
      exit_code = EXIT_FAILURE;
      return false;
   }
   fprintf(arquivo, "%g %g %g\n", t, aux[0], aux[1]);
   return true;
}
