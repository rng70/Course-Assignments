package com.company.Account;

public class Fixed extends Account {
  public Fixed(String name, String AccountType, double initialDeposit) {
    super(name, AccountType, initialDeposit);
    System.out.println(
        "Fixed Account for " + name + " created. Initial deposit " + initialDeposit + "$");
  }

  @Override
  public void Deposit(double depositAmount) {
    if (depositAmount >= 50000) {
      super.Deposit(depositAmount);
      System.out.println(depositAmount + "$ deposited; current balance " + this.getDeposit() + "$");
    } else {
      System.out.println("Invalid Deposit Amount.\n Please deposit 50000 or more.");
    }
  }

  @Override
  public void Withdraw(double withdrawAmount) {
    if (this.getYear() >= 1 && this.getDeposit() < withdrawAmount) {
      super.Withdraw(withdrawAmount);
      System.out.println("Transaction successful. Current deposit is " + this.getDeposit());
    } else {
      System.out.println("Invalid transaction; Maturity period of one year has not yet reached");
    }
  }

  @Override
  public void queryDeposit() {
    super.queryDeposit();
  }

  @Override
  public void requestLoan(int amount) {
    if (amount > 10000) {
      System.out.println("Invalid Amount requested. Please request a valid amount");
      return;
    }
    super.requestLoan(amount);
  }

  @Override
  public void yearlyIncrement(double rate) {
    double amount = (this.getDeposit() - this.getLoan()) * (1.0 + rate / 100.0) - 500.0;
    super.setDeposit(amount);
    super.yearlyIncrement(rate);
  }
}
