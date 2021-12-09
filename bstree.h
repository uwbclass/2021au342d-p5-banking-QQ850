
#ifndef BSTREE_H
#define BSTREE_H

#include "account.h"
#include <iostream>

typedef struct Node {
    Account *account;
    Node *right;
    Node *left;
  }
  Node;

class BSTree {
public:
  // Create BST
  BSTree();

  // Delete all nodes in BST
  ~BSTree();
  
  // Insert new account
  bool insert(Account *other);

 // bool insertHelper(Node *&root, Account *other);

  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int &accountNumber, Account *&other) const;
  
  // Display information on all accounts
  void display();
  
  //a helper to help display function with recursion 
  void displayHelper(Node *node);

  // delete all information in AccountTree
  void clear();
 
  //help clear() to delete each node
  void helper(Node *node);

  // check if tree is empty
  bool isEmpty() const;

private:
  Node *root;
};
#endif // BSTREE_H
