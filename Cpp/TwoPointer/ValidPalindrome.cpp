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
 *   A second string of only alphanumerics would be correct and O(n)
 *   extra heap; the two-pointer walk makes that allocation unnecessary.
 *
 * Memory management
 *   const std::string&: read-only alias of the caller's string object.
 *   A std::string, like a vector, is a small stack object (pointer,
 *   size, capacity, or a small-buffer optimization). The character
 *   bytes are contiguous. Since C++11 that contiguity is required:
 *   &s[0] through &s[0] + s.size() is a live array of char, and
 *   s.data() is a pointer to it. Passing the string by value would
 *   copy those bytes. We do not.
 *
 *   No heap allocation in this function. l and r are indices, not
 *   owning pointers.
 *
 * C theory — char signedness, ctype, toupper/tolower, UB
 *   char may be signed or unsigned; the standard allows either. On a
 *   signed-char platform, a byte with value 0xE9 is a negative char.
 *   The C ctype functions (tolower, toupper, isalnum, ...) take an
 *   int that is either EOF or a value representable as unsigned char.
 *   Passing a negative char other than EOF is undefined behavior.
 *   Always convert:
 *     const unsigned char uc = static_cast<unsigned char>(s[i]);
 *     std::tolower(uc);
 *   That conversion maps the byte 0..255 onto a non-negative int.
 *
 *   We still write our own isAlphaNumeric for ASCII so you see the
 *   range tests. They must be done on the unsigned value, or a
 *   negative char could fail 'a' <= c && c <= 'z' in surprising ways
 *   and is never a digit. For this lesson's English sample, all
 *   interesting bytes are ASCII and fit in positive signed char, but
 *   the habit is not optional in real text.
 *
 *   std::tolower / std::toupper use the current C locale. For ASCII
 *   letters they do the obvious mapping. For this problem ASCII is
 *   the intended alphabet. Locale-dependent classification of bytes
 *   is a different course.
 *
 *   Contiguous chars mean s[i] is pointer arithmetic: *(data + i).
 *   Out of range is UB, same as any array. Keep l <= r and both in
 *   [0, n) while comparing. After a match we do ++l and --r; if they
 *   cross, the loop ends. For n == 0, skip forming n-1.
 *
 *   Cache: two streams from the ends of a contiguous byte array.
 *   Characters are one byte; a cache line holds 64 of them. Skipping
 *   punctuation is still sequential.
 *
 *   No integer overflow. Mutation: we do not write the string. Case
 *   folding happens in registers for the comparison only. The caller's
 *   buffer is unchanged.
 */

#include <cctype>
#include <iostream>
#include <string>

bool isAlphaNumeric(char c) {
    const unsigned char uc = static_cast<unsigned char>(c);
    const bool letter = (uc >= 'A' && uc <= 'Z') || (uc >= 'a' && uc <= 'z');
    const bool digit = (uc >= '0' && uc <= '9');
    return letter || digit;
}

bool isPalindrome(const std::string& s) {
    if (s.size() < 2) {
        return true;
    }
    std::size_t l = 0;
    std::size_t r = s.size() - 1;
    while (l < r) {
        while (l < r && !isAlphaNumeric(s[l])) {
            ++l;
        }
        while (l < r && !isAlphaNumeric(s[r])) {
            --r;
        }
        if (l < r) {
            const unsigned char ul = static_cast<unsigned char>(s[l]);
            const unsigned char ur = static_cast<unsigned char>(s[r]);
            if (std::tolower(ul) != std::tolower(ur)) {
                return false;
            }
            ++l;
            --r;
        }
    }
    return true;
}

int main() {
    std::cout << std::boolalpha
              << isPalindrome("No, it is open on one position") << '\n';
    return 0;
}
