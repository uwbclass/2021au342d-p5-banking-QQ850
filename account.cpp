
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
  stringstream hisFromGivenFund;
  hisFromGivenFund << "W " << idNum << fundType;

  // check if given amount is greater then current balance at current fund
  if (amount > balance[fundType]) {
    int partial = amount - balance[fundType];
    bool evenFundType = (fundType % 2 == 0);

    // one exception, if you are withdrawing from a money market fund with
    // insufficient dollars and it can be covered with dollars from the other
    // money market fund owned by the client account
    // 0 and 1, 2 and 3, 4 and 5, 6 and 7, 8 and 9
    stringstream reportTotalAmount;
    reportTotalAmount << " and total withdraw amount: " << amount;

    stringstream hisFromAssociatedFund;

    if (evenFundType && (partial <= balance[fundType + 1])) {
      // report the history from given fund
      hisFromGivenFund << " " << balance[fundType];
      hisFromAssociatedFund
          << "W " << idNum << fundType + 1 << " "
          << partial; // report the history from associated fund

      // withdraw money from both fund
      balance[fundType] = 0;
      balance[fundType + 1] -= partial;

      // report history
      history[fundType].push_back(
          hisFromGivenFund.str() + " (withdraw partial from " +
          getNameOfFund(fundType + 1) + reportTotalAmount.str() + ")");
      history[fundType + 1].push_back(
          hisFromAssociatedFund.str() + " (withdraw partial for " +
          getNameOfFund(fundType) + reportTotalAmount.str() + ")");

    } else if (!evenFundType && (partial <= balance[fundType - 1])) {
      hisFromGivenFund << " " << balance[fundType];
      hisFromAssociatedFund << "W " << idNum << fundType - 1 << " " << partial;

      // withdraw money from both fund
      balance[fundType] = 0;
      balance[fundType - 1] -= partial;

      // report history
      history[fundType].push_back(
          hisFromGivenFund.str() + " (withdraw partial from " +
          getNameOfFund(fundType - 1) + reportTotalAmount.str() + ")");
      history[fundType - 1].push_back(
          hisFromAssociatedFund.str() + " (withdraw partial for " +
          getNameOfFund(fundType) + reportTotalAmount.str() + ")");

    } else if ((evenFundType && (partial > balance[fundType + 1])) ||
               (!evenFundType && (partial > balance[fundType - 1]))) {
      hisFromGivenFund << " " << amount;
      // report the failed history then return
      history[fundType].push_back(hisFromGivenFund.str() + " (Failed)");
    }

    return;
  }

  // if not then we are able to withdraw
  balance[fundType] -= amount;

  // report the successful history
  hisFromGivenFund << " " << amount;
  history[fundType].push_back(hisFromGivenFund.str());
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
  stringstream hisFromGivenFund;
  hisFromGivenFund << "T " << idNum << typeOfFund1;

  // assuming otherAccount alway exists since we have checked in bank.cpp
  // before calling transfer(...) function
  // check and print errors
  if (balance[typeOfFund1] < amount) {
    // transfer partial from associated fund
    stringstream reportTotalAmount;
    reportTotalAmount << " and total transfer amount: " << amount;

    stringstream hisFromAssociatedFund;

    int partial = amount - balance[typeOfFund1];
    bool evenFundType = (typeOfFund1 % 2 == 0);

    if (evenFundType && (partial <= balance[typeOfFund1 + 1])) {

      hisFromGivenFund << " " << balance[typeOfFund1] << " "
                       << otherAccount->getIDNum()
                       << typeOfFund2; // report the history from given fund
      hisFromAssociatedFund
          << "T " << idNum << typeOfFund1 + 1 << " " << partial << " "
          << otherAccount->getIDNum()
          << typeOfFund2; // report the history from associated fund

      // withdraw money from both fund
      balance[typeOfFund1] = 0;
      balance[typeOfFund1 + 1] -= partial;

      // report history
      history[typeOfFund1].push_back(
          hisFromGivenFund.str() + " (transfer partial from " +
          getNameOfFund(typeOfFund1 + 1) + reportTotalAmount.str() + ")");
      history[typeOfFund1 + 1].push_back(
          hisFromAssociatedFund.str() + " (transfer partial for " +
          getNameOfFund(typeOfFund1) + reportTotalAmount.str() + ")");

      // report history for other account as deposit
      otherAccount->deposit(amount, typeOfFund2);

    } else if (!evenFundType && (partial <= balance[typeOfFund1 - 1])) {
      hisFromGivenFund << " " << balance[typeOfFund1] << " "
                       << otherAccount->getIDNum()
                       << typeOfFund2; // report the history from given fund
      hisFromAssociatedFund
          << "T " << idNum << typeOfFund1 - 1 << " " << partial << " "
          << otherAccount->getIDNum()
          << typeOfFund2; // report the history from associated fund

      // withdraw money from both fund
      balance[typeOfFund1] = 0;
      balance[typeOfFund1 - 1] -= partial;

      // report history
      history[typeOfFund1].push_back(
          hisFromGivenFund.str() + " (transfer partial from " +
          getNameOfFund(typeOfFund1 - 1) + reportTotalAmount.str() + ")");
      history[typeOfFund1 - 1].push_back(
          hisFromAssociatedFund.str() + " (transfer partial for " +
          getNameOfFund(typeOfFund1) + reportTotalAmount.str() + ")");

      // report history for other account as deposit
      otherAccount->deposit(amount, typeOfFund2);

    } else if ((evenFundType && (partial > balance[typeOfFund1 + 1])) ||
               (!evenFundType && (partial > balance[typeOfFund1 - 1]))) {
      // report error
      hisFromGivenFund << " " << amount << " " << otherAccount->getIDNum()
                       << typeOfFund2;
      history[typeOfFund1].push_back(hisFromGivenFund.str() + " (Failed)");
    }

  } else {
    // else extrace amount from fund1 to other account's fund
    balance[typeOfFund1] -= amount;
    hisFromGivenFund << " " << amount << " " << otherAccount->getIDNum()
                     << typeOfFund2;

    // report history for current account
    history[typeOfFund1].push_back(hisFromGivenFund.str());

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
