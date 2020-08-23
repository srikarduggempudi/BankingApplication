//
// Created by Srikar Duggempudi on 12/2/2019.
//

#ifndef ASS5_FUND_H
#define ASS5_FUND_H
#include <string>
#include <vector>
using namespace std;

class Fund {

public:
  Fund();
  ~Fund();
  int getFundID();
  int getAccountID();
  string getName();
  int getAmount() const;
  void setFundID(int FundID);
  void setAccountID(int AccountID);
  void setName(string Name);
  vector<string> getHistory();
  int processWithdraw(int AmountWithdrawn);
  int processDeposit(int AmountDeposited);
  int processTransfer(int TransferToAccountID, int TransferToFundID,
                      int TransferAmount);

private:
  int FundID;
  int AccountID;
  string Name;
  int Amount;
  vector<string> History;
};

#endif // ASS5_FUND_H
