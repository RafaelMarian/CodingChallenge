/*
 * LESSON — A 26-slot array for a dense alphabet
 *
 * Student, given a string of lowercase English letters, return the
 * letter that occurs most often. Ties go to the earlier letter in
 * the alphabet (we scan 0..25 and keep a strict greater).
 *
 * Intuition
 *   There are 26 possible keys. 26 is a constant. Put 26 counters in
 *   a row, index them by c - 'a', increment, then scan for the max.
 *   You do not want a tree, a hash table, or a map. You want an array.
 *
 *   Sample "mkbqsqjbyq": q appears three times. Return 'q'.
 *
 * Complexity
 *   Time O(n + 26) = O(n). Extra memory O(1): 26 ints, independent of n.
 *
 * Memory
 *   int hash[26] is an automatic array. It lives on the stack of
 *   mostOccurringLetter. We zero it in a loop. There is no heap
 *   allocation and nothing to free. When the function returns, the
 *   26 ints die with the frame. That is the cheapest correct store
 *   you can have for a tiny dense key set.
 *
 *   26 * sizeof(int) = 104 bytes. A typical stack frame can hold that
 *   without comment. Contrast HashingIntro.cpp, where U+1 ints go on
 *   the heap because U is data-dependent and can be large.
 *
 *   The text is char str[]: a C string, NUL-terminated. In main it is
 *   a real array. Passed into the function it decays to char*. We
 *   walk until str[i] == '\0'. We do not need a separate length.
 *
 * C theory — ASCII, pointer decay, why not a map
 *   In ASCII, 'a' is 97, 'b' is 98, ..., 'z' is 122. They are
 *   contiguous. Therefore
 *
 *       index = c - 'a'     which is c - 97
 *
 *   maps a lowercase letter onto 0..25. That is arithmetic on the
 *   character's code, not on a pointer into the string. If c is not
 *   in 'a'..'z', the index is out of range and hash[index] is UB
 *   (stack smash if you are unlucky, silent corruption if you are
 *   unluckier). The sample is already lowercase. Production code
 *   should validate (or fold A-Z as we do).
 *
 *   A C array parameter decays to a pointer. Here hash is a local,
 *   so sizeof(hash) is 26 * sizeof(int). If you passed it to a helper
 *   declared void f(int hash[26]), sizeof inside f would be the size
 *   of a pointer. That decay rule is why C functions take a length
 *   for numeric arrays. For a C string the sentinel '\0' is the
 *   length.
 *
 *   Why an array, not a map: the alphabet is tiny, dense, and known
 *   at compile time. A hash table of 26 nodes is a heap graph with
 *   pointer chasing, extra allocations, and worse constants, to store
 *   what is already a perfect index. Maps win when the key domain is
 *   huge or unknown (Unicode code points, arbitrary strings). For
 *   'a'..'z', the array is the data structure.
 *
 *   Cache: 104 bytes is one or two cache lines. The increment loop
 *   over the string is sequential on the text; the hash[] updates hit
 *   the same hot lines again and again. This is as local as counting
 *   gets.
 *
 *   Overflow: counts fit in int for any string that fits in memory.
 *   The interesting overflow is the index, not the count.
 *
 * Sample prints q.
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
