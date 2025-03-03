#include <iostream>
#include <queue>
#include <unordered_map>
#include <chrono>

using namespace std;

// This is our Node structure
struct Node {
    char ch;
    int freq;
    Node *left, *right;
};
// This function creates a new node with given parameters
Node* getNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}
// This is a comparison function to order the heap
struct comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};
// This function encodes the characters in the tree and stores them in huffmanCode
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode) {
    if (root == nullptr)
        return;
    // If this is a leaf node, it's a character in our string
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }
    // Recursive calls for left and right children of this node
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}
// This function decodes the encoded string
void decode(Node* root, int &index, string str) {
    if (root == nullptr) {
        return;
    }
    // Found a leaf node
    if (!root->left && !root->right) {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}

void buildHuffmanTree(string text) {
    // Count frequency of appearance of each character
    // and store it in freq
    unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }
    // Create a priority queue to store live nodes of Huffman tree
    priority_queue<Node*, vector<Node*>, comp> pq;

    // Create a new node for each unique character and
    // add it to the priority queue.
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // do till there is more than one node in the queue
    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        // Create a new internal node with these two nodesas children and with frequency equal to the sum
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

        // The remaining node is the root node and the Huffman tree is complete.
Node* root = pq.top();

    // Traverse the Huffman tree and store the Huffman codes in a map
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes are:\n" << '\n';
    for (auto pair: huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }

    cout << "\nOriginal string was:\n" << text << '\n';

    // Print encoded string
    string str = "";
    for (char ch: text) {
        str += huffmanCode[ch];
    }

    cout << "\nEncoded string is:\n" << str << '\n';

    // Decode the encoded string
    int index = -1;
    cout << "\nDecoded string is: ";
    while (index < (int)str.size() - 2) {
        decode(root, index, str);
    }
}

int main() {
    string text = "Huffman coding algorithm";
         auto start = std::chrono::high_resolution_clock::now();

    buildHuffmanTree(text);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << std::endl;
    return 0;
}