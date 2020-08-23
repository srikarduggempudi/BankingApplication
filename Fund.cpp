//
// Created by Srikar Duggempudi on 12/2/2019.
//

#include "fund.h"
#include <string>
#include <vector>

using namespace std;

Fund::Fund() : FundID{-1}, Name{""}, Amount{0} {}

Fund::~Fund() = default;

// Returns Fund ID
int Fund::getFundID() { return FundID; }

// Returns Account ID
int Fund::getAccountID() { return AccountID; }

// Returns Name
string Fund::getName() { return Name; }

// Returns Amount
int Fund::getAmount() const { return Amount; }

// Sets Fund ID
void Fund::setFundID(int FundID) { this->FundID = FundID; }

// Sets Account ID
void Fund::setAccountID(int AccountID) { this->AccountID = AccountID; }

// Sets Name
void Fund::setName(string Name) { this->Name = Name; }

// Returns History
vector<string> Fund::getHistory() { return History; }

// Processes withdraw
int Fund::processWithdraw(int AmountWithdrawn) {
  string HistoryRecord = "W ";
  HistoryRecord.append(to_string(AccountID));
  HistoryRecord.append(to_string(FundID));
  HistoryRecord.append(" ");
  HistoryRecord.append(to_string(AmountWithdrawn));
  int ProcessedAmount = 0;
  if (Amount < AmountWithdrawn) {
    HistoryRecord.append(" (Failed)");
  } else {
    Amount -= AmountWithdrawn;
    ProcessedAmount = -AmountWithdrawn;
  }

  History.push_back(HistoryRecord);
  return ProcessedAmount;
}

// Processes deposit
int Fund::processDeposit(int AmountDeposited) {
  Amount += AmountDeposited;
  string HistoryRecord = "D ";
  HistoryRecord.append(to_string(AccountID));
  HistoryRecord.append(to_string(FundID));
  HistoryRecord.append(" ");
  HistoryRecord.append(to_string(AmountDeposited));
  History.push_back(HistoryRecord);
  return AmountDeposited;
}

// Processes transfer
int Fund::processTransfer(int TransferToAccountID, int TransferToFundID,
                          int TransferAmount) {

  Amount -= TransferAmount;
  string HistoryRecord = "T ";
  HistoryRecord.append(to_string(AccountID));
  HistoryRecord.append(to_string(FundID));
  HistoryRecord.append(" ");
  HistoryRecord.append(to_string(TransferAmount));
  HistoryRecord.append(" ");
  HistoryRecord.append(to_string(TransferToAccountID));
  HistoryRecord.append(to_string(TransferToFundID));
  History.push_back(HistoryRecord);

  return -Amount;
}