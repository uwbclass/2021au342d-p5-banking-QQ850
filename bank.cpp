
#include "bank.h"

// TODO(student)
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

// Bank::Bank() {}

void Bank::processTransactionFile(const string &fileName) {
  // declare a file name
  ifstream myFile;

  // open a file
  myFile.open(fileName);

  // check if the file is open
  if (myFile.is_open()) {
    // take out each line and push into queue
    string line;

    // stop loop when it reaches the end
    while (getline(myFile, line)) {
      // add each line to queue
      transactions.push(line);
    }

    // after queue has every information from the file
    // then we can process each line/transaction
    while (!transactions.empty()) {
      // get each line out and pop it out
      string transaction = transactions.front();
      transactions.pop();
      processTransactions(
          transaction); // call this method to process each transaction
    }

    cout << endl;
    accounts.display();
  }

  // when queueis empty then close file
  myFile.close();
}

void Bank::processTransactions(const string &transaction) {
  // using stringstring to get each word/number from a string
  stringstream ss(transaction);
  char typeOfFund;
  ss >> typeOfFund;

  // determine the type and process the transaction differently
  if (typeOfFund == 'O') {
    string firstName, lastName;           // get the last name and first name
    int idNum;                            // get the ID number
    ss >> firstName >> lastName >> idNum; // input the value to the variables
    Account *openAccount = new Account(firstName, lastName, idNum);
    bool exist = accounts.insert(openAccount); // insert the account to the tree

    // if failed insertion then retrun error
    if (!exist) {
      cout << "ERROR: Account " << idNum
           << " is already open. Transaction refused." << endl;
    }
  } else if (typeOfFund == 'T') {
    int idNum1, amount, idNum2;
    ss >> idNum1 >> amount >> idNum2;

    // to separate idNum and fund
    int fund1 = idNum1 % 10;
    idNum1 /= 10;

    int fund2 = idNum2 % 10;
    idNum2 /= 10;

    // check if account exist
    Account *a = nullptr;
    Account *b = nullptr;
    bool aExist = accounts.retrieve(idNum1, a);
    bool bExist = accounts.retrieve(idNum2, b);

    // then transfer money from idNum1's fund1 to idNum2's fund2
    if (aExist && bExist) {
      a->transfer(amount, b, fund1, fund2);
    } else if (!aExist) { // check if account1 exists
      cout << "ERROR: Could not find Account " << idNum1
           << " Transfer cancelled." << endl;
    } else { // check if account2 exists
      cout << "ERROR: Could not find Account " << idNum2
           << " Transfer cancelled." << endl;
    }
  } else if (typeOfFund == 'H') {
    // ex:  H 1001 or H 10010 -> 2 cases
    // get number first
    string num;
    ss >> num;

    // determine the length to see if it contaion a type of fund
    int idNum, fund = -1;
    if (num.length() == 4) {
      idNum = stoi(num); // no fund
    } else {
      fund = stoi(num) % 10;  // get fund
      idNum = stoi(num) / 10; // get idNUm
    }

    // check if account exist
    Account *a = nullptr;
    bool exist = accounts.retrieve(idNum, a);

    // if a is not nullptr then display the history
    if (!exist) {
      cout << "ERROR: Could not find Account " << idNum
           << " Display history cancelled." << endl;
    } else {
      if (num.length() == 4) {
        a->displayHistory();
      } else {
        cout << "Displaying Transaction History for " << a->getFirstName()
             << " " << a->getLastName() << " " << a->getNameOfFund(fund)
             << ": $" << a->getBalance(fund) << endl;
        a->getHistory(fund);
      }
    }
  } else if (typeOfFund == 'D') { // D/W 10010 542
    int num, amount;
    ss >> num >> amount;

    int idNum = num / 10;
    int fund = num % 10;

    Account *a = nullptr;
    bool aExist = accounts.retrieve(idNum, a);
    // cout << "D works" << endl;
    if (aExist) {
      a->deposit(amount, fund);
    } else {
      cout << "ERROR: Could not find Account " << idNum << " Deposit cancelled."
           << endl;
    }
  } else if (typeOfFund == 'W') { // D/W 10010 542
    int num, amount;
    ss >> num >> amount;

    int idNum = num / 10;
    int fund = num % 10;

    Account *a = nullptr;
    bool aExist = accounts.retrieve(idNum, a);

    if (aExist) {
      a->withdraw(amount, fund);
    } else {
      cout << "ERROR: Could not find Account " << idNum
           << " Withdrew cancelled." << endl;
    }
  }
}