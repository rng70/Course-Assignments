package com.company.Bank;

import com.company.Account.*;
import com.company.Employee.*;
import java.util.HashMap;

public class Bank {
  private int initialFund;
  private final int numberOfManagers, numberOfOfficers, numberOfCashiers;
  private int clockToCountYear;
  private double irStudent, irSavings, irFixed;

  // List of employees and accounts
  private HashMap<String, Account> accounts = new HashMap<>();
  private HashMap<String, Employee> employees = new HashMap<>();

  public Bank() {
    this.initialFund = 1000000;
    this.numberOfManagers = 1;
    this.numberOfOfficers = 2;
    this.numberOfCashiers = 5;
    this.clockToCountYear = 0;
    this.irStudent = 5;
    this.irSavings = 10;
    this.irFixed = 15;
    Initialize();
    Print();
  }

  public void CreateAccount(String name, String AccountType, double initialDeposit) {
    if (AccountType.equals("Student")) {
      Account newAccount = new Student(name, AccountType, initialDeposit);
      accounts.put(name, newAccount);
    } else if (AccountType.equals("Fixed")) {
      if (initialDeposit > 100000) {
        Account newAccount = new Fixed(name, AccountType, initialDeposit);
        accounts.put(name, newAccount);
      } else {
        System.out.println("Sorry, you need to deposit at least 100000$");
      }
    } else if (AccountType.equals("Savings")) {
      Account newAccount = new Savings(name, AccountType, initialDeposit);
      accounts.put(name, newAccount);
    }
  }

  private void initializeEmployees(String s, int count, String AccountType) {
    Employee emp = new Employee();
    StringBuilder sBuilder = new StringBuilder(s);
    s = sBuilder.toString() + "1";
    for (int i = 1; i <= count; i++) {
      s = s.substring(0, s.length() - 1) + Integer.toString(i);
      if (count == 1) s = s.substring(0, s.length() - 1);
      Employee newEmployee = emp.createEmployee(this, s, AccountType);
      employees.put(s, newEmployee);
    }
  }

  private void Initialize() {
    int count;
    count = this.getTotalNumberOfEmployee('M');
    initializeEmployees("MD", count, "ManagingDirector");
    count = this.getTotalNumberOfEmployee('O');
    initializeEmployees("O", count, "Officer");
    count = this.getTotalNumberOfEmployee('C');
    initializeEmployees("C", count, "Cashier");
  }

  private void Print() {
    System.out.print("Bank Created : ");
    for (String key : employees.keySet()) {
      System.out.print(key + " ");
    }
    System.out.println("created");
  }

  public int getTotalNumberOfEmployee(char ch) {
    int result;
    if (ch == 'C' || ch == 'c') {
      result = this.numberOfCashiers;
    } else if (ch == 'O' || ch == 'o') {
      result = this.numberOfOfficers;
    } else {
      result = this.numberOfManagers;
    }
    return result;
  }

  public void lookUpForUserDeposit(String name) {
    if (!accounts.containsKey(name)) {
      System.out.println("Invalid query for user " + name);
      return;
    }
    System.out.println(name + "’s current balance " + accounts.get(name).getDeposit() + "$");
  }

  public void approveLoanIfFundExists() {
    for (String key : accounts.keySet()) {
      if (accounts.get(key).getRequestedLoanStatus()
          && this.getInitialFund() - accounts.get(key).getRequestedLoan() > 0) {
        accounts.get(key).setLoanStatus(false, true);
        this.initialFund -= accounts.get(key).getLoan();
        System.out.println("Loan for " + key + " approved");
      } else if (this.getInitialFund() <= 0) {
        System.out.println("Sorry! Insufficient fund.");
        return;
      }
    }
  }

  public int getInitialFund() {
    return this.initialFund;
  }

  public Account getAccount(String name) {
    return accounts.get(name);
  }

  public Employee getEmployee(String name) {
    return employees.get(name);
  }

  public int getClockToCountYear() {
    return clockToCountYear;
  }

  public boolean getIfAnyLoanRequested() {
    for (String key : accounts.keySet()) {
      if (accounts.get(key).getRequestedLoanStatus()) return true;
    }
    return false;
  }

  public void yearlyIncrement() {
    this.clockToCountYear = this.getClockToCountYear() + 1;
    for (String key : accounts.keySet()) {
      double rate;
      if (accounts.get(key).getType().equals("Student")) rate = this.irStudent;
      else if (accounts.get(key).getType().equals("Fixed")) rate = this.irFixed;
      else rate = this.irSavings;
      accounts.get(key).yearlyIncrement(rate);
    }
  }

  public void changeInterest(double changedInterest, String AccountType) {
    if (AccountType.equals("Student")) {
      irStudent = changedInterest;
    } else if (AccountType.equals("Fixed")) {
      irFixed = changedInterest;
    } else {
      irSavings = changedInterest;
    }
  }
}
