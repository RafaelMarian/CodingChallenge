# Provocări de programare în C++

Un curs de algoritmi scris în C++, predat pe modelul mașinii din C:
așezarea memoriei, pointeri, cine deține resursele, comportament nedefinit
și complexitate.

1. Citește [`Cpp/00_FOUNDATIONS.md`](Cpp/00_FOUNDATIONS.md) o dată, încet.
2. Parcurge folderele **în ordinea de mai jos**.
3. Compilează și rulează fiecare fișier. Nu te opri la citit.
4. După fiecare fișier, închide-l și rescrie funcția din memorie.

```bash
# o lecție
g++ -std=c++17 -Wall -Wextra -Wpedantic -O0 -g Cpp/SinglePointer/LinearSearch.cpp -o /tmp/cc && /tmp/cc

# sanitizere (prind UB: ieșire din vector, overflow pe signed, use-after-free)
g++ -std=c++17 -O0 -g -fsanitize=address,undefined Cpp/SinglePointer/LinearSearch.cpp -o /tmp/cc && /tmp/cc

# toate lecțiile, compilate și rulate
make -C Cpp
```

---

## Ordinea de studiu (nu sări peste pași)

| Pas | Folder | Ce înveți |
|-----|--------|-----------|
| 1 | `Cpp/00_FOUNDATIONS.md` | Compilare, memoria procesului, pointeri, RAII, UB |
| 2 | `Cpp/SinglePointer/` | Tablouri contigue, overflow, o singură parcurgere |
| 3 | `Cpp/TwoPointer/` | Mutare pe loc, swap, șiruri C `char s[]` |
| 4 | `Cpp/ThreePointers/` | Partiționarea unui interval într-o singură trecere |
| 5 | `Cpp/PrefixSum/` | Memorie în plus în schimbul timpului |
| 6 | `Cpp/SlidingWindow/` | Ferestre amortizate O(n) |
| 7 | `Cpp/Kadanes/` | Decizii locale care păstrează un optimum global |
| 8 | `Cpp/Stack/` | Stive monotone, LIFO, tablou C + indice `top` |
| 9 | `Cpp/Hashing/` | Tablouri de numărare vs tabele hash, coliziuni |
| 10 | `Cpp/BoyerMooreMajority/` | Algoritmi cu memorie extra constantă |
| 11 | `Cpp/BinarySearch/` | Căutare pe indici *și* pe răspuns |
| 12 | `Cpp/MergeIntervals/` | Sortare + unire greedy |
| 13 | `Cpp/Gussai/` | Formulă închisă vs valori hardcodate |

Fiecare fișier `.cpp` este o lecție: enunț, de ce algoritmul e corect,
complexitate, memorie și teorie C, apoi cod pe care îl compilezi.
