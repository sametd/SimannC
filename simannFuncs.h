void prtvec(double *vector, int ncols, char *message);
void prt1();
void prt2(double param[Nparam], double f);
void prt3(double xp[Nparam], double param[Nparam], double f);
void prt4(double xp[Nparam], double param[Nparam], double fp, double f);
void prt6();
void prt7();
void prt8(double vm[Nparam], double xopt[Nparam], double param[Nparam]);
void prt9(double t, double xopt[Nparam], double vm[Nparam], double fopt,
          int nup, int ndown, int nrej, int lnobds, int nnew);
void prt10();
void initialPrints(double t, int iprint, double param[Nparam],
                   double vm[Nparam], double lb[Nparam], double ub[Nparam],
                   double c[Nparam]);
double objectiveFunc(double param[Nparam]);
double exprep(double rdum);