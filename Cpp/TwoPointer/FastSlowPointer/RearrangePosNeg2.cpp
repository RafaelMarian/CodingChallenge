/*
 * LECȚIE — Negativele primele, cu mai mult din ordinea relativă originală
 *
 * Studentule, partiția Hoare de la ambele capete e O(n) și distruge
 * ordinea. Lecția asta folosește o pereche lent/rapid care amândoi
 * merg înainte. Păstrează ordinea relativă a negativelor. Nu păstrează
 * ordinea relativă a pozitivelor. Poate face muncă pătratică. Trebuie
 * să știi că există ca să poți să-l refuzi.
 *
 * Problemă
 *   Mută fiecare negativ înaintea fiecărui pozitiv. Preferă păstrarea
 *   ordinii negativelor. Pe loc, cu swap-uri. Exemplul e
 *   {-2, 6, 3, -4, 1, 10, -5, 8, -7, -9}.
 *
 * Intuiție / Algoritm
 *   Indicele lent i găsește cea mai din stânga valoare care nu e
 *   negativă (primul pozitiv care stă în cale). Indicele rapid j
 *   pornește imediat după i și găsește următorul negativ. Fă-le swap.
 *   Negativul ăla a sărit la stânga în prima gaură. Repetă. Negativele
 *   întâlnite mai târziu tot fac swap în găuri mai târzii, deci
 *   negativele își păstrează ordinea. Fiecare swap aruncă un pozitiv
 *   în locul de unde a venit negativul, care poate fi departe la
 *   dreapta, deci pozitivele sunt permutate.
 *
 *   După destule swap-uri, prefixul e toate negativele în ordinea
 *   originală, iar sufixul e pozitivele rămase într-o ordine oarecare.
 *
 *   Asta nu e o partiție stabilă a ambelor clase. O partiție stabilă
 *   care păstrează ambele ordini are nevoie de memorie extra (un buffer
 *   de n, sau o listă) sau de un algoritm de rotație pe loc mai
 *   sofisticat.
 *
 * Complexitate
 *   Timp  O(n^2) în cazul cel mai rău. Fiecare swap mută un negativ
 *   la locul lui, dar i și j își reiau scanările de la gaura curentă.
 *   Dacă negativele și pozitivele alternează strict, parcurgi porțiuni
 *   lungi în repetate rânduri.
 *   Memorie extra O(1).
 *
 *   Contrast: partiția pe semn Hoare e O(n) timp, O(1) spațiu, nu e
 *   stabilă. Metoda cu buffer: o trecere într-un tablou nou, O(n) timp,
 *   O(n) spațiu, stabilă pe ambele părți dacă pui întâi negativele în
 *   ordine, apoi pozitivele în ordine.
 *
 * Memorie
 *   int arr[] decade la un pointer; n e lungimea. Swap-uri pe loc în
 *   buffer-ul apelantului. Fără a doua alocare. Evităm vector dinadins.
 *   Asta e singura virtute a scanării ăsteia pătratice. Memoria extra
 *   pe care ai refuzat-o e adesea mai ieftină decât timpul extra pe
 *   care l-ai acceptat. Măsoară înainte să păstrezi o metodă O(n^2)
 *   pe loc pe n mare.
 *
 * Teorie C — lent/rapid, swap, cache, de ce e pătratic
 *   Doi indici care amândoi cresc e tiparul „lent și rapid” pe care-l
 *   vei vedea și la detectarea de cicluri, dar aici nu e un ciclu.
 *   Lentul marchează o gaură (un pozitiv în prefixul negativ). Rapidul
 *   vânează următorul ocupant pentru gaura aia (un negativ). După swap,
 *   gaura s-a mutat: pozitivul e acum la j, iar i tot poate arăta spre
 *   un pozitiv (următorul), deci bucla exterioară continuă.
 *
 *   Fiecare while interior e o scanare liniară. Scanări liniare
 *   imbricate pe același tablou, reluate, e tiparul clasic O(n^2)
 *   prietenos cu cache-ul, dar tot pătratic. Accesul secvențial nu
 *   anulează un factor extra de n. Face doar ca fiecare dintre pașii
 *   O(n^2) să fie un load ieftin.
 *
 *   Swap-ul folosește un int temporar. Cei doi indici i și j sunt
 *   distincte când facem swap (j pornește de la i+1 și face swap doar
 *   când amândoi sunt în interval și s-a găsit un negativ). Fără XOR.
 *
 *   Limite: fiecare while verifică i < n și j < n înainte de
 *   dereferențiere. Asta e diferența dintre un program definit și un
 *   buffer overflow. AddressSanitizer îl prinde pe-al doilea; nu te
 *   baza pe el ca substitut al verificărilor.
 *
 *   Fără overflow pe valori. Mutația pe loc înseamnă din nou că
 *   permutarea originală e dusă.
 *
 *   Poți tipări i și j înainte de fiecare swap când urmărești. Programul
 *   de mai jos tipărește doar tabloul final, separat prin spații.
 */

#include <iostream>
using namespace std;

void rearrange2(int arr[], int n) {
    int i = 0;
    while (i < n) {
        while (i < n && arr[i] < 0) {
            i++;
        }
        int j = i + 1;
        while (j < n && arr[j] > 0) {
            j++;
        }
        if (i < n && j < n) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        } else {
            break;
        }
    }
}

int main() {
    int arr[] = {-2, 6, 3, -4, 1, 10, -5, 8, -7, -9};
    int n = sizeof(arr) / sizeof(arr[0]);
    rearrange2(arr, n);
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            cout << ' ';
        }
        cout << arr[i];
    }
    cout << '\n';
    return 0;
}
