package com.company;

import com.company.Bank.Bank;

import java.util.Scanner;

public class Main {

  static void takeInput(Bank currentBank) {
    Scanner sc = new Scanner(System.in);
    // SingleTone user
    String currentUser = "Parrot", type = "acc";
    // have to handle NullPointerException
    // String input = null;
    String input = "";
    String[] line;
    while (!input.equals("21H")) {
      input = sc.nextLine();
      line = input.split(" ");
      String check = line[0].toLowerCase();
      if (check.equals("create")) {
        currentUser = line[1];
        type = "acc";
        currentBank.CreateAccount(line[1], line[2], Double.parseDouble(line[3]));
      } else if (check.equals("deposit")) {
        currentBank.getAccount(currentUser).Deposit(Double.parseDouble(line[1]));
      } else if (check.equals("withdraw")) {
        currentBank.getAccount(currentUser).Withdraw(Double.parseDouble(line[1]));
      } else if (check.equals("query")) {
        currentBank.getAccount(currentUser).queryDeposit();
      } else if (check.equals("request")) {
        currentBank.getAccount(currentUser).requestLoan(Integer.parseInt(line[1]));
      } else if (check.equals("close")) {
        if (type.equals("acc")) System.out.println("Transaction Closed for " + currentUser);
        else System.out.println("Operations for " + currentUser + " closed");
      } else if (check.equals("approve")) {
        currentBank.getEmployee(currentUser).ApproveLoan();
      } else if (check.equals("lookup")) {
        System.out.println(
            line[1] + "'s current balance is " + currentBank.getAccount(line[1]).getDeposit());
      } else if (check.equals("see")) {
        currentBank.getEmployee(currentUser).seeInternalFund();
      } else if (check.equals("open")) {
        currentUser = line[1];
        if (currentBank.getAccount(currentUser) != null) {
          type = "acc";
          System.out.println("Welcome back, " + currentUser);
        } else {
          type = "emp";
          System.out.print(currentUser + " active");
          if(currentBank.getIfAnyLoanRequested()){
            System.out.print(", there are loan approvals pending");
          }
          System.out.println();
        }
      }else if(check.equals("change")){
        currentBank.getEmployee(currentUser).changeInterest(Double.parseDouble(line[2]), line[1]);
      }else if(check.equals("inc")){
        currentBank.yearlyIncrement();
        System.out.println("1 year passed");
      }
    }
  }

  public static void main(String[] args) {
    Bank bank = new Bank();
    takeInput(bank);
  }
}
