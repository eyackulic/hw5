#include <iostream>
#include "prefix_trie.h"

using namespace std;

int main(int argc, char ** argv) {
    if (strcmp(argv[1], "1a") == 0) {
        prefix_trie trie(argv[2],36, 5000,0);
        prefix_trie trie2(argv[2],36, 50000,0);
        prefix_trie trie3(argv[2],36, 100000,0);
        prefix_trie trie4(argv[2],36, 500000,0);
        prefix_trie trie5(argv[2],36, 1000000,0);

    }
    if (strcmp(argv[1], "1b") == 0) {
        prefix_trie trie(argv[2],36, 5000,0.05);
        prefix_trie trie2(argv[2],36, 50000,0.05);
        prefix_trie trie3(argv[2],36, 100000,0.05);
        prefix_trie trie4(argv[2],36, 500000,0.05);
        prefix_trie trie5(argv[2],36, 1000000,0.05);

    }
   return 0;
}

