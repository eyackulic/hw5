//
// Created by Ethan Yackulic on 4/20/22.
//

#include "prefix_trie.h"
prefix_trie::prefix_trie(){};
prefix_trie::prefix_trie(const char * filename){};
prefix_trie::~prefix_trie() {};
void prefix_trie::insert(const char * query, int length) {
    Node *current_pointer = root;

    for (int i = 0; i < length; i++) {
            if (query[i] == 'A') {
                if(current_pointer->A == nullptr){
                    current_pointer->A = new Node;
                }else{
                }
                current_pointer = current_pointer->A;
            }
        else if (query[i] == 'C') {
            if(current_pointer->C == nullptr){
                current_pointer->C = new Node;
            }else{
            }
                current_pointer = current_pointer->C;
        }
       else if (query[i] == 'G') {
            if(current_pointer->G == nullptr){
                current_pointer->G = new Node;
            }else{
            }
                current_pointer = current_pointer->G;
        }
        else if (query[i] == 'T') {
            if(current_pointer->T == nullptr){
                current_pointer->T = new Node;
            }else{
            }
                current_pointer = current_pointer->T;
        }
        else {
            if(current_pointer->N == nullptr){
                current_pointer->N = new Node;
            }else{;
            }
                current_pointer = current_pointer->N;
        }
    }
}


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


bool prefix_trie::search(Node * current_pointer, const char * query,int length){
    if (current_pointer == nullptr) {
        current_pointer = root;
    }
    for(int i =0; i<length; i++){
        current_pointer = next_ptr(current_pointer,query[i]);
        if(current_pointer==nullptr){
            return false;
        }
    }
    return true;
};

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
    if(current_pointer == nullptr || mismatch > 1){
        return false;
//
    }else if(level == length){
//        frag_found_counter ++;
        return true;
    }

    Node * next_pointer  = next_ptr(current_pointer, query[level]);
    bool out = false, outA = false, outC = false,outG = false,outT = false,outN = false;

    if(next_pointer != nullptr){
      out =  fuzzy_search(next_pointer, length, query, mismatch, level+1);
    }else {
        mismatch++;
        outA = fuzzy_search(current_pointer->A, length, query, mismatch, level + 1);
        outC = fuzzy_search(current_pointer->C, length, query, mismatch, level + 1);
        outG = fuzzy_search(current_pointer->G, length, query, mismatch, level + 1);
        outT = fuzzy_search(current_pointer->T, length, query, mismatch, level + 1);
        outN = fuzzy_search(current_pointer->N, length, query, mismatch, level + 1);
    }
        if (out || outA || outC || outG || outT || outN) {
            frag_found_counter++;
            return true;
        } else {
            return false;
        }

}

void prefix_trie::smartCheck(Node * current_pointer){
    if(next_ptr(current_pointer, 'A') != nullptr){
        current_pointer = next_ptr(current_pointer, 'A');
    }
    else if(next_ptr(current_pointer, 'C') != nullptr){
        current_pointer = next_ptr(current_pointer, 'C');
    }
    else if(next_ptr(current_pointer, 'G') != nullptr){
        current_pointer = next_ptr(current_pointer, 'G');
    }
    else if(next_ptr(current_pointer, 'T') != nullptr){
        current_pointer = next_ptr(current_pointer, 'T');
    }
    else if(next_ptr(current_pointer, 'N') != nullptr){
        current_pointer = next_ptr(current_pointer, 'N');
    }
}

void prefix_trie::readFile(const char * filename, int lines_to_read, int seq_length) {

    ifstream input;        //create filestream to read the file
    input.open(filename);        //initialize the filestream by pointing it to the right file
    char *temp_head = new char[1000];
    char * line;
 //   char *temp_read = new char[1000];
    if (lines_to_read == 0) {
        num_of_lines_read = getLength(filename);
    } else{
        num_of_lines_read = lines_to_read;
    }
//    cout << "Reading " << num_of_lines_read << " lines" << endl;
    query_array = new char*[num_of_lines_read];
     input >> temp_head; //read in the header line
    for (int i = 0; i < num_of_lines_read; i++) {
        query_array[i] = new char[71];
        input >> query_array[i];//read in the read line
        line = query_array[i];
        groupInsert(line,seq_length);
        //    cout << "reading in line: " << i << '\t' << query_array[i] << endl;

    }
        cout << "The number of nodes is:\t" << node_counter << endl;
}

int prefix_trie::getLength(const char *filename) {
    fstream input;
    input.open(filename);

    char line_buffer[100];
    char * temp_buff;
    int length_count = 0;
    input >> temp_buff;

    while (input.good()) { // until input no longer works
        length_count++; //add to length count
        input >> line_buffer; //temp storage
    }
//    divide counter by 2 for header and line
    int length = length_count ;
    return length;
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
        node_counter = node_counter + 1;
    }
}

void prefix_trie::groupInsert(char * line, int seq_size){
    char * fragment;
    for (int i=0; i <70 - seq_size+1;i++){
        fragment = new char[seq_size+1];
        for(int j=0;j < seq_size; j++){
            fragment[j] = line[i+j];
        }
        fragment[seq_size] = '\0';
        insert(fragment,seq_size);

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
    //              findRandomGM16Mers; HT.cpp; line 262
    //              findAll; HT.cpp; line 418
   // singleArray(filename);
    char * random_genome_sequence = new char[seq_size+1];
    for (int i=0; i < seq_size; i++){
        random_genome_sequence[i] = genome_array[g_index + i];
    }
    random_genome_sequence[seq_size] = '\0';
    insert(random_genome_sequence,seq_size);
//    return random_genome_sequence;
}


char * prefix_trie::generateQueries( int g_index, int seq_size){
    // function that generates all sequences based on a starting index position
    //Function calls:
    //Function called in:
    //              findRandomGM16Mers; HT.cpp; line 262
    //              findAll; HT.cpp; line 418
    // singleArray(filename);
    char * random_genome_sequence = new char[seq_size+1];
    for (int i=0; i < seq_size; i++){
        random_genome_sequence[i] = genome_array[g_index + i];
    }
    random_genome_sequence[seq_size] = '\0';
    //insert(random_genome_sequence,seq_size);
    return random_genome_sequence;
}


void prefix_trie::singleArray(const char *filename) {
    //creates a single array of all input sequences
    //creates a counter of all characters in array
    //Function calls:
    //Function called in:
    //          getSequence; HT.cpp ; line 145
    //          FASTAreadset_HT::FASTAreadset_HT; line 17


    ifstream input(filename);
    genome_array = new char[600000]; // should be big enough to hold it
    char temp_buffer[1000];
    char current_char;
    genome_size = 0;

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
    void prefix_trie::findRandomGM16Mers(int seq_size, int iterations){
        // function that generates a random number for indexing genome
        // sequences of size seq_size are generated based on random indexing of the original sequences
        // these sequences are then searched for within the original dataset
        // process is repeated for n = iterations times
        // number of results returned should be equal to number of iterations
        //Function calls:
        //          generateRandom; HT.cpp; line 239
        //          generateSequences; HT.cpp; line 248
        //          radixSearch; HT.cpp; line 208
        //Function called in:
        int index;
        char * r_seq;
        node_counter = 0;
        cout << "number of iterations:\t" <<iterations <<endl;
        for (int i = 0; i < iterations; i++) {
            index = generateRandom(genome_size, seq_size);
            generateSequences(index, seq_size);
        }
        frag_found_counter = 0;
            for(int i=0; i < genome_size-seq_size; i++){
               r_seq = generateQueries(i,seq_size);
                fuzzy_search(nullptr, seq_size,r_seq,0,0);
            }
        cout << "total fragments found in prefix trie: " << frag_found_counter << endl;
        cout << "total number of unique nodes: \t" << node_counter <<endl;
    }

double prefix_trie::randomFloat(){
    //finds a random float value (i.e. random decimal between 0-1)
    //Function calls:
    //Function called in: bernoulli_trial; HT.cpp; line 344
    double new_val;

    new_val = (double)rand()/(double)RAND_MAX;
    return new_val;
}
bool prefix_trie::bernoulli_trial(float p){
    //TRUE/FALSE - does random float value pass bernoulli trial based on designated p?
    //Function calls: randomFloat; HT.cpp; line 335
    //Function called in: generateFalseSequences; HT.cpp; line 374
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
    //Function called in: generateFalseSequences; HT.cpp; line 374
    char possible_vals[4] = {'A', 'C', 'G', 'T'};
    char rand_vals = original;
    int random_number;

    while(rand_vals == original){
        random_number = rand() % 4;
        rand_vals = possible_vals[random_number];
    }

    return rand_vals;
}

char * prefix_trie::generateFalseSequences( int g_index, int seq_size, float p) {
    //function that uses bernoulli_trial, based on input p,
    //to test when to replace characters in a sequence in order to produce a p% error rate
    //when the bernoulli trial is TRUE, a switch is made using random_char
    //otherwise, the sequence enters the original character
    //Function calls:
    //          bernoulli_trial; HT.cpp; line 344
    //          random_char; HT.cpp; line 357
    //Function called in:
    //          findMistakes; HT.cpp; line 397
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
    // number of results returned should be equal to number of iterations
    //Function calls:
    //          generateRandom; HT.cpp; line 239
    //          generateSequences; HT.cpp; line 248
    //          radixSearch; HT.cpp; line 208
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
    for(int i=0; i < genome_size-seq_size; i++){
        r_seq = generateQueries(i,seq_size);
        fuzzy_search(nullptr, seq_size,r_seq,0,0);
    }
    cout << "total fragments found in error-based prefix trie: " << frag_found_counter << endl;
    cout << "total number of unique nodes in error-based prefix trie: \t" << node_counter <<endl;
}
