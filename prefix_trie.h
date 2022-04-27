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
    char **query_array;
    char * genome_array;
    int genome_size;
    int node_counter;
    int num_of_lines_read;
    Node *root;
    int depth;

    prefix_trie();

    prefix_trie(const char *filename);

    ~prefix_trie();

    void insert(const char *query, int length);

    void insert(char *query, int length);

//            void remove(const char * query, int length, int MM);	// to delete, you need to traverse to flast independent string character
    bool search(Node * current_pointer,const char *query,
                int length);    // mismatch tolerance ; may need to add another variable to count numbers of errors in match
    bool fuzzy_search(const char *query, int length, int MM, int level);
    bool fuzzy_search(Node* pointer, int length,  const char *query,int MM, int level);

    Node *next_ptr(Node *current_pointer, char query);

    int getLength(const char *filename);

    void readFile(const char *filename, int lines_to_read, int seq_length);

    void smartCheck(Node *current_pointer);

    void groupInsert(char *line, int seq_size);
    char * generateQueries(int g_index, int seq_size);
    int generateRandom(int genome_size, int seq_size);
    void generateSequences(int g_index, int seq_size);
    void findRandomGM16Mers(int seq_size, int iterations);
    void singleArray(const char * filename);
    double randomFloat();
    bool bernoulli_trial(float p);
    char random_char(char original);
    char * generateFalseSequences(int g_index,int seq_size,float p);
    void findErrorMers(int seq_size, int iterations, float p);
};
#endif //HW5_PREFIX_TRIE_H
