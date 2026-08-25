/*
 * LESSON — Palindrome string, ignoring case and non-alphanumerics
 *
 * Student, this is the array palindrome test applied to a sentence.
 * The data is characters, not ints, and most of the work is deciding
 * which characters count.
 *
 * Problem
 *   A string is a valid palindrome if its alphanumeric characters, read
 *   case-insensitively, form a palindrome. Spaces, commas, and other
 *   punctuation are skipped. Sample: "No, it is open on one position"
 *   should print true.
 *
 * Algorithm intuition
 *   Two indices on the string: l from the left, r from the right.
 *   Advance l while the character is not alphanumeric. Retreat r while
 *   the character is not alphanumeric. Compare the two remaining
 *   characters case-insensitively. If they differ, reject. Otherwise
 *   step inward and repeat. The helper isAlphaNumeric defines the
 *   alphabet: ASCII letters and digits.
 *
 * Complexity
 *   Time  O(n): each character is classified a constant number of times
 *   and compared at most once.
 *   Extra space O(1). Do not allocate a filtered copy of the letters.
 *   A second array of only alphanumerics would be correct and O(n)
 *   extra memory; the two-pointer walk makes that allocation unnecessary.
 *
 * Memory management
 *   char s[] decays to char*: a pointer to the first character. Pass n
 *   (the count of characters, not including the terminating '\0').
 *   We avoid vector on purpose. A C string is a contiguous array of
 *   char ending in 0. s[i] is *(s + i). No heap allocation in this
 *   function. l and r are indices, not owning pointers.
 *
 *   In main, sizeof(s) includes the trailing '\0', so the live length
 *   is sizeof(s) - 1. That is the n we pass.
 *
 * C theory — char, ASCII case fold, ctype, UB
 *   We classify bytes with range tests on ASCII: 'A'..'Z', 'a'..'z',
 *   '0'..'9'. For this lesson's English sample, all interesting bytes
 *   are ASCII and fit in positive signed char.
 *
 *   Case folding is a register operation: if c is 'A'..'Z', add
 *   ('a' - 'A'). We do not write the string. The caller's buffer is
 *   unchanged. Locale-dependent classification of bytes is a different
 *   course. If you call tolower from <cctype>, pass the byte as
 *   unsigned char (or an equivalent non-negative int): a signed char
 *   with the high bit set is UB for the C ctype functions.
 *
 *   Contiguous chars mean s[i] is pointer arithmetic. Out of range is
 *   UB, same as any array. Keep l <= r and both in [0, n) while
 *   comparing. After a match we do l++ and r--; if they cross, the
 *   loop ends. For n == 0, skip forming n-1.
 *
 *   Cache: two streams from the ends of a contiguous byte array.
 *   Characters are one byte; a cache line holds 64 of them. Skipping
 *   punctuation is still sequential.
 *
 *   No integer overflow. Mutation: we do not write the string. Case
 *   folding happens in registers for the comparison only.
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
