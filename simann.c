#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "simannFuncs.h"

#define TRUE 1
#define FALSE 0
#define randomNum (((double)rand()) / ((double)(RAND_MAX)))

void simann(double *param, double *fval) {
  // Simann parametreleri
  // DOC lb: parametreler icin alt sinir arrayi
  // DOC ub: parametreler icin ust sinir arrayi
  // DOC x: parametreler icin baslangic degerlerinin bulundugu array
  // DOC xopt: optimize parametrelerin bulunacagi array
  // DOC c: adim uzunlugu ayarlamasini kontrol eden vektor. 2 degeri oneriliyor
  // DOC vm: adim uzunlugu vektoru. Baslangicta en az lb ile ub arasindaki
  // DOC     farki kapsamali parametre degerleri aranirken
  // DOC     x(i)-vm(i) ve x(i)+vm(i) arasindaki degerler denenir
  // DOC fopt: optimize olmus fonksiyon degeri bu degiskene yazilacak
  double lb[Nparam], ub[Nparam], xopt[Nparam], c[Nparam], vm[Nparam], fopt;
  // DOC nfcnev: toplam objektif fonksiyonun cagirilma sayisi
  // DOC iprint: ekrana yazilan raporun detayini kontrol eder
  // DOC         0: hicbir sey yazilmaz
  // DOC         1: nt*ns*n iterasyonda bir yazilan sicaklik degeri,
  // DOC            o anki optimal parametreler, fonksiyon degeri,
  // DOC            objektifin kac kere cagirildigi gibi bilgileri yazdiran
  // DOC            kontrol anahtari
  // DOC         2: vm, o andaki optimal parametreler
  // DOC         3: her yeni fonksiyon kabulunde ve reddinde yazar
  // DOC            asiri fazla output nedeniyle sadece kodu anlama amaciyla
  // DOC            kullanilmalidir
  // DOC nacc: kabul edilen foksiyon hesaplarinin sayisidir
  // DOC nobds: lb altinda veya ub ustundeki denemelerin sayisi
  int nfcnev, iprint, nacc, nobds;
  // Buradan sonrasi internal kullanildiklari yerlerde comment olacak
  double f, fp, p, pp, ratio, xp[Nparam], fstar[neps], t;
  int nup, ndown, nrej, nnew, lnobds, h, i, j, m, nacp[Nparam], z;
  int quit, finishCriteria;
  // Oncelikle baslangic parametrelerini ayarlayalim
  iprint = 1;
  for (i = 0; i < Nparam; i++) {
    c[i] = 2.;
    vm[i] = 1.;
    lb[i] = 0.;
    ub[i] = 1.;
    param[i] = randomNum;
  }
  t = startTemp;
  // Ayarlar yarlar ekrana yaziliyor
  initialPrints(t, iprint, param, vm, lb, ub, c);
  finishCriteria = FALSE;
  nacc = 0;
  nobds = 0;
  nfcnev = 0;
  // Optimize parametre degiskenine baslangic degeri olarak random
  // parametrelerini veriyorum, kabul edilen parametre sayisi degiskenine de ilk
  // deger atiyorum, fstar fonksiyon degerinin kac sicakliktir degismedigini
  // tutuyor, ona da ilk deger atiyorum
  for (i = 0; i < Nparam; i++) {
    xopt[i] = param[i];
    nacp[i] = 0;
  }
  for (i = 0; i < neps; i++) {
    fstar[i] = 1.;
  }
  // t 0 veya negatifse programi durduruyorum, hata mesaji veriyorum
  if (t <= 0.0) {
    printf("!!!!!!!!!THE INITIAL TEMPERATURE IS NOT POSITIVE.!!!!!!!\n");
    printf("  reset the variable t. \n");
    exit(0);
  }
  // Eger baslangic parametrelerim ln altinda veya ub ustundeyse hata mesaji
  // verip duruyorum
  for (i = 0; i < Nparam; i++) {
    if ((param[i] > ub[i]) || (param[i] < lb[i])) {
      prt1();
      exit(0);
    }
  }
  // Rastgele parametrelerimle objektif fonksiyonun ilk degerini hesapliyorum
  f = objectiveFunc(param);
  // Eger simann minimizasyon yapacaksa isaretini degistiriyorum, burada
  // karisiklik olmasin iterasyonlar sonrasinda bu isareti tekrar geri
  // getiriyorum
  if (!max) f = (-1.) * f;
  // Bir kere fonksiyon hesapladigim icin sayac degerlerine yaziyorum
  nfcnev = nfcnev + 1;
  fopt = f;
  fstar[0] = f;
  // Programin verbosity degerine gore (iprint) ekrana baslangic parametrelerini
  // ve fonksiyon degerini yaziyorum
  if (iprint >= 1) prt2(param, f);
  // Ana dongunun basladigi yer, maxeval iptal edildiginden finish criteria true
  // olunca bitecek
  do {
    // Sayaclarimin ilk degerlerini veriyorum
    nup = 0;
    nrej = 0;
    nnew = 0;
    ndown = 0;
    lnobds = 0;
    // Toplam nt iterasyon sonunda sicaklik dusuyor
    for (m = 0; m < nt; m++) {
      // Her ns iterasyon sonunda adim uzunluklari ayarlanacak
      for (j = 0; j < ns; j++) {
        for (h = 0; h < Nparam; h++) {
          // xp degiskenine deneme parametrelerini dolduracagim
          for (i = 0; i < Nparam; i++) {
            // her h dongude bir h indisli parametreyi adim uzunlugu araliginda
            // degistirecegim
            if (i == h) {
              xp[i] = param[i] + (2 * randomNum - 1.) * vm[i];
            } else {
              xp[i] = param[i];
            }
            // Deneme parametresi ub ustu veya lb altindaysa onlarin arasinda
            // olacak sekilde ayarliyorum
            if ((xp[i] < lb[i]) || (xp[i] > ub[i])) {
              xp[i] = lb[i] + (ub[i] - lb[i]) * randomNum;
              lnobds = lnobds + 1;
              nobds = nobds + 1;
              if (iprint >= 3) prt3(xp, param, f);
            }
          }
          // Fonksiyon degerini deneme parametreleriyle hesaplayip fp olarak
          // donduruyorum
          fp = objectiveFunc(xp);
          if (!max) fp = (-1.) * fp;
          nfcnev = nfcnev + 1;
          if (iprint >= 3) prt4(xp, param, fp, f);
          // Fonksiyon degeri daha iyiyse parametreleri kabul ediyorum

          if (fp >= f) {
            if (iprint >= 3) printf("  POINT ACCEPTED");
            for (z = 0; z < Nparam; z++) {
              param[z] = xp[z];
            }
            f = fp;
            nacc = nacc + 1;
            nacp[h] = nacp[h] + 1;
            nup = nup + 1;
            // Deger diger butun parametrelerle elde edilenlerden iyiyse optimum
            // olarak kabul ediyorum
            if (fp >= fopt) {
              if (iprint >= 3) printf("  NEW OPTIMUM");
              for (z = 0; z < Nparam; z++) {
                xopt[z] = xp[z];
              }
              fopt = fp;
              nnew = nnew + 1;
            }
          }
          // Eger parametrelerin fonksiyon degeri daha kotuyse metropolis
          // kullanarak secip secmeyecegime karar verecegim
          else {
            p = exprep((fp - f) / t);
            pp = randomNum;
            if (pp < p) {
              if (iprint >= 3) prt6();
              for (z = 0; z < Nparam; z++) {
                param[z] = xp[z];
              }
              f = fp;
              nacc = nacc + 1;
              nacp[h] = nacp[h] + 1;
              ndown = ndown + 1;
            } else {
              nrej = nrej + 1;
              if (iprint >= 3) prt7();
            }
          }
        }  // h nin bittigi yer (Nparam)
      }    // j nin bittigi yer (NS)
      // Adim uzunlugunu hesaplamalarin yarisi kabul edilecek sekilde
      // ayarliyorum
      for (i = 0; i < Nparam; i++) {
        ratio = nacp[i] / ns;
        if (ratio > 0.6) {
          vm[i] = vm[i] * (1. + c[i] * (ratio - 0.6) / 0.4);
        } else if (ratio < 0.4) {
          vm[i] = vm[i] / (1.0 + c[i] * ((0.4 - ratio) / 0.4));
        }
        if (vm[i] > (ub[i] - lb[i])) {
          vm[i] = ub[i] - lb[i];
        }
      }
      if (iprint >= 2) prt8(vm, xopt, param);
      for (i = 0; i < Nparam; i++) {
        nacp[i] = 0.;
      }
    }  // m nin bittigi yer (NT)
    // Sicaklik dusecegi icin raporumu yaziyorum
    if (iprint >= 1) prt9(t, xopt, vm, fopt, nup, ndown, nrej, lnobds, nnew);
    // Fonksiyon degerinin optimize olup olmadigina karar verecegim
    quit = FALSE;
    fstar[0] = f;
    if ((fopt - fstar[0]) <= eps) quit = TRUE;
    for (i = 0; i < neps; i++) {
      if (fabs(f - fstar[i]) > eps) quit = FALSE;
    }
    // Bitis kriteri karsilandiysa programi sonlandiriyorum
    if (quit) {
      for (i = 0; i < Nparam; i++) {
        param[i] = xopt[i];
      }
      if (!max) fopt = -fopt;
      if (iprint >= 1) prt10();
      *fval = fopt;
      finishCriteria = TRUE;
      return;
    }
    // Eger optimizasyon bitmediyse sicaklik dusuruyorum
    t = rt * t;
    for (i = neps; i > 0; i--) {
      fstar[i] = fstar[i - 1];
    }
    f = fopt;
    for (i = 0; i < Nparam; i++) {
      param[i] = xopt[i];
    }
    // Basa donuyorum
  } while (finishCriteria != TRUE);
}
