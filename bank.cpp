//
// Created by Srikar Duggempudi on 12/2/2019.
//

#include "bank.h"
#include <deque>
#include <fstream>
#include <list>
#include <queue>
#include <sstream>
#include <string>

Bank::Bank() = default;

Bank::~Bank() = default;

// Processes the transactions
void Bank::processTransactions(const string &FileName) {
  ifstream InFile(FileName);

  string Line;
  queue<string> Transactions;

  // Read transactions into a queue
  while (getline(InFile, Line)) {
    Transactions.push(Line);
    // cout << line << endl;
  }

  // Empty out queue and parse each line
  while (!Transactions.empty()) {
    Line = Transactions.front();
    stringstream SSin(Line);
    string Token;
    while (SSin.good()) {
      SSin >> Token;
      // cout << Token << " :: ";
      if (Token == "O") {
        string LastName;
        string FirstName;
        int AccountID;
        SSin >> LastName >> FirstName >> AccountID;
        // cout << "Opening account for Last Name: " << LastName
        //   << " First Name: " << FirstName << " Account ID: " << AccountID
        // << endl;
        processOpening(AccountID, FirstName, LastName);
      } else if (Token == "D") {
        int AccountID;
        int FundID;
        int DepositedAmount;
        int AccountFundID;
        SSin >> AccountFundID >> DepositedAmount;
        splitAccountID(AccountFundID, AccountID, FundID);
        // cout << "AccountID: " << AccountID << " FundID: " << FundID
        //    << " Deposited Amount: " << DepositedAmount << endl;
        processDeposit(AccountID, FundID, DepositedAmount);
      } else if (Token == "W") {
        int AccountID;
        int FundID;
        int WithdrawnAmount;
        int AccountFundID;
        SSin >> AccountFundID >> WithdrawnAmount;
        splitAccountID(AccountFundID, AccountID, FundID);
        // cout << "AccountID: " << AccountID << " FundID: " << FundID
        //    << " Withdrawn Amount: " << WithdrawnAmount << endl;
        processWithdraw(AccountID, FundID, WithdrawnAmount);
      } else if (Token == "T") {
        int TransferFromAccountID;
        int TransferFromFundID;
        int TransferFromAccountFundID;
        int TransferAmount;
        int TransferToAccountID;
        int TransferToFundID;
        int TransferToAccountFundID;
        SSin >> TransferFromAccountFundID >> TransferAmount >>
            TransferToAccountFundID;
        splitAccountID(TransferFromAccountFundID, TransferFromAccountID,
                       TransferFromFundID);
        splitAccountID(TransferToAccountFundID, TransferToAccountID,
                       TransferToFundID);
        // cout << "Transfer From Account ID: " << TransferFromAccountID
        //    << " From Fund ID: " << TransferFromFundID
        //  << " Amount: " << TransferAmount
        //<< " To Account ID: " << TransferToAccountID
        //<< " To Fund ID: " << TransferToFundID << endl;
        processTransfer(TransferToAccountID, TransferToFundID, TransferAmount,
                        TransferFromAccountID, TransferFromFundID);
      } else if (Token == "H") {
        int AccountID;
        int FundID = -1;
        int AccountFundID;
        SSin >> AccountFundID;
        if (AccountFundID < 10000) {
          AccountID = AccountFundID;
        } else {
          splitAccountID(AccountFundID, AccountID, FundID);
        }
        // cout << "History Account ID: " << AccountID
        //    << " History Fund ID: " << FundID << endl;
        processHistory(AccountID, FundID);
      }
    }
    Transactions.pop();
  }
}

// Splits the combined ID into Account ID and Fund ID
void Bank::splitAccountID(const int &Number, int &AccountID, int &FundID) {
  AccountID = Number / 10;
  FundID = Number % 10;
}

// Processes withdraw
void Bank::processWithdraw(int AccountID, int FundID, int WithdrawAmount) {
  Account *Acc;
  if (Accounts.retrieve(AccountID, Acc)) {
    Acc->processWithdraw(FundID, WithdrawAmount);
  } else {
    displayAccountError(AccountID, "Withdraw");
  }
}

// Processes deposit
void Bank::processDeposit(int AccountID, int FundID, int DepositAmount) {
  Account *Acc;
  if (Accounts.retrieve(AccountID, Acc)) {
    Acc->processDeposit(FundID, DepositAmount);
  } else {
    displayAccountError(AccountID, "Deposit");
  }
}

// Processes history
void Bank::processHistory(int AccountID, int FundID) {
  Account *Acc;
  Fund Fund;
  if (Accounts.retrieve(AccountID, Acc)) {
    Acc->processHistory(FundID);
  } else {
    displayAccountError(AccountID, "History");
  }
}

// Processes opening account
void Bank::processOpening(int AccountID, string FirstName, string LastName) {
  if (AccountID < 1000 || AccountID > 9999) {
    cout << "ERROR : Account " << AccountID
         << " is not valid. AccountID should be a 4-digit number. Opening "
            "transaction refused."
         << endl;
  } else {
    auto *Acc = new Account();
    Acc->setAccountID(AccountID);
    Acc->setFirstName(FirstName);
    Acc->setLastName(LastName);
    if (!Accounts.insert(Acc)) {
      cout << "ERROR : Account " << AccountID
           << " is already open. Transaction refused." << endl;
      delete Acc;
    }
  }
}

// Processes transfer
void Bank::processTransfer(int TransferToAccountID, int TransferToFundID,
                           int TransferAmount, int TransferFromAccountID,
                           int TransferFromFundID) {
  Account *FromAcc;
  Account *ToAcc;

  if (!Accounts.retrieve(TransferFromAccountID, FromAcc)) {
    displayAccountError(TransferFromAccountID, "Transfer");
    return;
  }
  if (!Accounts.retrieve(TransferToAccountID, ToAcc)) {
    displayAccountError(TransferToAccountID, "Transfer");
    return;
  }

  FromAcc->processTransfer(TransferFromFundID, TransferToAccountID,
                           TransferToFundID, TransferAmount);
  ToAcc->processDeposit(TransferToFundID, TransferAmount);
}

// Displays all the Accounts with their balances
void Bank::displayAllBankBalances() const { Accounts.display(); }

// Displays the error message
void Bank::displayAccountError(int AccountID, string TransactionType) {
  if (AccountID < 1000 || AccountID > 9999) {
    cout << "ERROR : Account " << AccountID
         << " is not valid. AccountID should be a 4-digit number. "
         << TransactionType << " transaction refused." << endl;
  } else {
    cout << "ERROR : Account " << AccountID << " is not found. "
         << TransactionType << " transaction refused." << endl;
  }
}
