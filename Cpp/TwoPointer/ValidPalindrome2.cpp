/*
 * LECȚIE — Palindrom după ștergerea a cel mult un caracter
 *
 * Studentule, testul strict de palindrom respinge la prima nepotrivire.
 * Aici ți se permite o ștergere. Gradul ăla de libertate tot se
 * rezolvă cu doi pointeri; n-ai nevoie să încerci să ștergi fiecare
 * caracter.
 *
 * Problemă
 *   Întoarce true dacă s poate fi palindrom după ce scoți cel mult un
 *   caracter (inclusiv să nu scoți niciunul). Exemplu: "abdeddba" e
 *   true.
 *
 * Intuiție / Algoritm
 *   Umblă spre interior ca la un palindrom normal. Cât timp s[i] == s[j],
 *   continuă. La prima nepotrivire trebuie să folosești ștergerea: fie
 *   sari s[i] și întreabă dacă s[i+1..j] e palindrom, fie sari s[j]
 *   și întreabă dacă s[i..j-1] e palindrom. Dacă oricare subinterval
 *   e palindrom, o ștergere e de ajuns. Dacă amândouă eșuează, rămân
 *   două sau mai multe nepotriviri și respingi.
 *
 *   Te ramifici doar la prima nepotrivire. O a doua nepotrivire în
 *   interiorul unui subinterval candidat e fatală pentru candidatul ăla.
 *   Asta e de ajuns, pentru că orice ștergere unică validă care repară
 *   șirul trebuie să șteargă unul din cele două capete care nu se
 *   potrivesc (sau un caracter pe care skip-ul ăsta îl simulează).
 *   Nu cauți mai întâi interiorul; capetele sunt obstacolul.
 *
 * Complexitate
 *   Timp  O(n): plimbarea exterioară plus cel mult două verificări de
 *   palindrom pe un sufix al șirului. Fiecare caracter e comparat de
 *   O(1) ori.
 *   Memorie extra O(1): doar indici. Copierea de substring-uri în
 *   buffer-e noi ar copia octeți și ar umfla și timpul, și memoria.
 *   Transmite indici în buffer-ul original.
 *
 * Memorie
 *   char s[] decade la char*. Transmite n pentru că pointerul n-are
 *   lungime. Helper-ul citește s[i]..s[j] după indice. Fără alocare de
 *   substring. Evităm vector dinadins. În C ai transmite (char *s,
 *   int i, int j) și n-ai copia niciodată o bucată afară.
 *
 *   Caracterele sunt contigue. Doar încărcăm. În main, n e
 *   sizeof(s) - 1 ca să nu numărăm '\0'-ul terminator.
 *
 * Teorie C — indici pe un tablou de octeți, fără mutație, overflow, UB
 *   s[i] e un char într-un tablou contig. i și j sunt int. Helper-ul
 *   rulează cât timp i < j, deci j-- e sigur: j e cel puțin i+1.
 *   Formarea lui j = n - 1 pe un șir gol e un indice prost; tratăm
 *   lungimea < 2 ca deja true înainte de asta.
 *
 *   Lecția asta nu sare punctuația. Fiecare caracter contează.
 *   Exemplul e doar litere mici. Să amesteci asta cu filtrul
 *   alfanumeric e o specificație diferită; nu le combina în tăcere.
 *
 *   Comparația e egalitate brută pe char. Fără ctype, fără locale.
 *
 *   Stivă: helper-ul e iterativ. Dacă ai scrie un palindrom recursiv
 *   pe n/2, ai putea umple stiva. Iterația ține un cadru constant.
 *
 *   Cache: secvențial de la ambele capete, apoi cel mult două scanări
 *   secvențiale în plus pe un subinterval. Tot streaming liniar.
 *
 *   Mutația pe loc nu e folosită. Ștergerea unui caracter e simulată
 *   sărind un indice, nu prin memmove al cozii. Șirul apelantului
 *   rămâne neschimbat. Asta e important: o ștergere reală ar fi O(n)
 *   mutări pe un buffer contig, pe care n-ai vrea-o în interiorul unei
 *   bucle de candidați.
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

bool validPalindrome(char s[], int n) {
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
    char s[] = "abdeddba";
    int n = sizeof(s) / sizeof(s[0]) - 1;
    if (validPalindrome(s, n)) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    return 0;
}
