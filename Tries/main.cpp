#include <iostream>
#include <string>
#include <unordered_map>
#include <iomanip>
using namespace std;

const int alphabetSize{26};

struct Trie{
    bool isLeaf;
    unordered_map<char, Trie*> map;
};

Trie* getTrieNode() {
    Trie* node = new Trie;
    node->isLeaf = false;
    return node;
}

void insert(Trie*& head, const string& str) {
    if (head == nullptr) {
        head = getTrieNode();
    }
    
    Trie* curr = head;
    for (const auto& c : str) {
        if (curr->map.find(c) == curr->map.end()) {
            curr->map[c] = getTrieNode();
        }
        curr = curr->map[c];
    }
    
        curr->isLeaf = true;
}


bool search(Trie* head, const string& str) {
    if (head == nullptr) {
        return false;
    }
    
    Trie* curr = head;
    for (const auto& c : str) {        
        if (curr->map.find(c) != curr->map.end()) {
             curr = curr->map[c];
        }
        else {
            return curr->isLeaf;
        }           
    }
    return curr->isLeaf;
}



bool deletion(Trie* curr, const char* s) {
    Trie* oldCurr = curr;
    if (curr == nullptr) return false;
    if (curr->isLeaf && *s == '\0') {     
        curr->isLeaf = false;
        return true;
    }
    else if (curr->map.find(*s) != curr->map.end()) {
        curr = curr->map[*s];
    }
    else {
        return false;
    }
    
    bool cond = {deletion(curr, s + 1)};
    static bool res{true};
    if (cond && oldCurr->isLeaf == false && res && curr->map.size() == 0) {
        oldCurr->map.erase(*s);
        delete curr;
    }
    else {
        res = false;
    }
    return cond;
}
int main() {
 Trie* head = nullptr;
 
    insert(head, "bear");
    insert(head, "bell");
    cout << boolalpha;
    cout << deletion(head, "bell") << endl;
    
    cout << search(head, "bear") << endl;
    return 0;
}