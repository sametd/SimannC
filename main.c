#include <stdio.h>
#include "config.h"
#include "initialSAreport.h"

int main(int argc, char *argv[]) {
  // Simann parametreleri
  // DOC n: parametre sayisi
  // DOC neps: epsilon degeri ile baglantili olarak, kac defa hic degisim
  // DOC       olmuyorsa onu sayarak programin bitis durumunu ayarliyor.
  // DOC       4 degeri oneriliyor
  int n = 2;
  int neps = 4;
  // DOC lb: parametreler icin alt sinir arrayi
  // DOC ub: parametreler icin ust sinir arrayi
  // DOC x: parametreler icin baslangic degerlerinin bulundugu array
  // DOC xopt: optimize parametrelerin bulunacagi array
  // DOC c: adim uzunlugu ayarlamasini kontrol eden vektor. 2 degeri oneriliyor
  // DOC vm: adim uzunlugu vektoru. Baslangicta en az lb ile ub arasindaki
  // DOC     farki kapsamali parametre degerleri aranirken
  // DOC     x(i)-vm(i) ve x(i)+vm(i) arasindaki degerler denenir
  // DOC fopt: optimize olmus fonksiyon degeri bu degiskene yazilacak
  double lb[n], ub[n], x[n], xopt[n], c[n], vm[n], fopt;
  // DOC nfcnev: toplam objektif fonksiyonun cagirilma sayisi
  // DOC ier: hata olmasi durumunda hatanin ne oldugunu raporlayan parametre
  //         0: programin hatasiz bittigini gosterir
  //         2: parametrelerin baslangic degerleri lb altinda veya ub ustunde
  //         3: baslangic sicakligi negatif
  // DOC iprint: ekrana hangi raporun yazilacagini kontrol eder
  // DOC         0: hicbir sey yazilmaz
  // DOC         1: nt*ns*n iterasyonda bir yazilan sicaklik degeri,
  // DOC            o anki optimal parametreler, fonksiyon degeri,
  // DOC            objektifin kac kere cagirildigi gibi bilgileri yazdiran
  // DOC            kontrol anahtari

  return 0;
}