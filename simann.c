#include "config.h"
#include "simannFuncs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

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
  // DOC ier: hata olmasi durumunda hatanin ne oldugunu raporlayan parametre
  //         0: programin hatasiz bittigini gosterir
  //         2: parametrelerin baslangic degerleri lb altinda veya ub ustunde
  //         3: baslangic sicakligi negatif
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
  int nfcnev, ier, iprint, nacc, nobds;
  // Buradan sonrasi internal kullanildiklari yerlerde comment olacak
  double f, fp, p, pp, ratio, xp[Nparam], fstar[neps];
  int nup, ndown, nrej, nnew, lnobds, h, i, j, m, nacp[Nparam];
  int quit, finishCriteria;
  // Oncelikle baslangic parametrelerini ayarlayalim
  iprint = 1;
  for (i = 0; i < Nparam; i++) {
    c[i] = 2.;
    vm[i] = 1.;
    lb[i] = 0.;
    ub[i] = 1.;
    param[i] = (((double)rand()) / ((double)(RAND_MAX)));
  }
  // Ayarlar yarlar ekrana yaziliyor
  initialPrints(iprint, param, vm, lb, ub, c);
  finishCriteria = FALSE;
  nacc = 0;
  nobds = 0;
  nfcnev = 0;
  ier = 99;
  // Optimize parametre degiskenine baslangic degeri olarak random
  // parametrelerini veriyorum, kabul edilen parametre sayisi degiskenine de ilk
  // deger atiyorum, fstar fonksiyon degerinin kac sicakliktir degismedigini
  // tutuyor, ona da ilk deger atiyorum
  for (i = 0; i < Nparam; i++) {
    xopt[i] = param[i];
    nacp[i] = 0;
    fstar[i] = 1.;
  }
  // t 0 veya negatifse programi durduruyorum, hata mesaji veriyorum
  if (t <= 0.0) {
    printf("!!!!!!!!!THE INITIAL TEMPERATURE IS NOT POSITIVE.!!!!!!!\n");
    printf("  reset the variable t. \n");
    ier = 3;
    exit(0);
  }
  // Eger baslangic parametrelerim ln altinda veya ub ustundeyse hata mesaji
  // verip duruyorum
  for (i = 0; i < Nparam; i++) {
    if ((param[i] > ub[i]) || (param[i] < lb[i])) {
      prt1();
      ier = 2;
      exit(0);
    }
  }
  // Rastgele parametrelerimle objektif fonksiyonun ilk degerini hesapliyorum
  f = objectiveFunc(param);
  // Eger simann minimizasyon yapacaksa isaretini degistiriyorum, burada
  // karisiklik olmasin iterasyonlar sonrasinda bu isareti tekrar geri
  // getiriyorum
  if (!max)
    f = (-1.) * f;
  // Bir kere fonksiyon hesapladigim icin sayac degerlerine yaziyorum
  nfcnev = nfcnev + 1;
  fopt = f;
  fstar[0] = f;
  // Programin verbosity degerine gore (iprint) ekrana baslangic parametrelerini
  // ve fonksiyon degerini yaziyorum
  if (iprint >= 1)
    prt2(param, f);
  // Ana dongunun basladigi yer, maxeval iptal edildiginden finish criteria true
  // olunca bitecek
  do {

  } while (finishCriteria != TRUE);
}
