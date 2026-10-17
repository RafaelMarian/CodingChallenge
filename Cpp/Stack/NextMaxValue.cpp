/*
 * LECȚIE — Următorul mai mare la dreapta: o stivă monotonă descrescătoare
 *
 * Studentule, pentru fiecare indice i, găsește cea mai apropiată valoare la
 * dreapta lui i care e strict mai mare decât nums[i]. Dacă nu
 * există, scrie -1.
 *
 * Intuiție
 *   Parcurge de la dreapta la stânga. Ține o stivă de valori care
 *   sunt încă candidate pentru cineva la stânga lor. Ține stiva aia
 *   strict descrescătoare de jos în sus (vârful e candidatul cel
 *   mai apropiat, cel mai mic rămas).
 *
 *   La indicele i:
 *     1. Scoate cât timp vârful e mai mic sau egal cu nums[i].
 *        Valorile astea nu pot fi niciodată următorul mai mare
 *        pentru i, și nu pot fi nici pentru cineva mai la stânga:
 *        nums[i] e mai aproape și cel puțin la fel de mare, deci
 *        le domină.
 *     2. Dacă stiva e goală, nimic la dreapta nu e mai mare: -1.
 *        Altfel vârful e cea mai apropiată valoare mai mare.
 *     3. Pune nums[i]. Acum e candidatul cel mai apropiat pentru
 *        stânga.
 *
 *   Stocăm valori, nu indici, pentru că API-ul cere următoarea
 *   *valoare* mai mare. Dacă mai târziu ai nevoie de indice, pune
 *   indici și citește nums[stk[top]].
 *
 *   De ce scoți valorile egale? „Următorul mai mare” e strict. Un
 *   egal nu e mai mare, și un element ulterior din stânga care
 *   voia ceva strict deasupra lui nums[i] n-ar vrea nici egalul ăla.
 *
 * Complexitate
 *   Fiecare valoare e pusă o dată și scoasă cel mult o dată. while
 *   din interior arată ca O(n) pe pas, dar e O(1) amortizat: pe
 *   toată parcurgerea sunt cel mult n push și n pop. Timp O(n).
 *   Memorie extra: stiva e O(n) în cazul cel mai rău (un tablou
 *   strict descrescător: nu se scoate niciodată nimic). Tabloul de
 *   răspuns e și el O(n); ăsta e output, nu auxiliar, depinde cum
 *   numeri.
 *
 * Memorie
 *   Stiva e un tablou C plus un indice:
 *
 *       int stk[100];
 *       int top = -1;          // gol: nimic la stk[top]
 *       stk[++top] = value;    // push
 *       value = stk[top--];    // pop
 *
 *   100 e o capacitate fixă. Exemplul are 10 elemente, deci încape.
 *   Să pui peste 99 e overflow pe buffer: UB. Codul de producție ar
 *   aloca n int (malloc / new int[n]) ca capacitatea să egaleze
 *   lungimea. nmv[] e tabloul de output, aceeași lungime ca arr,
 *   deținut de main. arr a decăzut la un pointer; n e lungimea.
 *
 * Teorie C — LIFO, pointeri, cache, UB pe stivă goală
 *   O stivă e last-in, first-out. „Cel mai apropiat la dreapta”
 *   pe care l-am văzut deja e ultimul lucru pe care l-am pus, deci
 *   stă la stk[top]. Pop e O(1): decrementezi top. Fără mutarea
 *   celorlalte elemente.
 *
 *   Nu confunda asta cu stiva de apel a CPU-ului. Asta e un tablou
 *   explicit pe care-l folosim ca stivă. Stiva de apel e cadrul
 *   lui nextMaxValue; overflow-ul *ăleia* e un alt bug (recursivitate
 *   adâncă). Aici adâncimea de recurență e 1.
 *
 *   Cache: parcurgem nums de la dreapta la stânga (tot secvențial,
 *   prefetch-ul merge destul de bine și invers pe majoritatea
 *   CPU-urilor) și atingem coada lui stk. Coada e fierbinte. O
 *   stivă pe listă înlănțuită ar urmări noduri pe heap și ar rata.
 *
 *   Valorile însele sunt int; nu le adunăm, deci overflow-ul nu e
 *   problema. În afara limitelor pe o stivă goală e: să citești
 *   stk[top] când top == -1 e UB. Garda top >= 0 e verificarea.
 *   N-o sări niciodată.
 *
 * Exemplul {2,1,3,2,6,3,5,9,1,7} -> 3 3 6 6 9 5 9 -1 7 -1
 */

#include <iostream>
using namespace std;

void nextMaxValue(int arr[], int n, int nmv[]) {
    int stk[100];
    int top = -1;
    for (int i = n - 1; i >= 0; i--) {
        while (top >= 0 && arr[i] >= stk[top]) {
            top--;
        }
        nmv[i] = (top < 0) ? -1 : stk[top];
        top++;
        stk[top] = arr[i];
    }
}

int main() {
    int arr[] = {2, 1, 3, 2, 6, 3, 5, 9, 1, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int nmv[sizeof(arr) / sizeof(arr[0])];
    nextMaxValue(arr, n, nmv);
    for (int i = 0; i < n; i++) {
        cout << nmv[i] << " ";
    }
    cout << "\n";
    return 0;
}
