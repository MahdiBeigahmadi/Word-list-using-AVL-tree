// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <mahdi beigahmadi>
// St.# : <301570853>
// Email: <mba188@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//

#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// IMPORTANT: no global variables are permitted in this file!
//
// It is okay to define helper functions defined outside the class.

class Wordlist : public Wordlist_base
{

public:
    // Use this Node to implement an AVL tree for the word list. You can *add*
    // extra variables/methods/features to this struct if you like, but you must
    // keep its name the same, and also keep the word, count, left, and right
    // variables as defined.

    struct Node
    {
        string word;
        int count;
        Node *left;
        Node *right;
        int height;

        Node(string value) : word(value), count(1),
                             left(nullptr), right(nullptr),
                             height(1) {}
    };

    Node *root = nullptr;

    // IMPORTANT: root is the only variable that can be defined in this class.
    // It should point to the top node of your AVL tree. When root == nullptr,
    // the tree is empty.
    //
    // No variables other than root are permitted!

    // default Wordlist constructor that creates an empty Wordlist object

    Wordlist() {}

    // "file" constructor that works as described in the assignment

    Wordlist(const string &filename)
    {

        ifstream inputFile(filename);

        if (!inputFile.is_open())
        {
            cout << "Error: Unable to open file '" << filename << "'" << endl;
            return;
        }

        string wordInput;
        while (inputFile >> wordInput)
        {
            add_word(wordInput);
        }

        inputFile.close();
    }
    ~Wordlist()
    {
        clear(root);
    }

    void clear(Node *node) const
    {
        if (node != nullptr)
        {
            clear(node->left);  // Recursively clear left subtree
            clear(node->right); // Recursively clear right subtree
            delete node;        // Delete the current node
        }
    }

    //
    // Returns the number of times w occurs as a word in the word list.
    //

    virtual int get_count(const string &w) const override
    {
        Node *node = searchNode(root, w);
        return node ? node->count : 0;
    }

    //
    // Returns the number of nodes in the word list.
    //

    virtual int num_different_words() const override
    {
        return countDifferentWords(root);
    }

    // Source: ChatGPT

    unsigned int countDifferentWords(Node *node) const
    {
        if (node == nullptr)
        {
            // Base case: If the node is null, return 0
            return 0;
        }

        // Count the current node and recursively count the left and right subtrees
        return 1 + countDifferentWords(node->left) +
               countDifferentWords(node->right);
    }

    // Returns the total number of words in the word list, i.e. the sum of the
    // word counts.

    virtual int total_words() const override
    {
        return countTotalWords(root);
        // Return 0 if the tree is empty
    }
    unsigned int countTotalWords(Node *node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->count + countTotalWords(node->left) +
               countTotalWords(node->right);
    }

    // Returns true if the words in the word list are in ascending sorted order,
    // false otherwise.
    //
    // For an AVL implementation, this should return true if the AVL tree is a
    // BST, and false otherwise.

    virtual bool is_sorted() const override
    {
        string lastWord;
        return checkIfSorted(root, lastWord);
    }
    bool checkIfSorted(Node *node, string &lastWord) const
    {
        if (node == nullptr)
        {
            // Base case: If the node is null, it's the end of a branch
            return true;
        }

        // Traverse the left subtree
        if (!checkIfSorted(node->left, lastWord))
        {
            return false;
        }

        // Check if the current node is greater than the last visited node
        if (!lastWord.empty() && node->word <= lastWord)
        {
            return false;
        }

        // Update the last visited word
        lastWord = node->word;

        // Traverse the right subtree
        return checkIfSorted(node->right, lastWord);
    }

    // Returns a string of the most frequent word in the format "word freq".
    // E.g. if the most frequent word is "the" with count 5437, then "the 5437"
    // is returned.
    //
    // If there is a tie, the first word in the list is returned. For an AVL
    // implementation, this means return the word that occurs first
    // alphabetically.
    //
    // Assumes the list is not empty.

    virtual string most_frequent() const override
    {
        Node *mostFrequent = findMostFrequent(root);
        if (mostFrequent != nullptr)
        {
            return ((mostFrequent->word) +
                    (" ") +
                    to_string(mostFrequent->count));
        }
        return " ";
    }

    // Source: ChatGPT

    Node *findMostFrequent(Node *node) const
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        Node *leftMostFrequent =
            findMostFrequent(node->left);
        Node *rightMostFrequent =
            findMostFrequent(node->right);

        Node *mostFrequent = node;
        if (leftMostFrequent != nullptr &&
            leftMostFrequent->count > mostFrequent->count)
        {
            mostFrequent = leftMostFrequent;
        }
        if (rightMostFrequent != nullptr &&
            rightMostFrequent->count > mostFrequent->count)
        {
            mostFrequent = rightMostFrequent;
        }
        return mostFrequent;
    }

    // Returns the number of nodes with count 1.

    virtual int num_singletons() const override
    {
        return countSingletons(root);
    }

    // Source: ChatGPT

    unsigned int countSingletons(Node *node) const
    {
        if (node == nullptr)
        {
            return 0;
            cout << "The list is empty" << endl;
        }
        if (node->count == 1)
        {
            return 1 + countSingletons(node->left) +
                   countSingletons(node->right);
        }
        return countSingletons(node->left) +
               countSingletons(node->right);
    }

    // Adds w to the word list. If w is already in the word list, then increment
    // its count. Otherwise add a new Node (with count 1) at the alphabetically
    // correct location for the word.

    unsigned int getHeight(Node *nodeHeight)
    {
        if (nodeHeight == nullptr)
        {
            return 0;
        }
        return nodeHeight->height;
    }

    // this function calculates balance factore for AVL using recursion method
    // it subtract the height of left subtree and right subtree
    // the balance factore must be {-1, 0, 1}
    // if the balance factore does not satisfy AVL condition it rotates the nodes by the
    // function you see below like rotateRight and etc.

    int getBalanceFactor(Node *nodeBalance)
    {
        if (nodeBalance == nullptr)
        {
            return 0;
        }
        return getHeight(nodeBalance->left) -
               getHeight(nodeBalance->right);
    }
    void updateHeight(Node *updateNode)
    {
        if (updateNode == nullptr)
        {
            return;
        }
        updateNode->height = 1 + max(getHeight(updateNode->left),
                                     getHeight(updateNode->right));
    }
    // A utility function right
    // rotate subtree rooted with helperNode
    // https://www.geeksforgeeks.org/insertion-in-an-avl-tree/

    Node *rotateRight(Node *helperNode)
    {
        Node *helperNode2 = helperNode->left;
        Node *helperNode3 = helperNode2->right;

        helperNode2->right = helperNode;
        helperNode->left = helperNode3;

        updateHeight(helperNode);
        updateHeight(helperNode2);

        return helperNode2;
    }
    // A utility function right
    // rotate subtree rooted with helperLeft
    // https://www.geeksforgeeks.org/insertion-in-an-avl-tree/

    Node *rotateLeft(Node *helperLeft)
    {
        Node *helperLeft2 = helperLeft->right;
        Node *helperLeft3 = helperLeft2->left;

        helperLeft2->left = helperLeft;
        helperLeft->right = helperLeft3;

        updateHeight(helperLeft);
        updateHeight(helperLeft2);

        return helperLeft2;
    }
    // a pointer function that adds a new node to AVL,
    // helping source:
    // https://www.geeksforgeeks.org/insertion-in-an-avl-tree/

    Node *insert(Node *node, const string &element)
    {
        if (node == nullptr)
        {
            return new Node(element);
        }

        if (element < node->word)
        {
            node->left = insert(node->left, element);
        }
        else if (element > node->word)
        {
            node->right = insert(node->right, element);
        }
        else
        {
            // Word already exists, increment its count
            node->count++;
        }

        // Update the height of the current node
        updateHeight(node);

        // Check the balance factor and perform rotations if needed
        int balance = getBalanceFactor(node);

        // Left Heavy
        if (balance > 1)
        {
            if (element < node->left->word)
            {
                return rotateRight(node);
            }
            else
            {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        // Right Heavy
        if (balance < -1)
        {
            if (element > node->right->word)
            {
                return rotateLeft(node);
            }
            else
            {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    // Source : https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
    // a function that searches AVL using recursion, it has two inputs
    // the first one is the node and second one is target element

    Node *searchNode(Node *node, const string &w) const
    {
        // Base Cases: root is null or word is present at root
        if (node == nullptr || node->word == w)
            return node;

        // Word is greater than root's word
        if (node->word < w)
            return searchNode(node->right, w);

        // Word is smaller than root's word
        else
        {
            return searchNode(node->left, w);
        }
    }

    // this function adds words into AVL list, it uses wrapper method and gets
    // help from another utility function
    // Source : https://www.geeksforgeeks.org/insertion-in-an-avl-tree/

    void add_word(const string &w) override
    {
        root = insert(root, w);
    }

    // this function generates the desired ouput with number of count
    // it uses inorder traversal, it traverses the AVL and increment the
    // rank of each word that occurs
    // source: basically everywhere we can find this recursion func

    void inOrderTraversalPrint(Node *node, unsigned int &rank) const
    {
        // inorder traversal of AVL/BST, is an amazing feature that
        // this type of Data Structure contains. According to this feature
        // if we travers a BST inorder format we will get the data sorted

        if (node != nullptr)
        {
            inOrderTraversalPrint(node->left, rank);
            cout << rank << ". {\"" << node->word
                 << "\", " << node->count << "}" << endl;
            rank++;
            inOrderTraversalPrint(node->right, rank);
        }
    }

    virtual void print_words() const override
    {
        unsigned int rank = 1;
        inOrderTraversalPrint(root, rank);
    }
};