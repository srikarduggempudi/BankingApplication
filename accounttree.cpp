//
// Created by Srikar Duggempudi on 12/2/2019.
//

#include "accounttree.h"
#include <iomanip>
#include <ios>
#include <iostream>

using namespace std;


AccountTree::AccountTree() : Root(nullptr) {};

// Delete all nodes in BST
AccountTree::~AccountTree() { clear(); }

// Insert new account into the Binary tree
bool AccountTree::insert(Account *Account) {
  if (Root == nullptr) {
    Root = new Node(Account);
    return true;
  }
  return insertNode(Root, Account);
}

// Inserts Node at the right location in the Binary Tree
bool AccountTree::insertNode(Node *N, Account *Account) {
  if (Account->getAccountID() < N->Account->getAccountID()) {
    if (N->Left == nullptr) {
      N->Left = new Node(Account);
      return true;
    }
    return insertNode(N->Left, Account);
  }

  if (Account->getAccountID() > N->Account->getAccountID()) {
    if (N->Right == nullptr) {
      N->Right = new Node(Account);
      return true;
    }
    return insertNode(N->Right, Account);
  }
  return false;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *&Account) const {
  return retrieveNode(Root, AccountNumber, Account);
}

// Recursive retrieve method
bool AccountTree::retrieveNode(Node *N, const int &AccountNumber,
                               Account *&Account) const {
  if (N == nullptr) {
    return false;
  }

  if (AccountNumber == N->Account->getAccountID()) {
    Account = N->Account;
    return true;
  }

  if (AccountNumber < N->Account->getAccountID()) {
    return retrieveNode(N->Left, AccountNumber, Account);
  }
  return retrieveNode(N->Right, AccountNumber, Account);
}

// Display information on all accounts
void AccountTree::display() const { displayNode(Root); }

// Recursive display method
void AccountTree::displayNode(Node *N) const {
  if (N == nullptr) {
    return;
  }
  displayNode(N->Left);

  // Print the Account in the current Node
  N->Account->display();

  displayNode(N->Right);
}

// delete all information in AccountTree
void AccountTree::clear() {
  clearNode(Root);
  Root = nullptr;
}

// Recursive delete method
void AccountTree::clearNode(Node *N) {
  if (N == nullptr) {
    return;
  }

  clearNode(N->Left);
  clearNode(N->Right);

  // Delete the Node
  delete N->Account;
  delete N;
}

// check if tree is empty
bool AccountTree::isEmpty() const { return Root == nullptr; }