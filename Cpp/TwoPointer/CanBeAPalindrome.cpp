/*
 * LECȚIE — Poate șirul deveni palindrom ștergând cel mult unul?
 *
 * Studentule, asta e aceeași procedură de decizie ca ValidPalindrome2.
 * Încadrarea e întrebarea pe care trebuie s-o spui cu voce tare: nu
 * „e palindrom,” ci „e la cel mult o editare distanță de a fi unul,”
 * unde singura editare e ștergerea. Scrie-o ca o funcție a ei, ca
 * specificația să rămână în nume.
 *
 * Problemă
 *   Dat un șir de caractere care toate contează (fără filtru de
 *   punctuație), întoarce true dacă poți șterge cel mult un caracter
 *   și obține un palindrom. Ștergerea a zero caractere e permisă.
 *   Exemplu: "aebbeba" e true (șterge 'e'-ul în plus sau 'b'-ul în
 *   plus de pe perechea nepotrivită, după care skip merge).
 *
 * Intuiție / Algoritm
 *   Doi pointeri de la capete. Caracterele egale își fac deja treaba
 *   de palindrom; mută-te spre interior. Prima nepotrivire e singurul
 *   loc unde cheltuiești ștergerea. Încearcă să sari caracterul din
 *   stânga: restul trebuie să fie un palindrom strict. Sau sari
 *   caracterul din dreapta. Dacă oricare încercare reușește, șirul
 *   poate fi palindrom. Dacă pointerii se întâlnesc fără nepotrivire,
 *   deja e unul.
 *
 *   De ce să nu încerci fiecare ștergere: sunt n candidați, fiecare
 *   verificare e O(n), total O(n^2). Prima nepotrivire fixează
 *   ștergerea la unul din doi indici. Asta e structura greedy a
 *   problemei.
 *
 *   Urmărește "aebbeba":
 *     a ... a se potrivesc
 *     e ... b nepotrivire
 *     sari stânga  (bbeba din intervalul rămas): b vs b, b vs e eșuează
 *     sari dreapta (sari j, compară i..j-1 care e "ebbe"):
 *       e vs e, b vs b. Succes.
 *
 * Complexitate
 *   Timp  O(n). Memorie extra O(1). Aceleași limite ca ValidPalindrome2.
 *
 * Memorie
 *   char s[] decade la char*. Indici în buffer-ul contig existent.
 *   Transmite n. Fără șir extra. Fără trafic pe heap. Evităm vector
 *   dinadins. Helper-ul împrumută același pointer. Proprietatea rămâne
 *   la apelant. Cadrele de stivă au dimensiune constantă: câțiva int.
 *
 *   N-ai copia șirul. N-ai scrie un temporar fără octetul sărit.
 *   Skip-ul e o incrementare de indice.
 *
 * Teorie C — două priviri pe aceiași octeți, UB, cache
 *   Plimbarea exterioară și helper-ul citesc amândouă același tablou.
 *   Nu există pericol de aliasing pentru că nimeni nu scrie. Mutația
 *   concurentă ar fi o cursă pe date (UB); programul ăsta e pe un
 *   singur fir.
 *
 *   Indici int, i < j înainte de s[j] și înainte de j-1. La nepotrivire
 *   evaluăm i+1 și j-1. Pentru că i < j, j >= 1, deci j-1 e în interval,
 *   iar i+1 <= j, deci i+1 e <= ultimul indice valid. Helper-ul poate
 *   primi i == j (interval gol sau de un caracter după skip), care e
 *   palindrom și bucla nu rulează.
 *
 *   Cache: tot secvențial. A doua scanare a helper-ului poate reciti
 *   octeți pe care primul helper i-a atins deja; rămân fierbinți în L1.
 *
 *   Fără overflow, fără ctype. Fără mutație pe loc: ștergerea e virtuală.
 *   O ștergere fizică într-un șir contig e memmove al cozii și un
 *   decrement de lungime. Făcând asta o dată e O(n). Făcând-o pentru
 *   fiecare candidat e timpul O(n^2) și scrierile O(n) pe care le-ai
 *   evitat.
 *
 *   Întoarcerea unui bool e un octet într-un registru, în practică.
 *   Tipărim textul true sau false.
 */

#include <iostream>
using namespace std;

bool isPalindromeRange(char s[], int i, int j) {
    while (i < j) {
        if (s[i] != s[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

bool canBeAPalindrome(char s[], int n) {
    if (n < 2) {
        return true;
    }
    int i = 0;
    int j = n - 1;
    while (i < j) {
        if (s[i] != s[j]) {
            return isPalindromeRange(s, i + 1, j) || isPalindromeRange(s, i, j - 1);
        }
        i++;
        j--;
    }
    return true;
}

int main() {
    char s[] = "aebbeba";
    int n = sizeof(s) / sizeof(s[0]) - 1;
    if (canBeAPalindrome(s, n)) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    return 0;
}
