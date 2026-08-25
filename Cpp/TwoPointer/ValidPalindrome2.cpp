/*
 * LESSON — Palindrome after deleting at most one character
 *
 * Student, the strict palindrome test rejects at the first mismatch.
 * Here you are allowed one deletion. That one degree of freedom is
 * still solvable with two pointers; you do not need to try deleting
 * every character.
 *
 * Problem
 *   Return true if s can be a palindrome after removing at most one
 *   character (including removing none). Sample: "abdeddba" is true.
 *
 * Algorithm intuition
 *   Walk inward as in a normal palindrome. While s[i] == s[j], keep
 *   going. On the first mismatch you must use the deletion: either
 *   skip s[i] and ask whether s[i+1..j] is a palindrome, or skip s[j]
 *   and ask whether s[i..j-1] is a palindrome. If either subrange is
 *   a palindrome, one deletion suffices. If both fail, two or more
 *   mismatches remain and you reject.
 *
 *   You only branch at the first mismatch. A second mismatch inside
 *   a candidate subrange is fatal for that candidate. That is enough,
 *   because any valid single deletion that repairs the string must
 *   delete one of the two disagreeing ends (or a character that this
 *   skip simulates). You do not search the interior first; the ends
 *   are the obstruction.
 *
 * Complexity
 *   Time  O(n): the outer walk plus at most two palindrome checks on
 *   a suffix of the string. Each character is compared O(1) times.
 *   Extra space O(1): indices only. Copying substrings into new buffers
 *   would copy bytes and blow both time and memory. Pass indices into
 *   the original buffer.
 *
 * Memory management
 *   char s[] decays to char*. Pass n because the pointer has no length.
 *   The helper reads s[i]..s[j] by index. No substring allocation. We
 *   avoid vector on purpose. In C you would pass (char *s, int i, int j)
 *   and never copy a piece out.
 *
 *   The characters are contiguous. We only load. In main, n is
 *   sizeof(s) - 1 so we do not count the terminating '\0'.
 *
 * C theory — indices on a byte array, no mutation, overflow, UB
 *   s[i] is a char in a contiguous array. i and j are int. The helper
 *   loops while i < j, so j-- is safe: j is at least i+1. Forming
 *   j = n - 1 on an empty string is a bad index; we treat length < 2
 *   as already true before that.
 *
 *   This lesson does not skip punctuation. Every character counts.
 *   The sample is lowercase letters only. Mixing this with the
 *   alphanumeric filter is a different specification; do not silently
 *   combine them.
 *
 *   Comparison is raw char equality. No ctype, no locale.
 *
 *   Stack: the helper is iterative. If you wrote a recursive palindrome
 *   on n/2, you could overflow the stack. Iteration keeps a constant
 *   frame.
 *
 *   Cache: sequential from both ends, then at most two more sequential
 *   scans of a subrange. Still linear streaming.
 *
 *   In-place mutation is not used. Deleting a character is simulated
 *   by skipping an index, not by memmove of the tail. The caller's
 *   string is unchanged. That is important: a real delete would be
 *   O(n) moves for a contiguous buffer, which you would not want
 *   inside a loop of candidates.
 */

#include <iostream>
using namespace std;

bool isPalindromeRange(char s[], int i, int j) {
    while (i < j) {
        if (s[i] != s[j]) {
            return false;
        }
        i++;
        j--;
    }
    return true;
}

bool validPalindrome(char s[], int n) {
    if (n < 2) {
        return true;
    }
    int i = 0;
    int j = n - 1;
    while (i < j) {
        if (s[i] != s[j]) {
            return isPalindromeRange(s, i + 1, j) || isPalindromeRange(s, i, j - 1);
        }
        i++;
        j--;
    }
    return true;
}

int main() {
    char s[] = "abdeddba";
    int n = sizeof(s) / sizeof(s[0]) - 1;
    if (validPalindrome(s, n)) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    return 0;
}
