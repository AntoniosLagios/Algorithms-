//B-Tree Search (Used in Databases & Indexing)
#include <iostream>
using namespace std;

class BTreeNode {
public:
    int *keys;
    int t;
    BTreeNode **children;
    int n;
    bool leaf;

    BTreeNode(int _t, bool _leaf);
    void traverse();
    BTreeNode* search(int k);

    friend class BTree;
};

class BTree {
public:
    BTreeNode *root;
    int t;

    BTree(int _t) { root = NULL; t = _t; }
    void traverse() { if (root) root->traverse(); }
    BTreeNode* search(int k) { return (root == NULL) ? NULL : root->search(k); }
};

// BTreeNode constructor
BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys = new int[2*t-1];
    children = new BTreeNode *[2*t];
    n = 0;
}

// Traverse the tree
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf) children[i]->traverse();
        cout << " " << keys[i];
    }
    if (!leaf) children[i]->traverse();
}

// Search key in BTree
BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i]) i++;

    if (keys[i] == k) return this;
    if (leaf) return NULL;
    return children[i]->search(k);
}

int main() {
    BTree t(3);
    cout << "B-Tree implementation (insert not implemented here)" << endl;
    return 0;
}
//PageRank Algorithm (Simplified)
#include <vector>

void pageRank(vector<vector<int>> &links, vector<double> &ranks, int iterations) {
    int N = ranks.size();
    vector<double> newRanks(N, 1.0 / N);

    for (int iter = 0; iter < iterations; iter++) {
        fill(newRanks.begin(), newRanks.end(), 0);
        for (int i = 0; i < N; i++) {
            int outLinks = links[i].size();
            if (outLinks == 0) continue;

            for (int j : links[i])
                newRanks[j] += ranks[i] / outLinks;
        }
        ranks = newRanks;
    }
}

int main() {
    vector<vector<int>> links = {{1, 2}, {2}, {0}, {2, 0}};
    vector<double> ranks(4, 1.0 / 4);
    
    pageRank(links, ranks, 10);

    cout << "PageRank Scores:\n";
    for (double rank : ranks) cout << rank << " ";
    return 0;
}
//Monte Carlo Search Algorithm
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

double monteCarloPi(int iterations) {
    int insideCircle = 0;
    
    for (int i = 0; i < iterations; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        
        if (x*x + y*y <= 1) insideCircle++;
    }

    return 4.0 * insideCircle / iterations;
}

int main() {
    srand(time(0));
    int iterations = 1000000;
    cout << "Approximate Pi: " << monteCarloPi(iterations) << endl;
    return 0;
}
// Bloom Filter (Probabilistic Search)
#include <iostream>
#include <bitset>
#include <vector>
#include <functional>

using namespace std;

const int BLOOM_SIZE = 1000;
bitset<BLOOM_SIZE> bloomFilter;

void addToBloomFilter(const string &s) {
    hash<string> hasher;
    bloomFilter[hasher(s) % BLOOM_SIZE] = 1;
}

bool mightContain(const string &s) {
    hash<string> hasher;
    return bloomFilter[hasher(s) % BLOOM_SIZE];
}

int main() {
    vector<string> words = {"hello", "world", "bloom", "filter"};
    
    for (const string &word : words)
        addToBloomFilter(word);

    cout << "Does Bloom filter contain 'hello'? " << mightContain("hello") << endl;
    cout << "Does Bloom filter contain 'chatgpt'? " << mightContain("chatgpt") << endl;

    return 0;
}
//Knuth-Morris-Pratt (KMP) Algorithm
#include <iostream>
#include <vector>

using namespace std;

void computeLPS(string pattern, vector<int> &lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < pattern.length()) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) len = lps[len - 1];
            else { lps[i] = 0; i++; }
        }
    }
}

void KMP(string text, string pattern) {
    int n = text.length(), m = pattern.length();
    vector<int> lps(m, 0);
    computeLPS(pattern, lps);

    int i = 0, j = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++, j++;
        }
        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            j ? j = lps[j - 1] : i++;
        }
    }
}

int main() {
    string text = "abxabcabcaby";
    string pattern = "abcaby";
    KMP(text, pattern);
    return 0;
}
//Rabin-Karp Algorithm (String Search using Hashing)
#include <iostream>
using namespace std;

#define PRIME 101

long long createHash(string str, int end) {
    long long hash = 0;
    for (int i = 0; i < end; i++)
        hash += str[i] * pow(PRIME, i);
    return hash;
}

long long recalculateHash(string str, int oldIndex, int newIndex, long long oldHash, int patternLen) {
    long long newHash = oldHash - str[oldIndex];
    newHash /= PRIME;
    newHash += str[newIndex] * pow(PRIME, patternLen - 1);
    return newHash;
}

void RabinKarp(string text, string pattern) {
    int n = text.length(), m = pattern.length();
    long long patternHash = createHash(pattern, m);
    long long textHash = createHash(text, m);

    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash && text.substr(i, m) == pattern)
            cout << "Pattern found at index " << i << endl;

        if (i < n - m)
            textHash = recalculateHash(text, i, i + m, textHash, m);
    }
}

int main() {
    string text = "hello world";
    string pattern = "world";
    RabinKarp(text, pattern);
    return 0;
}
