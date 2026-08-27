/*
 * LECȚIE — Un tablou de 26 de sloturi pentru un alfabet dens
 *
 * Studentule, dat un șir de litere englezești mici, întoarce litera care apare
 * cel mai des. La egalitate câștigă litera mai de la începutul
 * alfabetului (parcurgem 0..25 și ținem un strict greater).
 *
 * Intuiție
 *   Sunt 26 de chei posibile. 26 e o constantă. Pune 26 de contoare
 *   la rând, indexează-le cu c - 'a', incrementează, apoi parcurge
 *   după max. Nu vrei un arbore, o tabelă hash sau o mapă. Vrei un
 *   tablou.
 *
 *   Exemplul "mkbqsqjbyq": q apare de trei ori. Întoarce 'q'.
 *
 * Complexitate
 *   Timp O(n + 26) = O(n). Memorie extra O(1): 26 de int, independent de n.
 *
 * Memorie
 *   int hash[26] e un tablou automat. Trăiește pe stiva lui
 *   mostOccurringLetter. Îl zeruim într-o buclă. Fără alocare pe
 *   heap și nimic de eliberat. Când funcția se întoarce, cei 26 de
 *   int mor cu cadrul. Ăsta e cel mai ieftin depozit corect pe care
 *   îl poți avea pentru o mulțime densă mică de chei.
 *
 *   26 * sizeof(int) = 104 octeți. Un cadru de stivă tipic ține asta
 *   fără comentariu. Contrast cu HashingIntro.cpp, unde U+1 int merg
 *   pe heap pentru că U depinde de date și poate fi mare.
 *
 *   Textul e char str[]: un șir C, terminat cu NUL. În main e un
 *   tablou real. Transmis în funcție, decade la char*. Parcurgem
 *   până str[i] == '\0'. N-avem nevoie de o lungime separată.
 *
 * Teorie C — ASCII, decay de pointer, de ce nu o mapă
 *   În ASCII, 'a' e 97, 'b' e 98, ..., 'z' e 122. Sunt contigue.
 *   Prin urmare
 *
 *       index = c - 'a'     care e c - 97
 *
 *   mapează o literă mică pe 0..25. E aritmetică pe codul
 *   caracterului, nu pe un pointer în șir. Dacă c nu e în
 *   'a'..'z', indicele e în afara intervalului și hash[index] e UB
 *   (spargere de stivă dacă ești ghinionist, corupere tăcută dacă
 *   ești și mai ghinionist). Exemplul e deja cu minuscule. Codul
 *   de producție ar trebui să valideze (sau să plieze A-Z, cum
 *   facem noi).
 *
 *   Un parametru tablou C decade la un pointer. Aici hash e o
 *   locală, deci sizeof(hash) e 26 * sizeof(int). Dacă l-ai
 *   transmite unui helper declarat void f(int hash[26]), sizeof
 *   în f ar fi dimensiunea unui pointer. Regula aia de decay e
 *   de ce funcțiile C iau o lungime pentru tablouri numerice.
 *   Pentru un șir C, sentinela '\0' e lungimea.
 *
 *   De ce un tablou, nu o mapă: alfabetul e mic, dens, și cunoscut
 *   la compilare. O tabelă hash de 26 de noduri e un graf pe heap
 *   cu urmărire de pointeri, alocări extra și constante mai
 *   proaste, ca să stocheze ce e deja un indice perfect. Mapele
 *   câștigă când domeniul cheilor e uriaș sau necunoscut (puncte
 *   de cod Unicode, șiruri oarecare). Pentru 'a'..'z', tabloul e
 *   structura de date.
 *
 *   Cache: 104 octeți sunt una sau două linii de cache. Bucla de
 *   increment peste șir e secvențială pe text; actualizările
 *   hash[] lovesc aceleași linii fierbinți iar și iar. Asta e cât
 *   de locală poate fi numărarea.
 *
 *   Overflow: count-urile încap în int pentru orice șir care
 *   încape în memorie. Overflow-ul interesant e indicele, nu count.
 *
 * Exemplul afișează q.
 */

#include <iostream>
using namespace std;

char mostOccurringLetter(char str[]) {
    int hash[26];
    for (int i = 0; i < 26; i++) {
        hash[i] = 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
        hash[c - 'a']++;
    }
    int mx = 0;
    for (int i = 0; i < 26; i++) {
        if (hash[i] > hash[mx]) {
            mx = i;
        }
    }
    return mx + 'a';
}

int main() {
    char str[] = "mkbqsqjbyq";
    cout << mostOccurringLetter(str) << "\n";
    return 0;
}
