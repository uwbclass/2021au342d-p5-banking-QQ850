
// TODO(student)
#include "account.h"
#include <sstream>
#include <string>

using namespace std;

ostream &operator<<(ostream &out, const Account &other) {
  out << other.firstName << " " << other.lastName
      << " Account ID: " << other.idNum << endl;
  for (int i = 0; i < 10; i++) {
    out << "\t" << other.fund[i] << ": " << other.balance[i] << endl;
  }
  return out;
}

// constructor
Account::Account(string firstName, string lastName, int idNum)
    : firstName(firstName), lastName(lastName), idNum(idNum) {
  // initial balance is 0
  for (int &i : balance) {
    i = 0;
  }
}

// deposite any amount into a certain fund
void Account::deposit(int amount, int fundType) {
  // add amount to the balance at current fund
  balance[fundType] += amount;

  // report the history
  stringstream his;
  his << "D " << idNum << fundType << " " << amount;
  history[fundType].push_back(his.str());
}

// withdraw money which must be less than and equal to current balance in the
// current fund, else return error
void Account::withdraw(int amount, int fundType) {
  stringstream his;
  his << "W " << idNum << fundType << " " << amount;

  // check if given amount is greater then current balance at current fund
  if (amount > balance[fundType]) {
    // report the failed history then return
    history[fundType].push_back(his.str() + " (Failed)");
    // print out error
    // cerr << "ERROR: Not enough balance in current fund" << fund[fundType] <<
    // endl;
    return;
  }

  // if not then we are able to withdraw
  balance[fundType] -= amount;

  // report the successful history
  history[fundType].push_back(his.str());
}

// Display the history of all transactions for a client account or for a single
// fund.
void Account::displayHistory() {
  // print the name of the client
  cout << "Displaying Transaction History for " << firstName << " " << lastName
       << " by fund" << endl;
  // print each transaction history by using for loop
  for (int i = 0; i < 10; i++) {
    cout << fund[i] << ": $" << balance[i] << endl;
    getHistory(i);
  }
}

// transfer money from exist account to another exist account
// also check it has enough amount in the fund to be able to transfer
void Account::transfer(int amount, Account *otherAccount, int typeOfFund1,
                       int typeOfFund2) {
  stringstream his;
  his << "T " << idNum << typeOfFund1 << " " << amount
      << otherAccount->getIDNum() << typeOfFund2;

  // assuming otherAccount alway exists since we have checked in bank.cpp
  // before calling transfer(...) function
  // check and print put errors
  if (balance[typeOfFund1] < amount) {
    // report error
    history[typeOfFund1].push_back(his.str() + " (Failed)");
  } else {
    // else extrace amount from fund1 to other account's fund
    balance[typeOfFund1] -= amount;

    // report history for current account
    history[typeOfFund1].push_back(his.str());

    // report history for other account as deposit
    otherAccount->deposit(amount, typeOfFund2);
  }
}

// get the name
string Account::getFirstName() { return this->firstName; }

string Account::getLastName() { return this->lastName; }

// get id number
int Account::getIDNum() { return this->idNum; }

// get balance from each fund
int Account::getBalance(int typeOfFund) { return this->balance[typeOfFund]; }

// get teh name of each fund
string Account::getNameOfFund(int typeOfFund) { return fund[typeOfFund]; }

// get history for each fund
void Account::getHistory(int typeOfFund) {
  for (const auto &j : history[typeOfFund]) {
    cout << "\t" << j << endl;
  }
}
