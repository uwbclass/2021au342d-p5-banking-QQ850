
#ifndef BANK_H
#define BANK_H

#include "bstree.h"
#include "account.h"
#include <string>
#include <queue>

using namespace std;

class Bank {
public:
  Bank(); //constractor 
  //~Bank(); //destractor 
  void processTransactionFile(const string &fileName);
  void processTransactions(string transaction);

private:
  BSTree accounts;
  queue<string> transactions;
  Account *openAccount; 
};
#endif // BANK_H
