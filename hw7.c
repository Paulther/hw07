#include <stdio.h>
#include <math.h>
#include  <gsl/gsl_integration.h>

#include "timer.h"
#include "timer.c"
#include "adjust.c"
#include "integral_recur.c"
#include "integral_gen.c" 

#define NMAX 100

double vals1[NMAX + 1], vals2[NMAX + 1];

void integral_recur (int nmin, int nmax, double vals[]);
void integral_gen (int nmin, int nmax, double vals[]);
int adjust_rep_count (int n, double z, double x, double y);

int main (void)
{
    printf ("Recursion Relationship Interal Calculation:\n\n");
    printf ("   Terms        Value\n");

    /*Calculates the Integral using the recursion relationship
     */
      
    integral_recur (1, NMAX, vals1);
    for (int i = 1; i < NMAX +1; i++)
    {
        printf ("%8d     %20.15f\n", i, vals1[i]);
    }  
    printf ("\n\n");

    printf ("GSL Integrator Interal Calculation:\n\n");
    printf ("   Terms        Value\n");

    /*Calculates the Integral using the recursion relationship
     */

    integral_gen (1, NMAX, vals2);
    for (int i1 = 1; i1 < NMAX +1; i1++)
    {
        printf ("%8d     %20.15f\n", i1, vals2[i1]);
    }    
    printf ("\n\n");


    double time;
    double time1;
    double time2;
    int j;
    double tmax = 2;
    double tmin = 1;
    int count = 1000;

    printf ("Timing the Recursion Relationship:\n\n");
    printf ("   Time/Iteration          Total Time           Iterations\n");
    do
    {

        timer_start ();

        for (j = 0; j < count; j++)
        {
            integral_recur(1, NMAX, vals1);
        }

        //adjust count such that cpu time is between tmin and tmax

        time = timer_stop ();
        time1 = time / ((double) count);
        printf (" %10.2f usec         %10.6f sec      %10d\n", time1 * 1.e6,
            time, count);
        count = adjust_rep_count ((int) count, time, tmin, tmax);

    }
    while ((time > tmax) || (time < tmin));
    printf ("\n\n");

    count = 1000;

    printf ("Timing the GSL Integrator:\n\n");
    printf ("   Time/Iteration          Total Time           Iterations\n");
    do
    {

        timer_start ();

        for (j = 0; j < count; j++)
        {
            integral_gen(1, NMAX, vals2);
        }

        time = timer_stop ();

        //adjust count such that cpu time is between tmin and tmax

        time2 = time / ((double) count);
        printf (" %10.2f usec         %10.6f sec      %10d\n", time2 * 1.e6,
            time, count);
        count = adjust_rep_count ((int) count, time, tmin, tmax);

    }
    while ((time > tmax) || (time < tmin));
    printf ("\n\n");
    double q = time2 / time1;

    printf ("Speed up Factor: %10.2f\n\n", q);
}
