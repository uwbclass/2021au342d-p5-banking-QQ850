
#ifndef BSTREE_H
#define BSTREE_H

#include "account.h"
#include <iostream>

class BSTree {
public:
  // Create BST
  BSTree();

  // Delete all nodes in BST
  ~BSTree();

  // Insert new account
  bool insert(Account *account);

  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int &accountNumber, Account *&account) const;

  // Display information on all accounts
  void display() const;

  // delete all information in AccountTree
  void clear();

  // check if tree is empty
  bool isEmpty() const;

private:
  struct Node {
    Account *account;
    Node *right;
    Node *left;
  };
  Node *root;
};
#endif // BSTREE_H
