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


bool prefix_trie::search(const char * query,int length){
    Node * current_pointer = root;
    for(int i =0; i<length; i++){
        current_pointer = next_ptr(current_pointer,query[i]);
        if(current_pointer==nullptr){
            return false;
        }
    }
    return true;
};

bool prefix_trie::fuzzy_search(const char * query,int length, int mismatch){
    Node * current_pointer = root;
    Node * next_pointer;
    int counter;
    counter = 0;
    for(int i =0; i<length; i++){
        next_pointer = current_pointer;
        current_pointer = next_ptr(current_pointer,query[i]);
        if(current_pointer==nullptr){
            counter = counter + 1;
            current_pointer=next_pointer;
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
           // cout << "counter is :\t" << counter <<endl;
            if (counter > mismatch) {
                return false;
            }else{
            }
        }
    }
    return true;
};

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
