#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#include "../../include/pvi.h"

static double buf[2];
static double gamma;
static double t;
static FILE *arquivo;

#define Q (buf[0])
#define P (buf[1])

static double dot_Q(void){ return P; }
static double dot_P(void){ return (-(Q + gamma * P) + 1.0); }
static typeof(double(void)) *g[] = { dot_Q, dot_P };
#define f(i, t, x)   (g[i])()

static bool escrever_arquivo(void);
#undef  PVI_FAC_ALIQUID
#define PVI_FAC_ALIQUID if(!escrever_arquivo()) break;

int main(void){

   arquivo = fopen("dados.dat", "w");
   if(arquivo == NULL){
      fputs("Erro ao abrir arquivo", stderr);
      return EXIT_FAILURE;
   }

   gamma = 0.5;

   t = 0.0;
   Q = 0.0;
   P = 0.0;

   pvi_dimensio = 2;
   pvi_finalis = 10.0;
   pvi_h = 1.0e-1;

   PVI_INTEGRATOR_RK4(t, buf, f);

   fclose(arquivo);

   return EXIT_SUCCESS;
}

static bool escrever_arquivo(void){
   fprintf(arquivo, "%g %g %g\n", t, Q, P);
   return true;
}
