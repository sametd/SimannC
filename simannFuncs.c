#include <math.h>
#include <stdio.h>
#include "config.h"

void prtvec(double *vector, int ncols, char *message) {
  int i, j;
  printf("%s\n", message);
  if (ncols > 10) {
    for (i = 0; i < ncols; i++) {
      printf("%12.8f  ", vector[i]);
      if ((i % 10) == 9) printf("\n");
    }
    printf("\n");
  } else {
    for (j = 0; j < ncols; j++) {
      printf("%12.8f  ", vector[j]);
    }
    printf("\n");
  }
}

void prt1() {
  printf("THE STARTING VALUE (X) IS OUTSIDE THE BOUNDS\n");
  printf("(lb AND ub). execution terminated without any\n");
  printf("optimization. respecify param, ub OR lb so that\n");
  printf("lb(i) < x(i) < ub(i), i = 1, n.\n");
}

void prt2(double param[Nparam], double f) {
  printf("\n");
  prtvec(param, Nparam, "INITIAL X");
  if (max) {
    printf("INITIAL F: %20.15f \n", f);
  } else {
    printf("INITIAL F: %20.15f \n", -f);
  }
}

void prt3(double xp[Nparam], double param[Nparam], double f) {
  printf("\n");
  prtvec(param, Nparam, "CURRENT X");
  if (max) {
    printf("CURRENT F: %20.15f \n", f);
  } else {
    printf("CURRENT F: %20.15f \n", -f);
  }
  prtvec(xp, Nparam, "TRIAL X");
  printf("POINT REJECTED SINCE OUT OF BOUNDS\n");
}

void prt4(double xp[Nparam], double param[Nparam], double fp, double f) {
  printf("\n");
  prtvec(param, Nparam, "CURRENT X");
  if (max) {
    printf("CURRENT F: %20.15f \n", f);
    prtvec(xp, Nparam, "TRIAL X");
    printf("RESULTING F:%20.15f \n", fp);
  } else {
    printf("CURRENT F: %20.15f \n", -f);
    prtvec(xp, Nparam, "TRIAL X");
    printf("RESULTING F:%20.15f \n", -fp);
  }
}

void prt6() {
  if (max) {
    printf("THOUGH LOWER, POINT ACCEPTED\n");
  } else {
    printf("THOUGH HIGHER, POINT ACCEPTED\n");
  }
}

void prt7() {
  if (max) {
    printf("LOWER POINT REJECTED\n");
  } else {
    printf("HIGHER POINT REJECTED\n");
  }
}

void prt8(double vm[Nparam], double xopt[Nparam], double param[Nparam]) {
  printf("intermediate results after step length adjustment\n");
  prtvec(vm, Nparam, "NEW STEP LENGTH (VM)");
  prtvec(xopt, Nparam, "CURRENT OPTIMAL X");
  prtvec(param, Nparam, "CURRENT X");
  printf("\n");
}

void prt9(double t, double xopt[Nparam], double vm[Nparam], double fopt,
          int nup, int ndown, int nrej, int lnobds, int nnew) {
  int totmov;
  totmov = nup + ndown + nrej;
  printf("intermediate results before next temperature reduction\n");
  printf("CURRENT TEMPERATURE: %12.5e\n", t);
  if (max) {
    printf("MAX FUNCTION VALUE SO FAR: %20.15lf\n", fopt);
    printf("TOTAL MOVES: %8d\n", totmov);
    printf("UPHILL: %8d\n", nup);
    printf("ACCEPTED DOWNHILL: %8d\n", ndown);
    printf("REJECTED DOWNHILL: %8d\n", nrej);
    printf("OUT OF BOUNDS TRIALS: %8d\n", lnobds);
    printf("NEW MAXIMA THIS TEMPERATURE: %8d\n", nnew);
  } else {
    printf("MIN FUNCTION VALUE SO FAR: %8.8lf\n", -fopt);
    printf("TOTAL MOVES: %8d\n", totmov);
    printf("DOWNHILL: %8d\n", nup);
    printf("ACCEPTED UPHILL: %8d\n", ndown);
    printf("REJECTED UPHILL: %8d\n", nrej);
    printf("TRIALS OUT OF BOUNDS: %8d\n", lnobds);
    printf("NEW MINIMA THIS TEMPERATURE: %8d\n", nnew);
  }
  prtvec(xopt, Nparam, "CURRENT OPTIMAL X");
  prtvec(vm, Nparam, "STEP LENGTH (VM)");
  printf("\n");
}

void prt10() { printf("  SA ACHIEVED TERMINATION CRITERIA. \n"); }

void initialPrints(double t, int iprint, double param[Nparam],
                   double vm[Nparam], double lb[Nparam], double ub[Nparam],
                   double c[Nparam]) {
  printf("SIMULATED ANNEALING STARTING\n");
  printf("NUMBER OF PARAMETERS:%3d \t MAXIMIZATION: %d \n", Nparam, max);
  printf("INITIAL TEMP:%8.2f \t RT:%8.2f \t EPS:%8.2f \n", t, rt, eps);
  printf("NS:%3d \t NT:%3d \t NEPS: %3d \n", ns, nt, neps);
  printf("IPRINT:%d \n", iprint);
  prtvec(param, Nparam, "STARTING VALUES");
  prtvec(vm, Nparam, "INITIAL STEP LENGTH");
  prtvec(lb, Nparam, "LOWER BOUND");
  prtvec(ub, Nparam, "UPPER BOUND");
  prtvec(c, Nparam, "C VECTOR");
  printf("  ****  ****  ****  **** \n");
}

double exprep(double rdum) {
  double fnVal;
  if (rdum > 174.) {
    fnVal = 3.69;
  } else if (rdum < -180.) {
    fnVal = 0.;
  } else {
    fnVal = exp(rdum);
  }
  return fnVal;
}