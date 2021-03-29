package com.company.Employee;

import com.company.Bank.Bank;

public class Cashier extends Employee {
  public Cashier(Bank bank, String name, String AccountType, boolean hasAccess) {
    super(bank, name, AccountType, hasAccess);
  }

  @Override
  public void seeInternalFund() {
    System.out.println("Invalid operation! You don't have permission to see internal fund.");
  }

  @Override
  public void changeInterest(double x, String AccountType) {
    System.out.println("You don’t have permission for this operation");
  }

  @Override
  public void ApproveLoan() {
    if (!this.getHasAccess()) {
      System.out.println("Invalid Operation! You don't have permission to approve loan");
    } else {
      super.ApproveLoan();
    }
  }
}
