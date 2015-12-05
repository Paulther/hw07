#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

void integral_recur ( int nmin, int nmax, double vals[]);

void integral_recur (int nmin, int nmax, double vals[])
{
    double IN = 0;
    int i = nmax - 1;
    vals [nmax] = IN;
    while ( i >= nmin)
    {
        vals[i] = (IN + exp (-1.))/((double) i);
        i = i - 1;
    }
}

