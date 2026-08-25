/*
 * LESSON — Can the string become a palindrome by deleting at most one?
 *
 * Student, this is the same decision procedure as ValidPalindrome2.
 * The framing is the question you should ask out loud: not "is it a
 * palindrome," but "is it at most one edit away from being one," where
 * the only edit is deletion. Write it as its own function so the
 * specification stays in the name.
 *
 * Problem
 *   Given a string of characters that all count (no punctuation filter),
 *   return true if you can delete at most one character and obtain a
 *   palindrome. Deleting zero characters is allowed. Sample: "aebbeba"
 *   is true (delete the extra 'e' or the extra 'b' on the mismatched
 *   pair, depending on which skip works).
 *
 * Algorithm intuition
 *   Two pointers from the ends. Equal characters are already doing
 *   their palindrome job; move inward. The first mismatch is the only
 *   place you spend the deletion. Try skipping the left character:
 *   the remainder must be a strict palindrome. Or skip the right
 *   character. If either try succeeds, the string can be a palindrome.
 *   If the pointers meet with no mismatch, it already is one.
 *
 *   Why not try every deletion: there are n candidates, each check is
 *   O(n), total O(n^2). The first mismatch pins the deletion to one of
 *   two indices. That is the greedy structure of the problem.
 *
 *   Trace "aebbeba":
 *     a ... a match
 *     e ... b mismatch
 *     skip left  (bbeba from the remaining range): b vs b, b vs e fail
 *     skip right (aebbe  wait: skip j, compare i..j-1 which is "ebbe"):
 *       e vs e, b vs b. Success.
 *
 * Complexity
 *   Time  O(n). Extra space O(1). Same bounds as ValidPalindrome2.
 *
 * Memory management
 *   const std::string&. Indices into the existing contiguous buffer.
 *   No substr. No extra std::string. No heap traffic. The helper
 *   borrows the same object. Ownership stays with the caller. Stack
 *   frames are constant size: a few size_t and the string reference
 *   (one pointer).
 *
 *   In C: int can_be_palindrome(const char *s, size_t n). You would
 *   not strdup. You would not write a temporary without the skipped
 *   byte. Skipping is an index bump.
 *
 * C theory — two views of the same bytes, UB, cache
 *   The outer walk and the helper both read the same array. There is
 *   no aliasing hazard because nobody writes. Concurrent mutation
 *   would be a data race (UB); this program is single-threaded.
 *
 *   size_t indices, i < j before s[j] and before j-1. On mismatch we
 *   evaluate i+1 and j-1. Because i < j, j >= 1, so j-1 does not wrap,
 *   and i+1 <= j, so i+1 is <= the last valid index. The helper may
 *   receive i == j (empty or one-char range after skip), which is a
 *   palindrome and the loop does not run.
 *
 *   Cache: still sequential. The second helper scan may re-read bytes
 *   the first helper already touched; they remain hot in L1.
 *
 *   No overflow, no ctype. No in-place mutation: deletion is virtual.
 *   A physical delete in a contiguous string is memmove of the tail
 *   and a size decrement. Doing that once is O(n). Doing that for
 *   each candidate is the O(n^2) time and the O(n) writes you avoided.
 *
 *   Returning bool is a byte in a register in practice. Printing with
 *   std::boolalpha writes the text true or false.
 */

#include <iostream>
#include <string>

bool isPalindromeRange(const std::string& s, std::size_t i, std::size_t j) {
    while (i < j) {
        if (s[i] != s[j]) {
            return false;
        }
        ++i;
        --j;
    }
    return true;
}

bool canBeAPalindrome(const std::string& s) {
    if (s.size() < 2) {
        return true;
    }
    std::size_t i = 0;
    std::size_t j = s.size() - 1;
    while (i < j) {
        if (s[i] != s[j]) {
            return isPalindromeRange(s, i + 1, j) || isPalindromeRange(s, i, j - 1);
        }
        ++i;
        --j;
    }
    return true;
}

int main() {
    std::cout << std::boolalpha << canBeAPalindrome("aebbeba") << '\n';
    return 0;
}
