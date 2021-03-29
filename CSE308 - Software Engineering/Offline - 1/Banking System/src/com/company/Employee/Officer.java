package com.company.Employee;

import com.company.Bank.Bank;

public class Officer extends Employee {
  public Officer(Bank bank, String name, String AccountType, boolean hasAccess) {
    super(bank, name, AccountType, hasAccess);
  }

  @Override
  public void seeInternalFund() {
    System.out.println("Invalid operation! You don't have permission to see the internal fund");
  }

  @Override
  public void ApproveLoan() {
    if (!this.getHasAccess()) {
      System.out.println("You don’t have permission for this operation");
    } else {
      super.ApproveLoan();
    }
  }

  @Override
  public void changeInterest(double x, String AccountType) {
    System.out.println("You don’t have permission for this operation");
  }
}
