#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#include "../../../include/pvi.h"

static double t;
static double x[2];
#define f(i, t, x) (F[i])()

static double gamma;

static double dot_x0(void){ return x[1]; }
static double dot_x1(void){ return -(x[0] + gamma * x[1] + 1.0); }
static typeof(double(void)) *F[] = { dot_x0, dot_x1 };

static FILE *arquivo;
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
   x[0] = 0.0;
   x[1] = 0.0;

   pvi_dimensio = 2;
   pvi_finalis = 20.0;
   pvi_h = 1.0e-1;

   PVI_INTEGRATOR_RK4(t, x, f);

   fclose(arquivo);

   return EXIT_SUCCESS;
}

static bool escrever_arquivo(void){
   fprintf(arquivo, "%g %g %g\n", t, x[0], x[1]);
   return true;
}