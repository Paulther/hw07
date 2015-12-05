#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

double f (double x, void *params);
void integral_gen (int nmin, int nmax, double vals[]);

double f (double x, void *params)
{
       double n = *(double *) params;
       double f = exp (-x) *pow (x, n);
     
       return f;
}

void integral_gen (int nmin, int nmax, double vals[])
{
       double result;
       double error;
       size_t np = 1000;
       gsl_integration_workspace *w = gsl_integration_workspace_alloc (np);
       gsl_function F;

       for (double n = nmin; n <= nmax; n++)
       {
            F.function = &f;
            F.params = &n;
   
            gsl_integration_qag( &F, 0., 1., 0., 1.e-7, np, GSL_INTEG_GAUSS15, w, &result, &error);
            vals[(int) n] = result;
       }
}


