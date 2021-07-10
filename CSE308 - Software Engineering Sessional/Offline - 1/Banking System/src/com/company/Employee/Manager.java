package com.company.Employee;

import com.company.Bank.Bank;

public class Manager extends Employee {
  public Manager(Bank bank, String name, String AccountType, boolean hasAccess) {
    super(bank, name, AccountType, hasAccess);
  }

  @Override
  public void seeInternalFund() {
    super.seeInternalFund();
  }

  @Override
  public void ApproveLoan() {
    if (!this.getHasAccess()) {
      System.out.println("Invalid Operation! You don't have permission to approve loan");
    } else {
      super.ApproveLoan();
    }
  }

  @Override
  public void changeInterest(double x, String AccountType) {
    super.changeInterest(x, AccountType);
    System.out.println(
        "Interest rate is changed successfully to " + x + " for " + AccountType + " account");
  }
}
