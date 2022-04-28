//
// Created by Ethan Yackulic on 4/20/22.
//

#include "prefix_trie.h"
using namespace std;

prefix_trie::prefix_trie(){
    root = new Node;
    node_counter = 0;
    frag_found_counter = 0;
    genome_size = 0;
};
prefix_trie::prefix_trie(const char * filename,int seq_size, int iterations, float p){
    root = new Node;
    node_counter = 0;
    frag_found_counter = 0;
    genome_size = 0;
    singleArray(filename);
    findErrorMers(seq_size,iterations,p);

};
prefix_trie::~prefix_trie() {
    root = new Node;
    Node * current_pointer = root;
  //  int level = 0;
  //  Node *next_pointer = next_ptr(current_pointer, query[level]);
  //  if (next_pointer == nullptr) {
        delete [] current_pointer;

  //  } else if (level == length) {
//        delete[] current_pointer;
    }
//level++;


//};


Node * prefix_trie::next_ptr(Node *current_pointer, const char query) {
    if (query == 'A') {
        return current_pointer->A;
    }
    else if (query == 'C') {
       return current_pointer->C;
    }
    else if (query == 'G') {
        return current_pointer->G;
    }
    else if (query == 'T') {
        return current_pointer->T;
    }
    else if (query == 'N') {
        return current_pointer->N;
    }

}


bool prefix_trie::fuzzy_search(Node * current_pointer,int length, const char * query, int mismatch, int level) {
    //make sure counter is initialized to 0
    char *new_query;
    int level = 0;
//    if (next_pointer == nullptr) {
    Node *next_pointer = root;
    //   }
    Node *current_pointer;
//    for (int i = 0; i < length; i++) {
    //save position at each step before incrementing
    if (current_pointer == nullptr || mismatch > 1) {
        return false;
//
    } else if (level == length) {
        frag_found_counter++;
        return true;
    }

    Node *next_pointer = next_ptr(current_pointer, query[level]);
    bool out = false, outA = false, outC = false, outG = false, outT = false, outN = false;

    if (next_pointer != nullptr) {
        out = fuzzy_search(next_pointer, length, query, mismatch, level + 1);
    } else {
        mismatch++;
        outA = fuzzy_search(current_pointer->A, length, query, mismatch, level + 1);
        outC = fuzzy_search(current_pointer->C, length, query, mismatch, level + 1);
        outG = fuzzy_search(current_pointer->G, length, query, mismatch, level + 1);
        outT = fuzzy_search(current_pointer->T, length, query, mismatch, level + 1);
        outN = fuzzy_search(current_pointer->N, length, query, mismatch, level + 1);
    }
}

void prefix_trie::insert(char * query, int length) {
    Node *current_pointer = root;
    int unique = 0;
    for (int i = 0; i < length; i++) {
        if (query[i] == 'A') {
            if (current_pointer->A == nullptr) {
                current_pointer->A = new Node;
                unique = unique + 1;
            } else {
            }
            current_pointer = current_pointer->A;
        } else if (query[i] == 'C') {
            if (current_pointer->C == nullptr) {
                current_pointer->C = new Node;
                unique = unique + 1;
            } else {
            }
            current_pointer = current_pointer->C;
        } else if (query[i] == 'G') {
            if (current_pointer->G == nullptr) {
                current_pointer->G = new Node;
                unique = unique + 1;
            } else {
            }
            current_pointer = current_pointer->G;
        } else if (query[i] == 'T') {
            if (current_pointer->T == nullptr) {
                current_pointer->T = new Node;
                unique = unique + 1;
            } else {
            }
            current_pointer = current_pointer->T;
        } else {
            if (current_pointer->N == nullptr) {
                current_pointer->N = new Node;
                unique = unique + 1;
            } else { ;
            }
            current_pointer = current_pointer->N;
        }
    }
    if (unique > 0) {
        unique_records = unique_records + 1;
        node_counter = node_counter + unique;
    }
}

int prefix_trie::generateRandom( int genome_size, int seq_size){
    // function that generates a random number for indexing genome
    //Function calls:
    //Function called in: findRandomGM16Mers; HT.cpp; line
    int r_num = rand();
    int randomNumber =  r_num % (genome_size - seq_size - 1);
    return randomNumber;
}

void prefix_trie::generateSequences( int g_index, int seq_size){
    // function that generates all sequences based on a starting index position
    //Function calls:
    //Function called in:
    //              findRandom36Mers; HT.cpp; line 262

    char * random_genome_sequence = new char[seq_size+1];
    for (int i=0; i < seq_size; i++){
        random_genome_sequence[i] = genome_array[g_index + i];
    }
    random_genome_sequence[seq_size] = '\0';
    insert(random_genome_sequence,seq_size);
}


char * prefix_trie::generateQueries( int g_index, int seq_size){
    // function that generates all sequences based on a starting index position
    // returns char *
    //Function calls:
    //Function called in:
    //              findRandom36Mers; prefix_trie.cpp; line

    char * random_genome_sequence = new char[seq_size+1];
    for (int i=0; i < seq_size; i++){
        random_genome_sequence[i] = genome_array[g_index + i];
    }
    random_genome_sequence[seq_size] = '\0';
    return random_genome_sequence;
}


void prefix_trie::singleArray(const char *filename) {
    //creates a single array of all input sequences
    //creates a counter of all characters in array
    //Function calls:
    //Function called in:
    //          getSequence; prefix_trie.cpp ; line
    //          ; prefix_trie.cpp; line


    ifstream input(filename);
    genome_array = new char[600000]; // should be big enough to hold it
    char temp_buffer[1000];
    char current_char;

//skip first line
    input.getline(temp_buffer, 100);
    //iterate through all entries
    while (input.get(current_char)) {
        if (current_char == 'A' || current_char == 'G' || current_char == 'T' || current_char == 'C' ||
            current_char == 'N') {
            //fill array
            genome_array[genome_size] = current_char;
            //increment count
            genome_size++;

        }
    }
}
    void prefix_trie::findRandom36Mers(int seq_size, int iterations){
        // function that generates a random number for indexing genome
        // sequences of size seq_size are generated based on random indexing of the original sequences
        // these sequences are then searched for within the original dataset
        // process is repeated for n = iterations times
        // number of results returned should be equal to number of iterations
        //Function calls:
        //          generateRandom; prefix_trie.cpp; line
        //          generateSequences; prefix_trie.cpp; line
        //          radixSearch; prefix_trie.cpp; line
        //Function called in:
        int index;
        char * r_seq;
        cout << "number of iterations:\t" <<iterations <<endl;
        for (int i = 0; i < iterations; i++) {
            index = generateRandom(genome_size, seq_size);
            generateSequences(index, seq_size);
        }
            for(int i=0; i < genome_size-seq_size+1; i++){
               r_seq = generateQueries(i,seq_size);
                fuzzy_search(nullptr, seq_size,r_seq,0,0);
            }
        cout << "total fragments found in prefix trie:\t " << frag_found_counter << endl;
        cout << "total number of unique nodes: \t" << node_counter <<endl;
    }

double prefix_trie::randomFloat(){
    //finds a random float value (i.e. random decimal between 0-1)
    //Function calls:
    //Function called in: bernoulli_trial; prefix_trie.cpp; line
    double new_val;

    new_val = (double)rand()/(double)RAND_MAX;
    return new_val;
}
bool prefix_trie::bernoulli_trial(float p){
    //TRUE/FALSE - does random float value pass bernoulli trial based on designated p?
    //Function calls: randomFloat; prefix_trie.cpp; line
    //Function called in: generateFalseSequences; prefix_trie.cpp; line
    float new_val;
    new_val = randomFloat();
    if(new_val <= p) {
        return true;
    }else{
        return false;
    }
}

char prefix_trie::random_char(char original){
    //returns a randomly selected character that does not equal input character
    // used for introducing erroneous characters into sequence
    //Function calls:
    //Function called in: generateFalseSequences; prefix_trie.cpp; line
    char possible_vals[4] = {'A', 'C', 'G', 'T'};
    char rand_vals = original;
    int random_number;

    while(rand_vals == original){
        random_number = rand() % 4;
        rand_vals = possible_vals[random_number];
    }

    return rand_vals;
}

void prefix_trie::generateFalseSequences( int g_index, int seq_size, float p) {
    //function that uses bernoulli_trial, based on input p,
    //to test when to replace characters in a sequence in order to produce a p% error rate
    //when the bernoulli trial is TRUE, a switch is made using random_char
    //otherwise, the sequence enters the original character
    // void return; inserts false sequences into prefix trie
    //
    //Function calls:
    //          bernoulli_trial; prefix_trie.cpp; line
    //          random_char; prefix_trie.cpp; line
    //          insert; prefix_trie; line
    //Function called in:
    //          findErrorMers; prefix_trie.cpp; line
    char *random_genome_sequence = new char[seq_size + 1];
    for (int i = 0; i < seq_size; i++) {
        if (bernoulli_trial(p)) {
            random_genome_sequence[i] = random_char(genome_array[g_index + i]);
        } else {
            random_genome_sequence[i] = genome_array[g_index + i];
        }
        random_genome_sequence[seq_size] = '\0';
    }
    insert(random_genome_sequence,seq_size);
}

void prefix_trie::findErrorMers(int seq_size, int iterations,float p){
    // function that generates a random number for indexing genome
    // sequences of size seq_size are generated based on random indexing of the original sequences
    // these sequences are then searched for within the original dataset
    // process is repeated for n = iterations times
    //
    //Function calls:
    //          generateRandom; prefix_trie.cpp; line
    //          generateFalseSequences; prefix_trie.cpp; line
    //          generateQueries; prefix_trie.cpp; line
    //          fuzzy_search; prefix_trie.cpp; line
    //Function called in:
    int index;
    char * r_seq;
    frag_found_counter = 0;
    node_counter = 0;
    cout << "number of iterations:\t" <<iterations <<endl;
    for (int i = 0; i < iterations; i++) {
        index = generateRandom(genome_size, seq_size);
        generateFalseSequences(index, seq_size, p);
    }
    for(int i=0; i < genome_size-seq_size+1; i++){
        r_seq = generateQueries(i,seq_size);
        fuzzy_search(nullptr, seq_size,r_seq,0,0);
    }
    cout << "total fragments found in " << p << "% error-based prefix trie:\t " << frag_found_counter << endl;
    cout << "total number of unique nodes with " << p <<"% error-based prefix trie: \t" << node_counter <<endl;
}
