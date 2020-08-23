//
// Created by Srikar Duggempudi on 12/2/2019.
//

#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include <string>
#include "fund.h"
using namespace std;

class Account {

  friend ostream &operator<<(ostream &Out, const Account &Account);

public:
  Account();
  ~Account();
  int getAccountID();
  string getFirstName();
  string getLastName();
  void setAccountID(int AccountID);
  void setFirstName(string FirstName);
  void setLastName(string LastName);
  int getBalance() const;
  int processWithdraw(int FundID, int AmountWithdrawn);
  int processDeposit(int FundID, int AmountDeposited);
  int processTransfer(int FundID, int TransferToAccountID, int TransferToFundID,
                      int TransferAmount);
  void processHistory(int FundID);
  void display();

  static const int MAX_ITEMS = 10;
  static const string FundNames[MAX_ITEMS];

private:
  string FirstName;
  string LastName;
  int AccountID;
  Fund Funds[MAX_ITEMS];

  int specialProcessWithdraw(int FundID1, int FundID2, int AmountWithdrawn);
};

#endif // ASS5_ACCOUNT_H
