//
// Created by Srikar Duggempudi on 12/2/2019.
//

#ifndef ASS5_ACCOUNTTREE_H
#define ASS5_ACCOUNTTREE_H

#include "account.h"
#include <iostream>

class AccountTree {
public:
  // Create BST
  AccountTree();

  // Delete all nodes in BST
  ~AccountTree();

  // Insert new account
  bool insert(Account *Account);

  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int &AccountNumber, Account *&Account) const;

  // Display information on all accounts
  void display() const;

  // delete all information in AccountTree
  void clear();

  // check if tree is empty
  bool isEmpty() const;

private:
  class Node {
  public:
    explicit Node(Account *Account)
        : Account{Account}, Right{nullptr}, Left{nullptr} {};
    Account *Account;
    Node *Right;
    Node *Left;
  };
  Node *Root;

  bool insertNode(Node *N, Account *Account);
  bool retrieveNode(Node *N, const int &AccountNumber, Account *&Account) const;
  void displayNode(Node *N) const;
  void clearNode(Node *N);
};
#endif // ASS5_ACCOUNTTREE_H
