
#include "bstree.h"
#include <string>
#include <stack>

// TODO(student)

using namespace std;

BSTree& BSTree::operator = (const BSTree &other) {
  *this = other;
  return *this;
}

// Create BST
BSTree::BSTree() {
  //allocate memory 
  root = new Node();
  root = nullptr;
}

BSTree::BSTree(const BSTree &other) {
  *this = other;
}

// Delete all nodes in BST
BSTree::~BSTree() { clear();}


// Insert new account
bool BSTree::insert(Account *other) {  
  //create a new Node 
  Node* newNode = new Node(other);
 
  // Pointer pre maintains the trailing
  Node* pre = nullptr;

  //add front
  if (isEmpty()) {
    root = newNode;
    root->account = other;
    return true; 
  }
  
  Account *test;
  if (retrieve(other->getIDNum(), test)) {

    cout <<"retrive false "  << other->getIDNum() << endl;
    return false;
  }

  //add middle, if the same account then override. 
  Node *curr = root; 
  
  while (curr != nullptr) {
    pre = curr;
    //if the current account is greater than the given one then go left else go right 
    if (curr->account == other) {
      cout <<"retrive false "  << other->getIDNum() << endl;
      return false;
    }
    curr = curr->account > other ? curr->left : curr->right;  
  }
  
   if (pre->account > other) {//else determine add to the left side or right side 
    pre->left = newNode; // inseart a new node 
    pre->left->account = other;
  } else {
    pre->right = newNode;
    pre->right->account = other;
  }
  return true;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool BSTree::retrieve(const int &accountNumber, Account *&other) const {
  // if (isEmpty()) {
  //   return false;
  // }  
  
  //traverse the whole tree to find the accountNumber
  Node *curr = root;
  //bool result = false;
  while (curr != nullptr) {
    if (curr->account->getIDNum() == accountNumber) {
      cout << "exist? in retrive?????? " << curr->account->getIDNum() << " and " <<accountNumber << endl;
      other = curr->account;
      cout << "after other: " << other->getIDNum() << " and " <<accountNumber << endl;
      return true;
    }
    curr = curr->account->getIDNum() > accountNumber ? curr->left : curr->right;  
  }
  return false;
}

// Display information on all accounts
void BSTree::display()  {
  //traverse the whole tree and print out each account's balance for each fund
  //in-order sequence
  cout << "Processing Done. Final Balances." << endl;
  displayHelper(root);
  cout << endl;
  cout << endl;
  cout << "Process finished with exit code 0" << endl;
}


//Cash Johnny Account ID: 1001
        // Money Market: $470
        // Prime Money Market: $3042
        // Long-Term Bond: $10442
        // Short-Term Bond: $14540
        // 500 Index Fund: $0
        // Capital Value Fund: $54
        // Growth Equity Fund: $15053
        // Growth Index Fund: $10931
        // Value Fund: $0
        // Value Stock Index: $0
void BSTree::displayHelper(Node *node) {
  if (node == nullptr) {
    return;
  } else {
   //go to very left 
    displayHelper(node->left);
  
    //print out account
    cout << *(node->account) << endl;

    //go to right
    displayHelper(node->right);
  }
}

// delete all information in AccountTree
void BSTree::clear() {
  helper(root);
}

//help clear() to delete each node
void BSTree::helper(Node *node) {
  if (node == nullptr) {
    return;
  } else {
    //traverse left and right to th end 
    helper(node->left);
    helper (node->right);
    //delete current node
    delete node;
    node = nullptr;
  }  
}



// check if tree is empty
bool BSTree::isEmpty() const { return root == nullptr; }
