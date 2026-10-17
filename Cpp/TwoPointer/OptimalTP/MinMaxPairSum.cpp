/*
 * LECȚIE — Minimizează suma maximă a perechilor (împerecherea extremelor)
 *
 * Studentule, ăsta e o explicație independentă a aceleiași strategii de
 * împerechere ca MiniMaxSum, cu un exemplu diferit, ca să poți
 * reimplementa din comentariu fără să te uiți la fișierul ăla.
 *
 * Problemă
 *   Primești un număr par de întregi. Împerechează-i pe toți. Scorul
 *   unei împerecheri e cea mai mare sumă de pereche. Minimizează scorul
 *   ăla. Exemplu: {7,3,1,8,6,1,7,5}. După sortare, 1 1 3 5 6 7 7 8.
 *   Perechile de extreme sunt 1+8=9, 1+7=8, 3+7=10, 5+6=11. Maximul
 *   lor e 11. Ăsta e răspunsul.
 *
 * Intuiție / Algoritm
 *   Sortează tabloul nedescrescător. Cea mai mică valoare rămasă e cea
 *   mai bună contragreutate pentru cea mai mare valoare rămasă: ridică
 *   suma perechii numărului mare cât de puțin se poate. Apoi repetă pe
 *   intervalul interior rămas. Doi indici, câte unul la fiecare capăt,
 *   umblă până se încrucișează. Max-ul care rulează al lui (nums[i] +
 *   nums[j]) e scorul minimax.
 *
 *   Dacă împerechezi două numere mari, suma lor e o bară înaltă pe
 *   care n-o mai poți coborî mai târziu. Dacă împerechezi două numere
 *   mici, cheltuiești adunzi ieftini unul pe altul și lași un număr
 *   mare să se împerecheze cu unul mediu, ceea ce e de obicei un max
 *   mai rău. Împerecherea extremelor egalizează.
 *
 * Complexitate
 *   Timp  O(n log n) dominat de sort, apoi o scanare liniară a n/2
 *   perechi.
 *   Memorie extra O(1) memorie de lucru dacă sort e pe loc. Output-ul
 *   e un singur int. Nu stoca perechile.
 *
 * Memorie
 *   int nums[] decade la un pointer. sort(nums, nums+n) sortează cele
 *   n celule existente. Doi indici și un max long long pe stivă.
 *   Evităm vector dinadins. Fără al doilea tablou. Buffer-ul apelantului
 *   e permutat; nu există un destructor care să-l elibereze.
 *
 *   Să transmiți o copie ar păstra originalul cu O(n) memorie extra.
 *   API-ul ăsta n-are nevoie de original.
 *
 * Teorie C — extreme, overflow, lungime pară, cache, UB, pe loc
 *   Suma perechii trebuie calculată în long long. Doi adunzi int la
 *   extrema pozitivă dau overflow pe signed pe 32 de biți. UB nu e
 *   „se înfășoară la negativ și apoi max-ul tău e greșit”; UB înseamnă
 *   că compilatorul poate șterge actualizarea max-ului.
 *   1LL * nums[i] + nums[j] e obiceiul. Ține best în long long.
 *   Întoarce int doar când știi că rezultatul încape, ca în exemplul ăsta.
 *
 *   n par: i și j aterizează pe o împărțire curată. Buclăm cât timp
 *   i < j, deci nu împerechem niciodată un element cu el însuși.
 *   j = n-1 e valid după o gardă n < 2. Decrementarea lui j e sigură
 *   cât timp i < j.
 *
 *   sort cere ca operator< să fie o ordine slabă strictă. Pentru int
 *   e. Nu compara int-uri scăzându-le într-un comparator qsort;
 *   scăderea aia dă overflow. operator< din C++ nu scade.
 *
 *   După sort, tabloul e contig și monotonic. Încărcarea lui nums[i]
 *   și nums[j] într-o plimbare în pas spre interior lovește două
 *   fluxuri secvențiale. Prefetcher-ele iubesc asta. O listă de noduri
 *   legate prin pointeri cu aceleași valori ar transforma fiecare pas
 *   într-un potențial miss de cache.
 *
 *   Pe loc: sort suprascrie permutarea de input. Bucla de împerechere
 *   nu scrie. Dacă o funcție ulterioară ar avea nevoie de lista
 *   nesortată de oameni, deja ai pierdut-o. Copiază-și-sortează dacă
 *   contează.
 *
 *   Tablou gol: 0. Un element: nu e o pereche, 0. Gărzile alea și
 *   previn un n-1 fals.
 *
 *   Tipărirea int-ului e tot API-ul. Nu există o listă de perechi de
 *   formatat.
 */

#include <algorithm>
#include <iostream>
using namespace std;

int minPairSum(int nums[], int n) {
    if (n < 2) {
        return 0;
    }
    sort(nums, nums + n);
    int i = 0;
    int j = n - 1;
    long long best = 0;
    while (i < j) {
        long long s = 1LL * nums[i] + nums[j];
        if (s > best) {
            best = s;
        }
        i++;
        j--;
    }
    return best;
}

int main() {
    int nums[] = {7, 3, 1, 8, 6, 1, 7, 5};
    int n = sizeof(nums) / sizeof(nums[0]);
    cout << minPairSum(nums, n) << '\n';
    return 0;
}
