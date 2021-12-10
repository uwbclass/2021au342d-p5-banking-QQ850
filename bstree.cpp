
#include "bstree.h"
#include <stack>
#include <string>

// TODO(student)

using namespace std;

// Create BST
BSTree::BSTree() : root{nullptr} {}

// Delete all nodes in BST
BSTree::~BSTree() { clear(); }

// Insert new account
bool BSTree::insert(Account *other) {
  if (isEmpty()) {
    root = new Node();
    root->account = other;
    root->left = nullptr;
    root->right = nullptr;
    return true;
  }

  Node *curr = root;
  Node *pre = root;

  while (curr != nullptr && curr->account->getIDNum() != other->getIDNum()) {
    pre = curr;
    curr = curr->account->getIDNum() > other->getIDNum() ? curr->left
                                                         : curr->right;
  }

  if (curr != nullptr && curr->account->getIDNum() == other->getIDNum()) {
    return false;
  }

  if (pre->account->getIDNum() > other->getIDNum()) {
    pre->left = new Node();
    pre->left->account = other;
    pre->left->left = nullptr;
    pre->left->right = nullptr;
  } else {
    pre->right = new Node();
    pre->right->account = other;
    pre->right->left = nullptr;
    pre->right->right = nullptr;
  }
  return true;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool BSTree::retrieve(const int &accountNumber, Account *&other) const {
  // traverse the whole tree to find the accountNumber
  Node *curr = root;
  while (curr != nullptr) {
    if (curr != nullptr && curr->account->getIDNum() == accountNumber) {
      other = curr->account;
      return true;
    }
    curr = curr->account->getIDNum() > accountNumber ? curr->left : curr->right;
  }
  other = nullptr;
  return false;
}

// Display information on all accounts
void BSTree::display() {
  // traverse the whole tree and print out each account's balance for each fund
  // in-order sequence
  cout << "Processing Done. Final Balances." << endl;
  displayHelper(root);
  cout << endl;
  cout << endl;
  cout << "Process finished with exit code 0" << endl;
}

void BSTree::displayHelper(Node *node) {
  if (node == nullptr) {
    return;
  }
  // go to very left
  displayHelper(node->left);

  // print out account
  cout << *(node->account) << endl;

  // go to right
  displayHelper(node->right);
}

// delete all information in AccountTree
void BSTree::clear() { helper(root); }

// help clear() to delete each node
void BSTree::helper(Node *node) {
  if (node == nullptr) {
    return;
  }
  // traverse left and right to th end
  helper(node->left);
  helper(node->right);
  delete node->account;
  delete node;
  node = nullptr;
}

// check if tree is empty
bool BSTree::isEmpty() const { return root == nullptr; }
