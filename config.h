// DOC  Nparam: parametre sayisi
#define Nparam 2
// DOC neps: epsilon degeri ile baglantili olarak, kac defa hic degisim
// DOC       olmuyorsa onu sayarak programin bitis durumunu ayarliyor.
// DOC       4 degeri oneriliyor
#define neps 4
// DOC max: maksimizasyon mu minimizasyon mu secimi. (0 minimizasyon)
#define max 0
// DOC eps: epsilon kriteri
#define eps 0.01
// DOC rt: sicakligin dusme katsayisi (ornek: yeni_t = t * rt)
#define rt 0.85
// DOC ns: NS parametresi NS*N iterasyon boyunca ayni adim
// DOC     uzunlugunda parametre aramasi yapiliyor.
#define ns 40
// DOC nt: NT parametresi ayni sicaklikta kac defa adim uzunlugu
// DOC     ayarlanarak NS*N parametre aramasi yapilacagini ifade eder
// DOC     Yani NT defa ayarlanan adim uzunluklarinin herbirinde
// DOC     NS*N defa parametre aramasi yapilir
#define nt 40
// DOC t:  Baslangic sicakligidir
#define startTemp 5.0
