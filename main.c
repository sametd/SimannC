#include <stdio.h>
#include "config.h"
#include "simann.h"

int main(int argc, char *argv[]) 
{
  // DOC  p: parametre arrayi
  // DOC  f: fonksiyon degeri
  double param[Nparam];
  double fval = 0.;
  simann(param,&fval);

  return 0;
}
