#include <iostream>
#include <vector>
#include <chrono>

// BTree node
class BTreeNode {
    int *keys;  // An array of keys
    int t;      //  range for number of keys
    BTreeNode **C; // the array for child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
public:
    BTreeNode(int _t, bool _leaf);

    BTreeNode *search(int k);  // returns nullptr if k is not present.

    // For insertion
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode *y);

// Make BTree friend of this so that we can access private members of this class in BTree functions
friend class BTree;
};

// A BTree
class BTree {
    BTreeNode *root; // Pointer to root node
    int t;  // Minimum 
public:
    // Constructor making tree empty
    BTree(int _t) {  root = nullptr;  t = _t; }

    // function to search a key in this tree
    BTreeNode* search(int k) {  return (root == nullptr)? nullptr : root->search(k); }

    // The main function that inserts a new key in this B-Tree
    void insert(int k);
};

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];
    n = 0;
}

// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;
    if (keys[i] == k)
        return this;

    if (leaf == true)
        return nullptr;

    // Go to the appropriate child
    return C[i]->search(k);
}

// A utility function to insert a new key in this node
void BTreeNode::insertNonFull(int k) {
    int i = n-1;

    if (leaf == true) {
        // The following loop does two things:
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k) {
            keys[i+1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i+1] = k;
        n = n+1;
    } else { // If this node is not leaf find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;

        // See if the found child is full
        if (C[i+1]->n == 2*t-1) {
            // Split it if full
            splitChild(i+1, C[i+1]);

            // After split, the key at i where the child got split goes up and C[i] is splitted into two
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

// A function to split the child y 
void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];

    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }

    y->n = t - 1;

    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];

    C[i+1] = z;

    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];

    keys[i] = y->keys[t-1];
    n = n + 1;
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(int k) {
    // If tree is empty
    if (root == nullptr) {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0] = k;  
        root->n = 1;  // Update number of keys 

    } else { 

        if (root->n == 2*t-1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            // Change root
            root = s;
        } else { 
            root->insertNonFull(k);
        }
    }
}

int main() {
 auto start = std::chrono::high_resolution_clock::now();
    BTree t(3);


    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(1);
    t.insert(6);
    t.insert(11);
    t.insert(20);

    int k = 6;
    (t.search(k) != nullptr)? std::cout << "Key " << k << " is present.\n" : std::cout << "Key " << k << " is not present.\n";

    k = 25;
    (t.search(k) != nullptr)? std::cout << "Key " << k << " is present.\n" : std::cout << "Key " << k << " is not present.\n";
    auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << std::endl;

    return 0;
}