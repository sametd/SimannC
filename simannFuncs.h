void prtvec(double *vector, int ncols, char *message);
void prt1();
void prt2(double param[Nparam], double f);
void prt3(double *xp, double *param, double f);
void prt4(double *xp, double *param, double fp, double f);
void prt6();
void prt7();
void prt8(double *vm, double *xopt, double *param);
void prt9(double *xopt, double *vm, double fopt, int nup, int ndown,
          int nrej, int lnobds, int nnew);
void prt10();
void initialPrints(int iprint, double param[Nparam], double vm[Nparam],
                   double lb[Nparam], double ub[Nparam], double c[Nparam]);
double objectiveFunc(double param[Nparam]);
