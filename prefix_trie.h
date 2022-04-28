//
// Created by Ethan Yackulic on 4/20/22.
//

#ifndef HW5_PREFIX_TRIE_H
#define HW5_PREFIX_TRIE_H
#include <iostream>
#include <fstream>
#include <stdlib.h>
struct Node{
        Node * A;
        Node * C;
        Node * T;
        Node * G;
        Node * N;
        char character;

        Node(){
            A = nullptr;
            C = nullptr;
            T = nullptr;
            G = nullptr;
            N = nullptr;
        }
   //     bool terminal; all items are same length, otherwise include this
};

class prefix_trie {
private:

public:
    int frag_found_counter;
    char * genome_array;
    int genome_size;
    int unique_records;
    int node_counter;
    Node *root;

    //constructors
    prefix_trie();
    prefix_trie(const char *filename, int seq_size, int iterations, float p);
    //destructor
    ~prefix_trie();

    void insert(char *query, int length);
    bool fuzzy_search(Node* pointer, int length,  const char *query,int MM, int level);

    Node *next_ptr(Node *current_pointer, char query);

    char * generateQueries(int g_index, int seq_size);
    int generateRandom(int genome_size, int seq_size);
    void generateSequences(int g_index, int seq_size);
    void findRandom36Mers(int seq_size, int iterations);
    void singleArray(const char * filename);
    double randomFloat();
    bool bernoulli_trial(float p);
    char random_char(char original);
    void generateFalseSequences(int g_index,int seq_size,float p);
    void findErrorMers(int seq_size, int iterations, float p);
};
#endif //HW5_PREFIX_TRIE_H
