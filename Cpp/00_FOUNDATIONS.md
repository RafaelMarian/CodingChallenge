# Fundamente: C și C++, de la mașină în sus

Citește asta înainte de provocări. Un inginer bun nu știe doar *ce face*
un algoritm. Știe *unde stau octeții*, *cine îi deține* și *ce promite
limbajul* (și ce nu promite).

C este ansamblul portabil al UNIX: tipuri, pointeri și un runtime subțire.
C++ este modelul din C, plus tipuri care pot deține resurse. Lecțiile sunt
sursă C++. Tipul pe care îl folosim pentru o listă de `int` este un tablou C:
`int nums[]` plus o lungime `int n`. Asta înseamnă un pointer, o lungime
și un buffer pe care îl vezi. C++ are și `vector<int>` (un buffer pe heap
plus un obiect cu lungime). Aceste lecții nu îl folosesc. Vrem ca
parametrul să arate ca `int nums[]`.

---

## 1. Ce este, de fapt, un program

Compilatorul produce **cod mașină**. Pipeline-ul, pe scurt:

```
source.cpp  ->  preprocessor  ->  compiler  ->  assembler  ->  linker  ->  executable
   .cpp           #include           .s / .o        .o          libc++        a.out
```

- **Preprocessor**: înlocuire de text (`#include`, `#define`). Nu înțelege tipuri.
- **Compiler**: parsează C++, verifică tipurile, emite object code.
- **Linker**: leagă fișierele obiect și bibliotecile, rezolvă `main`, `printf`,
  `std::cout`.
- **Loader** (sistemul de operare): mapează binarul într-un proces: cod, date
  statice, heap, stivă.

Un `#include` lipsă este eroare de **compilare**. O bibliotecă lipsă este
eroare de **link**. Un pointer sălbatic este crash la **rulare** — sau
corupere tăcută.

Compilează fiecare lecție cu avertismentele pornite:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 -g file.cpp -o file
```

`-O0 -g` păstrează maparea de la sursă la mașină cinstită cât înveți.
Mai târziu, `-O2` schimbă generarea de cod (inlining, unrolling), dar nu
*sensul* programelor bine definite.

Compilarea C este același pipeline cu `gcc` și un fișier `.c`. C++ adaugă
name mangling, constructori și o bibliotecă standard mai bogată. CPU-ul tot
execută load-uri, store-uri și salturi.

---

## 2. Așezarea memoriei unui proces

Un proces tipic în user-space (adresele cresc ca în desen):

```
adrese mari
  ┌─────────────────────────┐
  │ stivă (stack)           │  cadre de funcție, locale, adrese de retur
  │         ↓ crește în jos │
  ├─────────────────────────┤
  │ ... nefolosit ...       │
  ├─────────────────────────┤
  │         ↑ crește în sus │
  │ heap                    │  malloc / new / buffer std::vector
  ├─────────────────────────┤
  │ BSS  (stocare statică   │  globale/statice fără inițializare explicită
  │       zeroată)          │
  ├─────────────────────────┤
  │ data (stocare statică   │  globale/statice cu valori
  │       inițializată)     │
  ├─────────────────────────┤
  │ text (cod mașină)       │  funcțiile tale, de obicei doar citire
  └─────────────────────────┘
adrese mici
```

**Stiva (stack)**

- Fiecare apel pune un **cadru**: adresa de retur, registre salvate, locale.
- Alocarea este o mutare de pointer (`sub rsp, N`). Eliberarea este `ret`.
  Extrem de rapid.
- Dimensiunea e limitată (adesea câteva MB). `int a[10'000'000];` ca local
  poate sparge stiva.
- Obiectele de pe stivă mor când se închide domeniul (scope). Asta e inima RAII.

**Heap**

- Aici trăiesc `malloc` / `new` / buffer-ul din `std::vector`.
- Allocatorul vorbește cu OS-ul (`brk` / `mmap`) în bucăți, apoi îți dă
  piese.
- Cineva **trebuie** să elibereze. În C asta e `free`. În C++ e un destructor
  (sau `delete`, pe care nu trebuie să-l scrii de mână în aceste lecții).

**Stocare statică**

- Globalele și localele `static` trăiesc tot programul.
- `.data` ține inițializatori expliciți; `.bss` e zeroat de loader.

Un tablou pe stivă (în acest curs, când n e cunoscut):

```cpp
int nums[] = {8, 3, 10, 5};
int n = sizeof(nums) / sizeof(nums[0]);
```

Un tablou pe heap (când lungimea depinde de date, vezi HashingIntro):

```cpp
int *a = new int[n];
/* folosește a[0..n) */
delete[] a;
```

În C e aceeași poveste pe heap cu `malloc` / `free`. C++ are și `vector<int>`;
aceste lecții nu îl folosesc. `int nums[], int n` transmite un pointer și o
lungime: nu se copiază buffer-ul.

---

## 3. Valori, pointeri, referințe, tablouri

```cpp
int  x  = 42;   // o valoare: 42 trăiește în acest obiect
int* p  = &x;   // un pointer: p ține adresa lui x
int& r  = x;    // o referință: alt nume pentru x, legată la inițializare
```

| | Pointer `T*` | Referință `T&` |
|---|---|---|
| Poate fi null? | Da (`NULL` / `nullptr`) | Nu, în cod bine definit |
| Se poate relega? | Da (`p = q`) | Nu |
| Aritmetică? | Da (`p + 1`) | Nu |
| Trebuie dereferențiat? | Da (`*p`, `p->`) | Implicit |

**Aritmetica pointerilor** este modul în care funcționează tablourile C:
`a[i]` este definit ca `*(a + i)`. Dacă `p` pointează la un `int`, `p + 1`
avansează **un int**, nu un octet. Compilatorul înmulțește cu `sizeof(int)`.

**Decay-ul tablou → pointer** este regula C pe care nu trebuie s-o uiți:

```c
void f(int a[10]);      /* minciună: tot int *a este */
void f(int a[], int n); /* interfața folosită în acest curs */
```

Un parametru declarat ca tablou **decade** la pointer. `sizeof(a)` în
interiorul lui `f` este dimensiunea unui pointer (8 octeți pe LP64), nu a
tabloului. De aceea fiecare funcție din acest curs primește o lungime:
`int nums[], int n`.

În `main` tabloul încă are o dimensiune cunoscută. Calculează `n` *acolo*,
cât timp `nums` este un tablou real, apoi transmite ambele:

```cpp
int nums[] = {8, 3, 10, 5};
int n = sizeof(nums) / sizeof(nums[0]);  // 4 — valid DOAR AICI
foo(nums, n);                            // nums decade la &nums[0]
```

În interiorul lui `foo`, `sizeof(nums)` este 8 pe LP64, nu 16. Lungimea a
călătorit ca `n`. Acesta este tot punctul decay-ului.

C++ are și `vector<int>` în biblioteca standard. Aceste lecții nu îl
folosesc. Transmitem un pointer și o lungime dinadins, ca tipul să arate
ca `int nums[]`.

**Transmitere prin valoare vs prin pointer (tablouri) vs prin referință**

```cpp
void by_value(int x);           // copiază int-ul
void by_ref  (int& x);          // alias; apelatul poate muta
void by_cref (const int& x);    // alias, doar citire
void by_arr  (int a[], int n);  // acest curs: pointer + lungime. Fără copie a buffer-ului.
void by_ptr  (int *a, int n);   // la fel ca by_arr: a[] decade la int*
```

Preferă `int` (prin valoare) pentru tipuri mici. Preferă `int a[], int n`
pentru tablouri în acest curs. Scrierile prin `a[i]` schimbă buffer-ul
apelantului: nu este o copie. Preferă `T*` când vrei „opțional” sau un
șir C.

---

## 4. Proprietate și RAII (C++ deasupra lui C)

În C, fiecare `malloc` are un `free` pe fiecare cale, inclusiv pe erori.
Ratezi o cale și ai leak. Eliberezi de două ori și corupezi heap-ul.

**RAII** = Resource Acquisition Is Initialization. Leagă resursa de durata
de viață a unui obiect:

- Constructorul o dobândește (memorie, fișier, lock).
- Destructorul o eliberează. Destructorii rulează când obiectul iese din
  scope, inclusiv la derularea excepțiilor.

```cpp
{
    std::vector<int> v{1, 2, 3};  // constructorul alocă
} // destructorul eliberează. Nu apelezi niciodată delete.
```

**Nu** scrie `new` / `delete` în aceste lecții. STL-ul o face corect.
`new` brut este cum se nasc leak-urile, double-free și use-after-free.

Model mintal: **fiecare resursă are exact un proprietar**. `std::vector`
își deține buffer-ul. `std::unique_ptr` deține un singur obiect pe heap.
`std::shared_ptr` este proprietate partajată cu număr de referințe — folosește-l rar.

Analogul C al RAII este `goto cleanup;` plus un singur `free` la sfârșitul
funcției. C++ automatizează acest tipar cu destructori.

---

## 5. Tipuri întregi, overflow și comportament nedefinit

Pe această mașină `int` este complementul față de doi pe 32 de biți.
Standardele C și C++ *garantează* doar `INT_MIN <= -32767` și
`INT_MAX >= 32767`. Aceste lecții tratează `int` ca 32 de biți.

**Overflow-ul pe signed este comportament nedefinit (UB).**

```cpp
int s = (n * (n + 1)) / 2;   // dacă n*(n+1) dă overflow, programul nu mai are sens
```

Compilatorul poate presupune că overflow-ul nu se întâmplă niciodată și
poate șterge verificări „imposibile”. Overflow-ul pe unsigned se înfășoară
modulo 2^w și este bine definit. De aceea wrap-ul pe `size_t` e viclean dar
legal, iar wrap-ul pe `int` nu este.

Corecții pe care le vei vedea în curs:

- Calculează în `long long` (cel puțin 64 de biți). Forțează cu `1LL * a * b`.
- Folosește `l + (r - l) / 2` în loc de `(l + r) / 2` ca mijlocul să nu dea overflow.
- Atenție la `INT_MIN`: minusul unar al lui `INT_MIN` nu poate fi reprezentat
  în complement față de doi pe 32 de biți.

**Alt UB pe care îl vei întâlni:** acces în afara limitelor, folosirea
stocării neinițializate, pointeri dangling, curse pe date. Compilatorul nu
îți datorează **nimic**. Programul poate crăpa, poate părea că merge, sau
poate corupe date mai târziu.

Obicei de profesionist:

```bash
g++ -std=c++17 -O0 -g -fsanitize=address,undefined file.cpp -o file
```

AddressSanitizer prinde overflow pe heap/stivă și use-after-free.
UndefinedBehaviorSanitizer prinde overflow pe signed și multe load-uri
nealiniate.

---

## 6. Cache, localitate și de ce câștigă tablourile

CPU-ul aduce **linii de cache** (de obicei 64 de octeți), nu câte un `int`.
Un `int a[n]` contig sau un `std::vector<int>` este prietenos: parcurgerea
`a[i], a[i+1], ...` lovește aceeași linie, apoi pe următoarea.

O structură pe noduri (`std::list`, un graf de pointeri) sare prin heap.
Același big-O, constante mai proaste, predicție de salt mai proastă,
prefetch mai prost.

De aceea atâtea provocări rămân pe tablouri: memorie extra O(1) și acces
secvențial este felul în care sistemele reale rămân rapide.

`sizeof(int)` este 4. O linie de 64 de octeți ține 16 `int`. O parcurgere
liniară a unui milion de `int` sunt câteva zeci de mii de umpleri de linie.
O parcurgere care urmărește pointeri pe un milion de noduri poate fi un
milion de miss-uri de cache.

---

## 7. Complexitatea pe care trebuie s-o spui cu voce tare

Pentru fiecare funcție, spune:

- **Timp**: cazul cel mai rău în `n` (și parametri extra `k`, `W`, ...).
- **Spațiu extra**: în afara inputului. Pe loc O(1) vs o copie O(n).
- **Ce muți**: mai are apelantul tabloul original?

Big-O ascunde constantele. Un hashing `O(n)` cu cache rece poate pierde
în fața lui `O(n log n)` pe tablouri sortate de `n` moderat. Raționează
întâi; măsoară când contează.

---

## 8. Biblioteca C vs ce scrie de fapt acest curs

Fiecare lecție începe cu `using namespace std;` ca numele să fie `cout`,
`sort`, `unordered_map` — nu `std::cout`. Nu scrie prefixe `std::`.
Nu scrie `vector`. Nu scrie `size_t` sau `static_cast`.

Tipul de tablou al acestui curs este un tablou C plus o lungime:

```cpp
#include <iostream>
using namespace std;

int foo(int nums[], int n) {
    for (int i = 0; i < n; i++) {
        /* nums[i] este *(nums + i) */
    }
    return 0;
}

int main() {
    int nums[] = {8, 3, 10, 5};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << foo(nums, n) << "\n";
    return 0;
}
```

`vector<int>` există în C++. Nu îl folosim aici. `int nums[]` este tipul
dinadins.

| Nevoie | C | Acest curs |
|--------|---|------------|
| Tablou de int | `int a[n]` sau `malloc` | `int nums[]` + `int n` |
| Buffer pe heap (U necunoscut) | `malloc` + `free` | `int *p = new int[U];` … `delete[] p` |
| Octeți de text | `char *` + `strlen` | `char str[]`, parcurgi până la `'\0'` |
| Sortare | `qsort` | `sort(nums, nums + n)` din `<algorithm>` |
| Min / max | operator ternar | `min` / `max`, sau un `if` |
| Tabelă hash | o scrii tu | `unordered_map<K,V>` (sau `typedef`) |
| Numărare pe alfabet | `int hash[26]` | `int hash[26]` |
| Stivă | tablou + indice `top` | `int stk[100]; int top = -1;` |
| Limite | `INT_MIN` în `<climits>` | `INT_MIN` / `INT_MAX` |
| Afișare | `printf` | `cout << x << "\n"` (nu `endl`) |

`endl` golește stream-ul (flush). Preferă `"\n"` decât dacă ai nevoie de flush.

`sizeof` pe un *parametru* care arată ca un tablou este dimensiunea unui
pointer. Transmite întotdeauna `n` separat. Calculează `n` în `main` cu
`sizeof(nums) / sizeof(nums[0])` cât timp `nums` este încă un tablou real.

---

## 9. Cum studiezi fiecare provocare

1. Citește comentariul din cap (enunț + de ce algoritmul e corect).
2. Urmărește exemplul pe hârtie, cu indici. Desenează tabloul în memorie.
3. Compilează și rulează. Schimbă inputul. Strică-l dinadins.
4. Întreabă-te: *unde stau octeții? cine îi eliberează? poate `int` să dea overflow?*
5. Rescrie într-un fișier gol, fără să te uiți.

Când poți explica **corectitudinea, complexitatea și memoria** fără
comentarii, ai terminat lecția.
