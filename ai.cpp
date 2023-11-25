#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct TreeNode {
    string word;
    int frequency;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string w) : word(w), frequency(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    TreeNode* root;

    // Helper function to insert a word into the AVL tree
    TreeNode* insert(TreeNode* node, string word) {
        if (node == nullptr) {
            return new TreeNode(word);
        }
        if (word < node->word) {
            node->left = insert(node->left, word);
        }
        else if (word > node->word) {
            node->right = insert(node->right, word);
        }
        else {
            node->frequency++;
        }
        // Update height and balance factor
        updateHeightAndBalance(node);
        // Perform balancing if necessary
        return balance(node);
    }

    // Helper function to update the height and balance factor of a node
    void updateHeightAndBalance(TreeNode* node) {
        int leftHeight = (node->left != nullptr) ? node->left->height : 0;
        int rightHeight = (node->right != nullptr) ? node->right->height : 0;
        node->height = 1 + max(leftHeight, rightHeight);
        node->balance = leftHeight - rightHeight;
    }

    // Helper function to perform AVL tree balancing
    TreeNode* balance(TreeNode* node) {
        if (node->balance > 1) {
            if (node->left->balance >= 0) {
                return rotateRight(node);
            }
            else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        else if (node->balance < -1) {
            if (node->right->balance <= 0) {
                return rotateLeft(node);
            }
            else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        return node;
    }

    // Helper function to perform a right rotation
    TreeNode* rotateRight(TreeNode* node) {
        TreeNode* newRoot = node->left;
        TreeNode* temp = newRoot->right;
        newRoot->right = node;
        node->left = temp;
        updateHeightAndBalance(node);
        updateHeightAndBalance(newRoot);
        return newRoot;
    }

    // Helper function to perform a left rotation
    TreeNode* rotateLeft(TreeNode* node) {
        TreeNode* newRoot = node->right;
        TreeNode* temp = newRoot->left;
        newRoot->left = node;
        node->right = temp;
        updateHeightAndBalance(node);
        updateHeightAndBalance(newRoot);
        return newRoot;
    }

public:
    AVLTree() : root(nullptr) {}

    // Public function to insert a word into the AVL tree
    void insert(string word) {
        root = insert(root, word);
    }

    // Public function to get the number of different words in the AVL tree
    int getNumberOfDifferentWords() {
        return countNodes(root);
    }

    // Public function to get the total number of words in the AVL tree
    int getTotalNumberOfWords() {
        return countWords(root);
    }

    // Public function to find the most frequent word in the AVL tree
    string findMostFrequentWord() {
        TreeNode* mostFrequent = findMostFrequent(root);
        if (mostFrequent != nullptr) {
            return mostFrequent->word;
        }
        return "";
    }

    // Public function to get the number of singleton words in the AVL tree
    int getNumberOfSingletons() {
        int singletons = countSingletons(root);
        return singletons;
    }

    // Public function to print the AVL tree in-order
    void printInOrder() {
        printInOrder(root);
    }

private:
    // Helper function to count the number of nodes in the AVL tree
    int countNodes(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    // Helper function to count the total number of words in the AVL tree
    int countWords(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->frequency + countWords(node->left) + countWords(node->right);
    }

    // Helper function to find the node with the highest frequency in the AVL tree
    TreeNode* findMostFrequent(TreeNode* node) {
        if (node == nullptr) {
            return nullptr;
        }
        TreeNode* leftMostFrequent = findMostFrequent(node->left);
        TreeNode* rightMostFrequent = findMostFrequent(node->right);

        TreeNode* mostFrequent = node;
        if (leftMostFrequent != nullptr && leftMostFrequent->frequency > mostFrequent->frequency) {
            mostFrequent = leftMostFrequent;
        }
        if (rightMostFrequent != nullptr && rightMostFrequent->frequency > mostFrequent->frequency) {
            mostFrequent = rightMostFrequent;
        }
        return mostFrequent;
    }

    // Helper function to count the number of singleton words in the AVL tree
    int countSingletons(TreeNode* node) {
         if (node == nullptr) {
            return 0;
            cout <<"The list is empty" << endl;
        }
        if (node->frequency == 1) {
            return 1 + countSingletons(node->left) + countSingletons(node->right);
        }
        return countSingletons(node->left) + countSingletons(node->right);
    }

    // Helper function to print the AVL tree in-order
    void printInOrder(TreeNode* node) {
        if (node != nullptr) {
            printInOrder(node->left);
            cout << node->word << " " << node->frequency << endl;
            printInOrder(node->right);
        }
    }
};

int main() {
    AVLTree avlTree;
    ifstream inputFile("input.txt");

    if (!inputFile) {
        cerr << "Error: Could not open the input file." << endl;
        return 1;
    }

    string word;
    while (inputFile >> word) {
        // Remove punctuation and convert to lowercase
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        avlTree.insert(word);
    }

    inputFile.close();

    int differentWords = avlTree.getNumberOfDifferentWords();
    int totalWords = avlTree.getTotalNumberOfWords();
    string mostFrequentWord = avlTree.findMostFrequentWord();
    int singletons = avlTree.getNumberOfSingletons();

    cout << "Number of different words: " << differentWords << endl;
    cout << "Total number of words: " << totalWords << endl;
    cout << "Most frequent word: " << mostFrequentWord << " " << avlTree.findMostFrequent(mostFrequentWord) << endl;
    cout << "Number of singletons: " << singletons << " (" << (static_cast<double>(singletons) / differentWords * 100) << "%)" << endl;

    return 0;
}
