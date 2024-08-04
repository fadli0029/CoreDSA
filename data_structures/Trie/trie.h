#include "bits/stdc++.h"
using namespace std;

struct TrieNode {
    TrieNode *links[26];
    bool end;

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            links[i] = nullptr;
        }
        end = false;
    }

    bool exists(char c) { return links[c - 'a'] != nullptr; }
};

class Trie {
  private:
    TrieNode *root;
    int idx(char c) { return c - 'a'; }

  public:
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode *node = root;
        for (const auto &c : word) {
            if (!node->exists(c)) {
                node->links[idx(c)] = new TrieNode();
            }
            node = node->links[idx(c)];
        }
        node->end = true;
    }

    bool search(string word) {
        TrieNode *node = root;
        for (const auto &c : word) {
            if (!node->exists(c)) {
                return false;
            }
            node = node->links[idx(c)];
        }
        return node->end == true;
    }

    bool startsWith(string prefix) {
        TrieNode *node = root;
        for (const auto &c : prefix) {
            if (!node->exists(c)) {
                return false;
            }
            node = node->links[idx(c)];
        }
        return true;
    }
};
