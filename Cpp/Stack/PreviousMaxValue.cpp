/*
 * LECȚIE — Anteriorul mai mare la stânga: aceeași stivă, parcurgere inversă
 *
 * Studentule, pentru fiecare indice i, găsește cea mai apropiată valoare la
 * *stânga* lui i care e strict mai mare decât nums[i]. Dacă nu
 * există, scrie -1.
 *
 * Intuiție
 *   E next-greater cu axa timpului inversată. Parcurge de la stânga
 *   la dreapta. Stiva ține candidați la stânga, tot monoton
 *   descrescătoare spre vârf. La i, scoate tot ce e mai mic sau
 *   egal cu nums[i] (sunt ascunși de nums[i] pentru oricine mai
 *   la dreapta). Noul vârf, dacă există, e anteriorul mai mare.
 *   Apoi pune.
 *
 *   Aceiași trei pași, direcție opusă. Dacă ai înțeles
 *   NextMaxValue.cpp, fișierul ăsta e argumentul ăla cu „dreapta”
 *   și „stânga” schimbate. Ține-le pe ambele la îndemână: multe
 *   probleme (dreptunghiuri de histogramă, apă prinsă, span de
 *   cotații) au nevoie de una sau de ambele.
 *
 * Complexitate
 *   O(n) amortizat: fiecare valoare pusă o dată, scoasă cel mult
 *   o dată. Memorie extra O(n) în cazul cel mai rău. Strict
 *   crescător: fiecare valoare nouă e mai mare, deci scoatem tot
 *   și stiva ține un element. Cazul cel mai rău e strict
 *   descrescător: nimic nu e mai mare decât ce e deja pe stivă,
 *   nu se scoate nimic, stiva crește la n.
 *
 * Memorie
 *   Aceeași stivă pe tablou C ca NextMaxValue:
 *
 *       int stk[100];
 *       int top = -1;
 *
 *   Un buffer de stivă, un tablou de output pmv[]. Inputul arr e
 *   un pointer plus n. Capacitate fixă 100: exemplul e 10.
 *   Overflow pe stk e UB. Varianta pe heap: int *stk = new int[n];
 *   ... delete[] stk;
 *
 * Teorie C — simetrie, UB pe stivă goală, cache
 *   Stiva e un indice într-un buffer contig. Push e ++top și un
 *   store. Pop e --top. Fără lungime ascunsă; top e lungimea minus
 *   unu. Să citești stk[top] când top < 0 e UB: ai indexa înainte
 *   de buffer. Ternarul (top < 0) ? -1 : stk[top] e garda.
 *
 *   Parcurgerea e stânga-dreapta: load-ul secvențial din manual.
 *   Coada stivei e linia de cache fierbinte. Aceeași poveste de
 *   localitate ca next-greater.
 *
 *   Valorile sunt comparate, nu adunate. Overflow-ul pe întregi
 *   nu e în joc. Ce e în joc e indicele signed i care merge
 *   0 .. n-1, sigur cât timp n încape în int.
 *
 * Exemplul {7,1,3,2,9,5,6,3,1,2} -> -1 7 7 3 -1 9 9 6 3 3
 */

#include <iostream>
using namespace std;

void previousMaxValue(int arr[], int n, int pmv[]) {
    int stk[100];
    int top = -1;
    for (int i = 0; i < n; i++) {
        while (top >= 0 && arr[i] >= stk[top]) {
            top--;
        }
        pmv[i] = (top < 0) ? -1 : stk[top];
        top++;
        stk[top] = arr[i];
    }
}

int main() {
    int arr[] = {7, 1, 3, 2, 9, 5, 6, 3, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int pmv[sizeof(arr) / sizeof(arr[0])];
    previousMaxValue(arr, n, pmv);
    for (int i = 0; i < n; i++) {
        cout << pmv[i] << " ";
    }
    cout << "\n";
    return 0;
}
