
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// enum TYPE {
//   MONEY_MARKET,
//   PRIME_MONEY_BOND,
//   LONG_TERM_BOND,
//   SHORT_TERM_BOND,
//   F_INDEX_FUND,
//   CAPITAL_VALUE_FUND,
//   GROWTH_EQUITY_FUND, 
//   GROWTY_INDEX_FUND,
//   VALUE_FUND,
//   VALUE_STOCK_INDEX
// };

class Account {
  //print out a series of history  
  friend ostream &operator << (ostream &out, const Account &other);
public:
 
 //constractor 
 Account(string firstName, string lastName, int idNum);

 //operator to compare each account object by ID Number
 bool operator < (const Account &other) const;
 bool operator > (const Account &other) const; 
 bool operator == (const Account &other) const;
 bool operator != (const Account &other) const;
 
//  //compare Account with int num
//  bool operator == (const int &num) const;
//  bool operator > (const int &num) const; 

 Account& operator = (const Account &other);


 //there are five types of transactions 
 void deposit(int amount, int fundType); // deposite any amount into a certain fund  
 void withdraw(int amount, int fundType); // withdraw money which must be less than and equal to current balance in the current fund, else return error 
 void displayHistory(); // Display the history of all transactions for a client account or for a single fund.
 void transfer(int amount, Account *otherAccount, int typeOfFund1, int typeOfFund2);
 bool openFunds(int fundType); // check if we open a client account with the appropriate funds 
 string getFirstName(); // get name 
 string getLastName();
 int getIDNum(); //return client's ID num
 int getBalance(int typeOfFund); // get balance from each fund
 string getNameOfFund (int typeOfFund); // get the name of each fund 



private:
  string firstName;
  string lastName;
  int idNum; //a client's account number 
  int balance[10]; // an array of funds' balance, initial value is 0 
  vector<string> history[10]; // it is used to report the history for each fund 
  //create a const string to get the name of each fund 
  const string fund[10] = {
    "Money Market",
    "Prime Money Market",
    "Long-Term Bond",
    "Short-Term Bond",
    "500 Index Fund",
    "Capital Value Fund",
    "Growth Equity Fund",
    "Growth Index Fund",
    "Value Fund",
    "Value Stock Index"
  }; 
};
#endif // ACCOUNT_H
