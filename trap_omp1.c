#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
int     N = atoi( argv[1] );
double dx = 2./(N-1);
double integral = 0.0;
const double pi = 3.141592653589793;
double x, f;
#pragma omp parallel for private (x,f)
for (int i=0;i<N;++i) {
x = -1. + dx*i;
// compute x_i
f = 1. / (1. + x*x);
// compute f_i = f(x_i)
printf("thread %i, x =%f, f=%f\n",omp_get_thread_num(),x,f);
// for diagnostics
critical: integral += dx*f;
}
// end points of trapezoidal rule treated specially
x = -1.0;
f = 1. / (1. + x*x);
// compute f_i = f(x_i)
integral -= 0.5*dx*f;
x = 1.0;
f = 1. / (1. + x*x);
// compute f_i = f(x_i)
integral -= 0.5*dx*f;
//printf("integral = %f , error = %e\n",integral, integral - pi / 2.);
printf("%i %f %e\n",N, integral, integral - pi / 2.);
return 0;
}
