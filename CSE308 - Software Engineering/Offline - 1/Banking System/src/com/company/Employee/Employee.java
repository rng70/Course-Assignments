package com.company.Employee;

import com.company.Bank.Bank;

public class Employee {
  Bank currentWorkingBank;
  private String name, type;
  private boolean hasAccess;

  public Employee() {
    this.name = "";
    this.type = "";
    hasAccess = false;
    currentWorkingBank = null;
  }

  public Employee(Bank bank, String name, String AccountType, boolean hasAccess) {
    this.currentWorkingBank = bank;
    this.name = name;
    this.type = AccountType;
    this.hasAccess = hasAccess;
  }

  public Employee createEmployee(Bank bank, String name, String AccountType) {
    if (AccountType.equals("ManagingDirector")) {
      return new Manager(bank, name, AccountType, true);
    } else if (AccountType.equals("Officer")) {
      return new Officer(bank, name, AccountType, true);
    } else {
      return new Cashier(bank, name, AccountType, false);
    }
  }

  public void seeInternalFund() {
    System.out.println("Internal fund is " + currentWorkingBank.getInitialFund() + "$");
  }

  protected void lookUp(String name) {
    currentWorkingBank.lookUpForUserDeposit(name);
  }

  public void ApproveLoan() {
    currentWorkingBank.approveLoanIfFundExists();
  }

  public void changeInterest(double rate, String AccountType) {
    currentWorkingBank.changeInterest(rate, AccountType);
  }

  public boolean getHasAccess() {
    return this.hasAccess;
  }
}
