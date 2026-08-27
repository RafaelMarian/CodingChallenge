/*
 * LECȚIE — Mută zerourile la capăt, păstrează ordinea restului
 *
 * Studentule, asta e o partiție stabilă pe loc: valorile nenule își
 * păstrează ordinea relativă, zerourile umplu coada. Doi pointeri,
 * două trebi.
 *
 * Problemă
 *   Mutează tabloul astfel încât fiecare nenul să apară primul, în
 *   aceeași ordine în care a apărut inițial, iar fiecare zero să ocupe
 *   sufixul. Nu aloca un al doilea buffer de n int-uri.
 *
 * Intuiție / Algoritm
 *   Ține un indice de scriere și un indice de citire. read scanează
 *   tot tabloul. Ori de câte ori read vede un nenul, valoarea aia
 *   aparține la write. Copiaz-o acolo (și, dacă celulele diferă, pune
 *   un zero în gaura pe care tocmai ai părăsit-o, ca coada să fie deja
 *   zerouri pe măsură ce înaintezi). Apoi avansează write. Când read
 *   termină, write e numărul de nenule, iar [write, n) e deja zero
 *   dacă ai plantat zerouri pe măsură ce făceai swap, sau poți umple
 *   intervalul ăla cu zerouri într-o a doua trecere.
 *
 *   write e destinația pentru următoarea valoare păstrată. read e
 *   sursa. write <= read întotdeauna. Regiunea [0, write) e prefixul
 *   nenul gata. Regiunea (write, read] a fost scotocită și ține doar
 *   zerouri (sau e goală). [read, n) n-a fost încă privită.
 *
 * Complexitate
 *   Timp  O(n): fiecare indice e vizitat de un număr constant de ori.
 *   Memorie extra O(1): doi indici, fără al doilea tablou.
 *
 * Memorie
 *   int nums[] decade la un pointer. Muteăm buffer-ul apelantului.
 *   Tabloul nu crește. Scriem doar în celule existente. Asta e pe loc
 *   pe bune: aceleași n int-uri sunt și input, și output. Evităm
 *   vector dinadins.
 *
 *   Alternativa leneșă e să aloci un tablou nou, să copiezi nenulele,
 *   apoi să completezi cu zerouri. Asta e O(n) memorie extra, un al
 *   doilea buffer, o copie înapoi și o poveste de cache mai proastă.
 *   Nu face asta când API-ul permite mutația.
 *
 * Teorie C — partiție, aliasing-ul lui write și read, cache, UB
 *   E același schelet ca o partiție stabilă în C:
 *     int w = 0;
 *     for (int r = 0; r < n; r++)
 *         if (a[r] != 0) { int t = a[r]; a[r] = 0; a[w++] = t; }
 *   Când r == w și a[r] e nenul, store-ul de zero ar șterge valoarea
 *   înainte s-o copiezi dacă ai pune zero mai întâi. Ordonează
 *   atribuirile: fie swap, fie copiază apoi pune zero doar când w != r.
 *   Implementarea de mai jos copiază mai întâi, apoi pune zero pe
 *   celula veche doar la o mutare reală.
 *
 *   Dacă ai scrie a[w++] = a[r]; a[r] = 0; cu w == r, copiezi valoarea
 *   peste ea însăși și apoi o pui pe zero. Ăsta e un bug: distrugi
 *   nenulul pe care voiai să-l păstrezi. Garda w != r nu e stil; e
 *   corectitudine când cei doi indici sunt alias.
 *
 *   În afara intervalului: w nu trece niciodată de r, iar r < n, deci w < n.
 *   Nicio scriere după capăt.
 *
 *   Overflow-ul nu apare: copiem int-uri, nu le adunăm.
 *
 *   Cache: o singură scanare înainte. Un flux. Ăsta e cazul cel mai bun
 *   pentru prefetcher-e. Suprascrii unele celule pe care le-ai trecut
 *   deja; liniile alea sunt încă fierbinți.
 *
 *   Ordinea relativă a nenulelor e păstrată pentru că le scriem în
 *   ordinea în care le citim. Zerourile n-au o ordine care merită
 *   păstrată; sunt de nedistins. Dacă zerourile ar fi obiecte unice,
 *   tot ar fi o partiție stabilă a clasei nenule.
 */

#include <iostream>
using namespace std;

void moveZeroes(int nums[], int n) {
    int write = 0;
    for (int read = 0; read < n; read++) {
        if (nums[read] != 0) {
            if (write != read) {
                nums[write] = nums[read];
                nums[read] = 0;
            }
            write++;
        }
    }
}

int main() {
    int nums[] = {8, 0, 0, 3, 4, 0, 6, 3, 0, 2};
    int n = sizeof(nums) / sizeof(nums[0]);
    moveZeroes(nums, n);
    for (int i = 0; i < n; i++) {
        cout << nums[i] << '\n';
    }
    return 0;
}
