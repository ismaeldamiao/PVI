#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../include/pvi.h"

static double buf[3];
static double alpha;
static double t;
static FILE *arquivo;

#define S (buf[0])
#define I (buf[1])
#define R (buf[2])

static double dot_S(void){ return - alpha * S * I; }
static double dot_I(void){ return alpha * S * I - I; }
static double dot_R(void){ return I; }
static typeof(double(void)) *g[] = { dot_S, dot_I, dot_R };
#define f(i, t, x)   (g[i])()
#define N            (S + I + R)

static bool escrever_arquivo(void);
#undef  PVI_FAC_ALIQUID
#define PVI_FAC_ALIQUID if(!escrever_arquivo()) break;

int main(void){

   arquivo = fopen("dados.dat", "w");
   if(arquivo == NULL){
      fputs("Erro ao abrir arquivo", stderr);
      return EXIT_FAILURE;
   }

   alpha = 5.;

   t = 0.0;
   S = 0.9;
   I = 1.0 - S;
   R = 0.0;

   pvi_dimensio = 3;
   pvi_finalis = 10.0;
   pvi_h = 1.0e-1;

   PVI_INTEGRATOR_EULER(t, buf, f);

   fclose(arquivo);

   return EXIT_SUCCESS;
}

static bool escrever_arquivo(void){
   if(fabs(N - 1.0) > 1.0e-8){
      fputs("A populacao nao estah conservando.\n", stderr);
      return false;
   }
   fprintf(arquivo, "%g %g %g %g \n", t, S, I, R);
   return true;
}
