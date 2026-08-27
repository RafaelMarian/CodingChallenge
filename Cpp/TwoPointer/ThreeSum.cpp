/*
 * LECȚIE — Three-sum: existență după sortare
 *
 * Studentule, two-sum pe un tablou sortat e o pereche de pointeri.
 * Three-sum e algoritmul ăla în interiorul unei bucle care fixează a
 * treia valoare. Plătești un factor de n și tot nu ajungi la forța
 * brută O(n^3).
 *
 * Problemă
 *   Întoarce dacă există trei valori (nu neapărat de indici distincți
 *   ca valoare) care se adună la un target. Indicii trebuie să fie
 *   distincți: fiecare poziție e folosită cel mult o dată. Exemplu:
 *   {1,4,45,6,10,8} și target 22 e true (4 + 8 + 10).
 *
 * Intuiție / Algoritm
 *   Sortează mai întâi. Pentru fiecare indice i de la 0 la n-3, caută
 *   două valori în sufixul strict i+1..n-1 care se adună la
 *   target - nums[i], folosind metoda sortată cu doi pointeri: l = i+1,
 *   r = n-1, mută l dacă triplul e prea mic, mută r dacă e prea mare,
 *   întoarce true la egalitate.
 *
 *   Sortarea e permisă pentru că întoarcem un boolean, nu indici
 *   originali. Dacă ai avea nevoie de indici în tabloul nesortat,
 *   sortează perechi (valoare, indice) sau caută fără să distrugi
 *   identitatea.
 *
 *   Să sari nums[i] duplicate e opțional pentru un boolean; ajută doar
 *   varianta „listează toate triplele unice.” Aici nu sărim nimic extra
 *   dincolo de distinctivitatea pozițiilor i,l,r.
 *
 * Complexitate
 *   Timp  O(n^2): sort O(n log n) plus n ori o scanare cu doi pointeri
 *   O(n). Forța brută e O(n^3).
 *   Memorie extra O(1) în afară de sort. sort(nums, nums+n) e pe loc
 *   (introsort) cu O(log n) stivă pentru recurență, pe care tot o
 *   numim O(1) extra față de input în vorbirea de zi cu zi, sau O(log n)
 *   dacă suntem preciși cu stiva lui sort. Muteăm tabloul apelantului
 *   sortându-l.
 *
 * Memorie
 *   int arr[] decade la un pointer. Sortăm pe loc cu sort(arr, arr+n).
 *   Dacă apelantul avea nevoie de ordinea originală, am copia mai întâi:
 *   copia aia e O(n) extra. Funcția asta tratează buffer-ul ca spațiu de lucru.
 *   Documentează asta. Evităm vector dinadins.
 *
 *   Fără hash set. Un hash set de complemente e abordarea two-sum
 *   nesortată și ar fi O(n) memorie extra per i, constante mai proaste
 *   și localitate mai proastă.
 *
 * Teorie C — sort, overflow-ul a trei int-uri, pointeri, cache, UB
 *   Trei int-uri pot da overflow pe int: INT_MAX + INT_MAX + INT_MAX
 *   nu încape pe 32 de biți. Expresia a + b + c e asociativă la stânga
 *   și tot int, deci prima adunare poate fi deja UB. Acumulează în
 *   long long:
 *     1LL * nums[i] + nums[l] + nums[r]
 *   care e ((1LL * nums[i]) + nums[l]) + nums[r]. Sigur.
 *
 *   sort are nevoie de iteratori random-access. Un tablou C decade la
 *   un pointer, iar pointerii într-un tablou sunt random-access.
 *   sort(arr, arr+n) sortează cele n int-uri pe loc. Pentru int, asta
 *   înseamnă copii de cuvinte mașină.
 *
 *   După sort, argumentul cu doi pointeri din TwoSumSorted se aplică
 *   pe sufix: sufixul e tot sortat.
 *
 *   Cache: sort e partea grea, mai puțin secvențială (sare). Cele n
 *   scanări cu doi pointeri sunt secvențiale pe un tablou fierbinte.
 *   Pentru n moderat, scanările pătratice domină timpul și sunt
 *   prietenoase cu cache-ul.
 *
 *   Limite: l și r rămân în (i, n) cu l < r. i rulează doar cât timp
 *   rămân cel puțin două celule la dreapta: i + 2 < n.
 *
 *   Gol / n < 3: întoarce false. Fără n-1 pe un tablou prea scurt.
 *
 *   Mutație pe loc: permutarea sortată înlocuiește input-ul. Booleanul
 *   n-are nevoie de ordinea originală după sort.
 */

#include <algorithm>
#include <iostream>
using namespace std;

bool find3Numbers(int arr[], int n, int sum) {
    if (n < 3) {
        return false;
    }
    sort(arr, arr + n);
    long long need = sum;
    for (int i = 0; i + 2 < n; i++) {
        int l = i + 1;
        int r = n - 1;
        while (l < r) {
            long long cur = 1LL * arr[i] + arr[l] + arr[r];
            if (cur == need) {
                return true;
            }
            if (cur < need) {
                l++;
            } else {
                r--;
            }
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 4, 45, 6, 10, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (find3Numbers(arr, n, 22)) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    return 0;
}
