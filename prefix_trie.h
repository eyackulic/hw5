//
// Created by Ethan Yackulic on 4/20/22.
//

#ifndef HW5_PREFIX_TRIE_H
#define HW5_PREFIX_TRIE_H

struct Node{
        Node * A;
        Node * C;
        Node * T;
        Node * G;
        Node * N;
}

class prefix_trie {
private:
public:
            Node * root;
            int depth;
            prefix_trie();
            prefix_trie(const char * filename);
            ~prefix_trie();
            void insert(char * query, int numb);
            void remove(char * query, int numb);	// to delete, you need to traverse to flast independent string character
            bool search(char* query, int numb, int MM);	// mismatch tolerance ; may need to add another variable to count numbers of errors in match


};


#endif //HW5_PREFIX_TRIE_H
