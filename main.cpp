#include <iostream>
#include "prefix_trie.h"

using namespace std;

int main() {
   const char * seq1 = "ACTG";
   const char * seq2 = "ANAC";
   const char * seq3 = "ANTG";
   const char * seq4 = "NCTG";
   prefix_trie trie;
   const char ** sequences;
   trie.readFile("/Users/ethanyackulic/CLionProjects/hw5/data/covid_genome.fasta",100,10);
    cout << "search result: " << trie.search("ATTAAAGGTT",10) <<endl;
    cout << "search result: " << trie.search("CGAACTTTAA",10) <<endl;

//    cout << "search result: " << trie.fuzzy_search("ACACGAGTAA",10,1) <<endl;

//   trie.insert(seq1,4);
//   trie.insert(seq2, 4);
//    trie.insert(seq3, 4);
//
//    cout << "search result: " << trie.search(seq1,4) <<endl;
//    cout << "search result: " << trie.fuzzy_search(seq4,4,1) <<endl;

   return 0;
}

