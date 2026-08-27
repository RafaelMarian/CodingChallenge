/*
 * LECȚIE — Șir palindrom, ignorând majusculele și non-alfanumericele
 *
 * Studentule, ăsta e testul de palindrom pe tablou aplicat unei fraze.
 * Datele sunt caractere, nu int-uri, și cea mai mare parte a muncii
 * e să decizi care caractere contează.
 *
 * Problemă
 *   Un șir e un palindrom valid dacă caracterele lui alfanumerice,
 *   citite fără distincție de majuscule, formează un palindrom.
 *   Spațiile, virgulele și restul punctuației se sar. Exemplu:
 *   "No, it is open on one position" ar trebui să tipărească true.
 *
 * Intuiție / Algoritm
 *   Doi indici pe șir: l din stânga, r din dreapta. Avansează l cât
 *   timp caracterul nu e alfanumeric. Retrage r cât timp caracterul
 *   nu e alfanumeric. Compară cele două caractere rămase fără
 *   distincție de majuscule. Dacă diferă, respinge. Altfel fă un pas
 *   spre interior și repetă. Helper-ul isAlphaNumeric definește
 *   alfabetul: litere și cifre ASCII.
 *
 * Complexitate
 *   Timp  O(n): fiecare caracter e clasificat de un număr constant de
 *   ori și comparat cel mult o dată.
 *   Memorie extra O(1). Nu aloca o copie filtrată a literelor. Un al
 *   doilea tablou doar cu alfanumerice ar fi corect și O(n) memorie
 *   extra; plimbarea cu doi pointeri face alocarea aia inutilă.
 *
 * Memorie
 *   char s[] decade la char*: un pointer către primul caracter.
 *   Transmite n (numărul de caractere, fără '\0'-ul terminator).
 *   Evităm vector dinadins. Un șir C e un tablou contig de char care
 *   se termină în 0. s[i] e *(s + i). Fără alocare pe heap în funcția
 *   asta. l și r sunt indici, nu pointeri care dețin ceva.
 *
 *   În main, sizeof(s) include '\0'-ul de la capăt, deci lungimea vie
 *   e sizeof(s) - 1. Ăsta e n-ul pe care-l transmitem.
 *
 * Teorie C — char, case fold ASCII, ctype, UB
 *   Clasificăm octeții cu teste de interval pe ASCII: 'A'..'Z',
 *   'a'..'z', '0'..'9'. Pentru exemplul în engleză al lecției, toți
 *   octeții interesanți sunt ASCII și încap într-un signed char
 *   pozitiv.
 *
 *   Case folding-ul e o operație de registru: dacă c e 'A'..'Z',
 *   adună ('a' - 'A'). Nu scriem șirul. Buffer-ul apelantului rămâne
 *   neschimbat. Clasificarea de octeți dependentă de locale e un alt
 *   curs. Dacă apelezi tolower din <cctype>, transmite octetul ca
 *   unsigned char (sau un int nenegativ echivalent): un signed char
 *   cu bitul înalt setat e UB pentru funcțiile ctype din C.
 *
 *   char-urile contigue înseamnă că s[i] e aritmetică de pointer.
 *   În afara intervalului e UB, la fel ca la orice tablou. Ține l <= r
 *   și amândoi în [0, n) cât timp compari. După o potrivire facem
 *   l++ și r--; dacă se încrucișează, bucla se oprește. Pentru n == 0,
 *   sari formarea lui n-1.
 *
 *   Cache: două fluxuri de la capetele unui tablou contig de octeți.
 *   Caracterele sunt un octet; o linie de cache ține 64 dintre ele.
 *   Să sari punctuația tot e secvențial.
 *
 *   Fără overflow pe întregi. Mutație: nu scriem șirul. Case folding-ul
 *   se întâmplă în registre, doar pentru comparație.
 */

#include <iostream>
using namespace std;

bool isAlphaNumeric(char c) {
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

char toLowerAscii(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

bool isPalindrome(char s[], int n) {
    if (n < 2) {
        return true;
    }
    int l = 0;
    int r = n - 1;
    while (l < r) {
        while (l < r && !isAlphaNumeric(s[l])) {
            l++;
        }
        while (l < r && !isAlphaNumeric(s[r])) {
            r--;
        }
        if (l < r) {
            if (toLowerAscii(s[l]) != toLowerAscii(s[r])) {
                return false;
            }
            l++;
            r--;
        }
    }
    return true;
}

int main() {
    char s[] = "No, it is open on one position";
    int n = sizeof(s) / sizeof(s[0]) - 1;
    if (isPalindrome(s, n)) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    return 0;
}
