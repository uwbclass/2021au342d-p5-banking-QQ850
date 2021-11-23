
#ifndef BANK_H
#define BANK_H

#include "bstree.h"
#include <string>

using namespace std;

class Bank {
public:
  void processTransactionFile(const string &fileName);

private:
  BSTree accounts;
};
#endif // BANK_H
