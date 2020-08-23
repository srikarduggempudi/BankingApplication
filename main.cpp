//
// Created by Srikar Duggempudi on 12/2/2019.
//

#include "bank.h"
#include <iostream>
#include <string>


using namespace std;

int main(int Argc, char *Argv[]) {
    Bank Bank;
    //Note that tests were done in BankTransIn.txt
    for(int I = 1; I < Argc; ++I) {
        cout << "The command line argument(s) was " << Argv[I] << std::endl;
        string FileName = Argv[I];
        Bank.processTransactions(FileName);
        Bank.displayAllBankBalances();
    }
    cout << "Done" << endl;
    return 0;
}