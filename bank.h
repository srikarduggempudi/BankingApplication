
#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include <fstream>
#include <string>

using namespace std;

class Bank {
public:
  Bank();
  ~Bank();
  void processTransactions(const string &FileName);
  void processWithdraw(int AccountID, int FundID, int WithdrawAmount);
  void processDeposit(int AccountID, int FundID, int DepositAmount);
  void processHistory(int AccountID, int FundID);
  void processOpening(int AccountID, string FirstName, string LastName);
  void processTransfer(int TransferToAccountID, int TransferToFundID,
                       int TransferAmount, int TransferFromAccountID,
                       int TransferFromFundID);
  void displayAllBankBalances() const;

private:
  AccountTree Accounts;

  void splitAccountID(const int &Number, int &AccountID, int &FundID);
  void displayAccountError(int AccountID, string TransactionType);
};
#endif // ASS5_BANK_H
