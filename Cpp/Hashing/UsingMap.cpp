/*
 * LECȚIE — Aceeași problemă de frecvență, acum cu o tabelă hash
 *
 * Studentule, întoarce litera mică cea mai comună dintr-un șir. De data asta
 * depozitul e unordered_map<char, int>, nu int[26]. Răspunsul pentru
 * "mkbqsqjbyq" tot e 'q'. Punctul e modelul mașinii de sub mapă,
 * și când chiar ai plăti pentru el.
 *
 *   using namespace std;
 *   typedef unordered_map<char, int> Freq;
 *
 *   Scrie Freq, nu std::unordered_map. Directiva using pune
 *   unordered_map în namespace-ul global pentru fișierul ăsta.
 *
 * Intuiție
 *   O tabelă hash mapează o cheie oarecare pe un slot dintr-un
 *   tablou de bucket-uri printr-o funcție hash, apoi tratează
 *   coliziunile (de obicei chaining: o listă înlănțuită sau un
 *   arbore de noduri în bucket-ul ăla). Lookup-ul și insert-ul
 *   medii sunt O(1). Media aia ascunde un caz cel mai rău O(n)
 *   când fiecare cheie cade în același bucket, și ascunde o
 *   constantă mult mai mare decât un tablou dens.
 *
 *   Tot pliem A-Z la a-z, apoi pentru fiecare caracter: lookup,
 *   increment, și dacă noul count bate campionul, înregistrează
 *   caracterul. La egalitate rămâne primul câștigător (strict
 *   greater), ceea ce se potrivește cu o parcurgere stânga-dreapta
 *   a șirului, nu cu ordinea alfabetică. Pe exemplul ăsta n-ai
 *   egalitate.
 *
 * Complexitate
 *   Timp mediu O(n). Timp cel mai rău O(n^2) dacă hash-ul se
 *   prăbușește (sau O(n log n) pe operație dacă implementarea
 *   transformă lanțurile lungi în arbori, ceea ce unele fac).
 *   Memorie extra O(A) noduri pe heap unde A e numărul de chei
 *   distincte văzute de fapt, plus tabloul de bucket-uri.
 *
 * Memorie
 *   Nodurile unordered_map trăiesc pe heap. Fiecare inserare a
 *   unei chei noi alocă un nod: cheie, valoare, next-pointer (și
 *   mai mult). Asta nu e un tablou de numărare contig. Să parcurgi
 *   tabela mai târziu ar urmări pointeri. Noi n-o parcurgem: ținem
 *   un campion care rulează, deci nu plătim o parcurgere a tabelei
 *   întregi.
 *
 *   Obiectul mapă stă pe stivă; bucket-urile și nodurile stau pe
 *   heap. Destructorul le parcurge și le eliberează. Fără delete
 *   manual.
 *
 *   Textul e char str[], un șir C. Decade la char*. Parcurgem
 *   până la '\0'.
 *
 * Teorie C — tabele hash vs tablouri de numărare, coliziuni, cache
 *   În C ți-ai scrie tu: un tablou de bucket-uri de struct node,
 *   malloc pe fiecare cheie nouă, free la teardown. Tabela C++ e
 *   design-ul ăla cu un hash bine testat și o politică de
 *   load-factor.
 *
 *   O(1) mediu presupune un hash bun și un load factor ținut departe
 *   de „totul într-un bucket”. O(n) cel mai rău e real: chei
 *   patologice, un hash prost, sau un input advers. Nu cita O(1)
 *   ca o garanție. Citează-l ca costul așteptat.
 *
 *   Când alfabetul e uriaș sau necunoscut — Unicode, id-uri pe
 *   64 de biți, șiruri — nu poți aloca U+1 contoare. Memoria
 *   tabelei urmărește cheile distincte. Când alfabetul e 26 de
 *   litere mici, HashingLetters.cpp e uneltele corecte: 26 de int
 *   pe stivă, fără hash, fără coliziune, fără heap, cache mai bun.
 *   Folosește fișierul ăsta când domeniul cheilor nu încape într-un
 *   indice dens mic.
 *
 *   Cache: fiecare map[c]++ poate parcurge un lanț de noduri pe
 *   heap. Nodurile astea au fost alocate în momente diferite și nu
 *   sunt adiacente. Tabloul de 26 de int stă pe una sau două linii
 *   de cache. Același algoritm, constante sălbatice. Big-O nu vede
 *   liniile de cache; CPU-ul da.
 *
 *   operator[] pe unordered_map inserează implicit 0 dacă cheia
 *   lipsește, apoi incrementezi. E convenabil și alocă un nod la
 *   prima vedere a unei chei. E în regulă aici.
 *
 * Exemplul afișează q.
 */

#include <iostream>
#include <unordered_map>
using namespace std;

typedef unordered_map<char, int> Freq;

char mostOccurringLetter(char str[]) {
    Freq map;
    int mx = 0;
    char maxLetter = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
        map[c]++;
        if (map[c] > mx) {
            mx = map[c];
            maxLetter = c;
        }
    }
    return maxLetter;
}

int main() {
    char str[] = "mkbqsqjbyq";
    cout << mostOccurringLetter(str) << "\n";
    return 0;
}
