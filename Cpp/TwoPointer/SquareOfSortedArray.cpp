/*
 * LECȚIE — Pătratele unui tablou sortat, inclusiv negative
 *
 * Studentule, să ridici la pătrat un tablou sortat doar cu valori
 * nenegative e o singură trecere înainte: pătratele sunt deja ordonate.
 * Negativele strică asta. Magnitudinea cea mai mare stă la unul din
 * cele două capete, nu la mijloc.
 *
 * Problemă
 *   nums e sortat nedescrescător și poate conține negative. Umple un
 *   tablou nou cu pătratele, tot sortat nedescrescător. Exemplu:
 *   {-8,-6,-5,1,2,3,4} -> 1,4,9,16,25,36,64 fiecare pe linia lui.
 *
 * Intuiție / Algoritm
 *   Compară pătratele (sau magnitudinile) lui nums[l] și nums[r].
 *   Pătratul mai mare e următoarea valoare de pus la spatele
 *   rezultatului. Umple res de la indicele n-1 în jos până la 0.
 *   Avansează capătul care a donat pătratul mai mare. Pentru că fiecare
 *   pas ia pătratul maxim rămas, rezultatul e umplut în ordine sortată
 *   de la dreapta.
 *
 *   Mijlocul lui nums are valorile cele mai apropiate de zero, deci
 *   cele mai mici pătrate. Ele aterizează în fața lui res la urmă.
 *
 * Complexitate
 *   Timp  O(n).
 *   Memorie extra O(n) pentru buffer-ul rezultat. Input-ul nu e
 *   suprascris. Ai putea suprascrie nums de la spate doar dacă apelantul
 *   ar permite mutația și ai fi atent să nu calci capetele necitite —
 *   tabloul extra e proiectul cinstit și sigur aici.
 *
 * Memorie
 *   int nums[] decade la un pointer; transmite n. int res[] e un al
 *   doilea buffer de n int-uri, și el decade. Evităm vector dinadins.
 *   În main ambele tablouri sunt tablouri pe stivă ale căror dimensiuni
 *   se cunosc la compilare (sizeof initializer-ului). Funcția umple
 *   res și nu întoarce nimic: apelantul deține deja celulele de output.
 *
 *   În C ai transmite doi pointeri și o lungime. Proprietatea e
 *   explicită. Nimeni nu face malloc, nimeni nu face free.
 *
 * Teorie C — abs(INT_MIN), overflow la pătrat, cache, UB
 *   Nu clasa capetele cu abs ca int pe 32 de biți. abs(INT_MIN) nu
 *   poate fi reprezentat în complement față de doi pe 32 de biți:
 *   magnitudinea e 2^31, iar INT_MAX e 2^31-1. Apelezi abs(INT_MIN)
 *   pe int e comportament nedefinit. labs pe un long care tot e pe
 *   32 de biți are aceeași capcană. llabs pe long long e sigur pentru
 *   INT_MIN pentru că 2^31 încape pe signed pe 64 de biți.
 *
 *   Preferă să nu iei abs deloc. Compară pătratele pe 64 de biți:
 *     1LL * nums[l] * nums[l]  versus  1LL * nums[r] * nums[r]
 *   Asociativ la stânga: (1LL * nums[l]) * nums[l] promovează mai întâi,
 *   apoi înmulțește. INT_MIN * INT_MIN = 2^62, care încape pe signed
 *   pe 64 de biți (până la 2^63-1). Pătratul stocat în res tot e un
 *   int în exemplul lecției; dacă |x| > 46340, x*x nu încape pe int
 *   pe 32 de biți și să-l stochezi în int e un bug. Folosește long long
 *   pentru tipul rezultat când problema permite magnitudini mari.
 *   Aici valorile din exemplu încap, și tot calculăm comparația în
 *   long long ca ranking-ul să nu dea overflow. Scriem nums[l] * nums[l]
 *   în res doar după ranking-ul ăla, și doar pentru că exemplul e în
 *   interval.
 *
 *   Cache: citim nums de la ambele capete secvențial și scriem res
 *   de la spate secvențial. Trei fluxuri secvențiale. Tabloul rezultat
 *   poate fi rece la prima scriere; după aia liniile se umplu frumos.
 *
 *   Indici: un indice de scriere signed de la n-1 în jos până la 0 e
 *   mai simplu decât să treci prin zero unsigned. l și r rămân în
 *   interval pentru că fiecare pas consumă una din n celule. Input gol:
 *   bucla nu rulează.
 */

#include <iostream>
using namespace std;

void sortedSquares(int nums[], int n, int res[]) {
    int l = 0;
    int r = n - 1;
    for (int index = n - 1; index >= 0; index--) {
        long long left_sq = 1LL * nums[l] * nums[l];
        long long right_sq = 1LL * nums[r] * nums[r];
        if (left_sq > right_sq) {
            res[index] = nums[l] * nums[l];
            l++;
        } else {
            res[index] = nums[r] * nums[r];
            r--;
        }
    }
}

int main() {
    int nums[] = {-8, -6, -5, 1, 2, 3, 4};
    int n = sizeof(nums) / sizeof(nums[0]);
    int res[sizeof(nums) / sizeof(nums[0])];
    sortedSquares(nums, n, res);
    for (int i = 0; i < n; i++) {
        cout << res[i] << '\n';
    }
    return 0;
}
