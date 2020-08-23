//
// Created by Srikar Duggempudi on 12/2/2019.
//

#include "account.h"

#include <iostream>
#include <string>
using namespace std;

// Array which stores the names of all the funds
const string Account::FundNames[Account::MAX_ITEMS] = {
    "Money Market",       "Prime Money Market", "Long-Term Bond",
    "Short-Term Bond",    "500 Index Fund",     "Capital Value Fund",
    "Growth Equity Fund", "Growth Index Fund",  "Value Fund",
    "Value Stock Index"};

Account::Account() : FirstName{""}, LastName{""}, AccountID{0} {
  for (int I = 0; I < MAX_ITEMS; ++I) {
    Funds[I].setName(FundNames[I]);
    Funds[I].setFundID(I);
  }
}

Account::~Account() = default;

ostream &operator<<(ostream &Out, const Account &Account) {
  Out << "Account: " << Account.AccountID << endl;
  Out << "Name: " << Account.FirstName << " " << Account.LastName << endl;

  return Out;
}

// Returns Account ID
int Account::getAccountID() { return AccountID; }

// Returns First Name
string Account::getFirstName() { return FirstName; }

// Returns Last Name
string Account::getLastName() { return LastName; }

// Returns Balance
int Account::getBalance() const {
  int Balance = 0;
  for (int I = 0; I < MAX_ITEMS; ++I) {
    Balance += Funds[I].getAmount();
  }
  return Balance;
}

// Sets Account ID
void Account::setAccountID(int AccountID) {
  this->AccountID = AccountID;
  for (int I = 0; I < MAX_ITEMS; ++I) {
    Funds[I].setAccountID(AccountID);
  }
}

// Sets First Name
void Account::setFirstName(string FirstName) { this->FirstName = FirstName; }

// Sets Last Name
void Account::setLastName(string LastName) { this->LastName = LastName; }

// Processes withdraw
int Account::processWithdraw(int FundID, int AmountWithdrawn) {
  if (FundID == 0) {
    return specialProcessWithdraw(0, 1, AmountWithdrawn);
  }

  if (FundID == 1) {
    return specialProcessWithdraw(1, 0, AmountWithdrawn);
  }

  if (FundID == 2) {
    return specialProcessWithdraw(2, 3, AmountWithdrawn);
  }

  if (FundID == 3) {
    return specialProcessWithdraw(3, 2, AmountWithdrawn);
  }
  return Funds[FundID].processWithdraw(AmountWithdrawn);
}

// Processes deposit
int Account::processDeposit(int FundID, int AmountDeposited) {
  return Funds[FundID].processDeposit(AmountDeposited);
}

// Processes transfer
int Account::processTransfer(int FundID, int TransferToAccountID,
                             int TransferToFundID, int TransferAmount) {
  return Funds[FundID].processTransfer(TransferToAccountID, TransferToFundID,
                                       TransferAmount);
}

// Processes history
void Account::processHistory(int FundID) {
  if (FundID == -1) {
    cout << "Displaying Transaction History for " << LastName << " "
         << FirstName << " by fund." << endl;
    for (int I = 0; I < MAX_ITEMS; ++I) {
      cout << FundNames[I] << ": $" << Funds[I].getAmount() << endl;
      vector<string> History = Funds[I].getHistory();
      for (auto I : History) {
        cout << "        " << I << endl;
      }
    }
  } else {
    cout << "Displaying Transaction History for " << LastName << " "
         << FirstName << "'s " << FundNames[FundID] << ": $"
         << Funds[FundID].getAmount() << endl;
    vector<string> History = Funds[FundID].getHistory();
    for (auto I :History) {
      cout << "        " << I << endl;
    }
  }
}

// Displays the Account with all its funds
void Account::display() {
  cout << LastName << " " << FirstName << "  Account ID: " << AccountID
       << "  Balance: $" << getBalance() << endl;
  for (int I = 0; I < MAX_ITEMS; ++I) {
    cout << "    " << FundNames[I] << ": $" << Funds[I].getAmount() << endl;
  }
  cout << endl;
}

// Special withdraw for Market funds and bonds
int Account::specialProcessWithdraw(int FundID1, int FundID2,
                                    int AmountWithdrawn) {
  if (AmountWithdrawn >
      Funds[FundID1].getAmount() + Funds[FundID2].getAmount()) {
    // This will fail and generate an error in history
    return Funds[FundID1].processWithdraw(AmountWithdrawn);
  }
  if (AmountWithdrawn <= Funds[FundID1].getAmount()) {
    return Funds[FundID1].processWithdraw(AmountWithdrawn);
  }
  Funds[FundID2].processWithdraw(AmountWithdrawn - Funds[FundID1].getAmount());
  Funds[FundID1].processWithdraw(Funds[FundID1].getAmount());

  return AmountWithdrawn;
}
