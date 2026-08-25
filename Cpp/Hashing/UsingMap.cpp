/*
 * LESSON — The same frequency problem, now with a hash table
 *
 * Student, return the most common lowercase letter in a string. This
 * time the store is std::unordered_map<char, int>, not int[26]. The
 * answer for "mkbqsqjbyq" is still 'q'. The point is the machine
 * model underneath the map, and when you would actually pay for it.
 *
 * Intuition
 *   A hash table maps an arbitrary key to a slot in an array of
 *   buckets via a hash function, then handles collisions (typically
 *   chaining: a linked list or a tree of nodes in that bucket).
 *   Average lookup and insert are O(1). That average hides a worst
 *   case of O(n) when every key collides into one bucket, and it
 *   hides a much larger constant than a dense array.
 *
 *   We still lowercase, then for each character: look up, increment,
 *   and if the new count beats the champion, record the character.
 *   Ties keep the first winner (strict greater), which matches a
 *   left-to-right scan of the string rather than alphabetical order.
 *   For this sample there is no tie.
 *
 * Complexity
 *   Average time O(n). Worst time O(n^2) if the hash collapses (or
 *   O(n log n) per operation if the implementation tree-ifies long
 *   chains, which some do). Extra memory O(A) heap nodes where A is
 *   the number of distinct keys actually seen, plus the bucket array.
 *
 * Memory management
 *   unordered_map nodes live on the heap. Each insertion of a new
 *   key allocates a node: key, value, next-pointer (and more). That
 *   is not a contiguous count array. Walking the table later would
 *   chase pointers. We do not walk it: we keep a running champion,
 *   so we never pay a full-table scan.
 *
 *   The map object sits on the stack; its buckets and nodes sit on
 *   the heap. Destructor walks and frees them. RAII, no manual free.
 *
 *   const std::string&: no copy of the text.
 *
 * C theory — hash tables vs count arrays, collisions, cache
 *   In C you would roll your own: a bucket array of struct nodes,
 *   malloc per new key, free on teardown. The C++ table is that
 *   design with a well-tested hash and load-factor policy.
 *
 *   Average O(1) assumes a good hash and a load factor bounded away
 *   from "everything in one bucket." Worst O(n) is real: pathological
 *   keys, a bad hash, or an adversarial input. Never quote O(1) as a
 *   guarantee. Quote it as the expected cost.
 *
 *   When the alphabet is huge or unknown — Unicode, 64-bit ids,
 *   strings — you cannot allocate U+1 counters. The table's memory
 *   tracks distinct keys. When the alphabet is 26 lowercase letters,
 *   HashingLetters.cpp is the correct tool: 26 stack ints, no hash,
 *   no collision, no heap, better cache. Use this file when the key
 *   domain does not fit in a small dense index.
 *
 *   Cache: each map[c]++ may walk a chain of heap nodes. Those nodes
 *   were allocated at different times and are not adjacent. The 26
 *   int array sits in one or two cache lines. Same algorithm, wildly
 *   different constants. Big-O does not see cache lines; the CPU does.
 *
 *   operator[] on unordered_map default-inserts 0 if the key is
 *   missing, then you increment. That is convenient and it allocates
 *   a node on first sight of a key. Fine here.
 */

#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>

char mostOccurringLetter(const std::string& str) {
    std::unordered_map<char, int> map;
    int max = 0;
    char maxLetter = 0;
    for (char ch : str) {
        const unsigned char uc = static_cast<unsigned char>(ch);
        const char c = static_cast<char>(std::tolower(uc));
        const int count = ++map[c];
        if (count > max) {
            max = count;
            maxLetter = c;
        }
    }
    return maxLetter;
}

int main() {
    const std::string str = "mkbqsqjbyq";
    std::cout << mostOccurringLetter(str) << '\n';
    return 0;
}
