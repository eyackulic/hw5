#include <iostream>
#include "prefix_trie.h"

using namespace std;

int main() {

     prefix_trie trie;
    prefix_trie trie1;
    prefix_trie trie2;
    prefix_trie trie3;
    prefix_trie trie4;

  // trie.readFile("/Users/ethanyackulic/CLionProjects/hw5/data/covid_genome.fasta",10,10);
    trie.singleArray("/Users/ethanyackulic/CLionProjects/hw5/data/covid_genome.fasta");
    trie.findRandomGM16Mers(36,5000);
   // trie1.singleArray("/Users/ethanyackulic/CLionProjects/hw5/data/covid_genome.fasta");
    //trie1.findErrorMers(10,5000,.05);
    trie2.singleArray("/Users/ethanyackulic/CLionProjects/hw5/data/covid_genome.fasta");
    trie2.findRandomGM16Mers(36,50000);
    trie3.singleArray("/Users/ethanyackulic/CLionProjects/hw5/data/covid_genome.fasta");
    trie3.findRandomGM16Mers(36,500000);
    trie4.singleArray("/Users/ethanyackulic/CLionProjects/hw5/data/covid_genome.fasta");
    trie4.findRandomGM16Mers(36,1000000);



   return 0;
}

