/*
 * LECȚIE — Unicizează un tablou sortat pe loc; întoarce lungimea nouă
 *
 * Studentule, unicitatea e ușoară cu un hash set și un buffer nou. E
 * mai interesantă când tabloul e deja sortat și trebuie să ții seria
 * unică în aceeași alocare.
 *
 * Problemă
 *   nums e sortat nedescrescător, deci duplicatele sunt alăturate.
 *   Suprascrie tabloul astfel încât valorile unice să ocupe un prefix,
 *   în ordine, și întoarce k, numărul de valori unice. Prefixul [0, k)
 *   e răspunsul. Celulele [k, n) sunt rest nespecificat; apelanții nu
 *   trebuie să le citească ca parte a secvenței unice. Nu micșorăm
 *   tabloul.
 *
 * Intuiție / Algoritm
 *   Pointerul lent k e lungimea prefixului unic de până acum, echivalent
 *   cu indicele de destinație al următoarei valori noi. Pointerul rapid
 *   i scanează. Când nums[i] diferă de ultima valoare păstrată nums[k-1],
 *   e o serie nouă: stocheaz-o la nums[k] și incrementează k. Când e
 *   egal cu nums[k-1], sari peste el. Pentru că egalitățile apar doar
 *   în serii alăturate ale unui tablou sortat, comparația cu ultima
 *   valoare păstrată e de ajuns; n-ai nevoie niciodată de un set.
 *
 *   După scanare, [0, k) e strict crescător (sau nedescrescător cu
 *   toate duplicatele stoarse — aici valorile sunt unice, deci
 *   strict crescător).
 *
 * Complexitate
 *   Timp  O(n).
 *   Memorie extra O(1). Valorile unice ocupă fața aceluiași buffer.
 *   Ștergerea din față într-o buclă ar fi O(n^2) mutări. Un tablou
 *   nou de unice e O(k) memorie extra. Algoritmul ăsta n-are nevoie
 *   de niciuna.
 *
 * Memorie
 *   int nums[] decade la un pointer; n e lungimea vie. Scriem valorile
 *   unice în buffer-ul existent. Nu alocăm o copie mai scurtă. Cele n
 *   celule tot există; doar prefixul de lungime k e răspunsul. Evităm
 *   vector dinadins. k nu trece niciodată de n, deci nu scriem niciodată
 *   după alocare. Nici nu citim după ea: i < n.
 *
 * Teorie C — sursă și destinație care se suprapun, coada rămasă
 *   Copia nums[k] = nums[i] poate avea k < i (după ce-ai sărit duplicate)
 *   sau k == i (încă nicio duplicată, prefixul unic e încă toată
 *   scanarea). Când k == i, atribuirea e un no-op. Când k < i scriem
 *   într-o celulă a cărei valoare originală a fost deja consumată ca
 *   duplicat sau deja copiată înainte. Sursa și destinația se suprapun
 *   în sensul că sunt același tablou, dar fiecare atribuire e o celulă
 *   către o celulă, deci nu e problema de overlap de la memmove/memcpy.
 *
 *   memcpy pe regiuni care se suprapun e comportament nedefinit.
 *   memmove e definit pentru overlap. Nu apelăm niciuna; atribuim câte
 *   un int pe rând. Asta e întotdeauna bine definit dacă ambii indici
 *   sunt în interval.
 *
 *   Tablou gol: nu există nums[k-1]. Întoarce 0 înainte de buclă.
 *   Un element: k pornește de la 1, bucla nu rulează, întoarce 1.
 *
 *   k - 1 pe k == 0 ar fi un indice prost. Ținem k >= 1 după verificarea
 *   de gol, deci nums[k - 1] e valid.
 *
 *   Cache: o scanare înainte, în mare parte streaming. Scrierile merg
 *   spre stânga acelorași linii. Localitate excelentă.
 *
 *   Overflow-ul nu e implicat. Mutația pe loc e tot punctul: secvența
 *   unică reutilizează celulele input-ului.
 *
 *   Tipărirea lui "ans" concatenat cu întregul e convenția exemplului,
 *   nu un format pe care ar trebui să-l folosești într-o bibliotecă.
 */

#include <iostream>
using namespace std;

int removeDuplicates(int nums[], int n) {
    if (n == 0) {
        return 0;
    }
    int k = 1;
    for (int i = 1; i < n; i++) {
        if (nums[i] != nums[k - 1]) {
            nums[k] = nums[i];
            k++;
        }
    }
    return k;
}

int main() {
    int nums[] = {1, 1, 1, 2, 2, 3, 3, 4, 5, 5};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << "ans" << removeDuplicates(nums, n) << '\n';
    return 0;
}
