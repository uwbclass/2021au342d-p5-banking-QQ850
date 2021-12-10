
#ifndef BANK_H
#define BANK_H

#include "account.h"
#include "bstree.h"
#include <queue>
#include <string>

using namespace std;

class Bank {
public:
  // Bank(defaualt); // constractor
  void processTransactionFile(const string &fileName);
  void processTransactions(const string &transaction);

private:
  BSTree accounts;
  queue<string> transactions;
};
#endif // BANK_H
