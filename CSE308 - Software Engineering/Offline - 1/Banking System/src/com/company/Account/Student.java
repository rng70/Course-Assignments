package com.company.Account;

public class Student extends Account {
  public Student(String name, String AccountType, double initialDeposit) {
    super(name, AccountType, initialDeposit);
    System.out.println(
            "Student Account for " + name + " created. Initial deposit " + initialDeposit + "$");

  }

  @Override
  public void Deposit(double depositAmount) {
    super.Deposit(depositAmount);
    System.out.println(depositAmount + "$ deposited; current balance " + this.getDeposit() + "$");
  }

  @Override
  public void Withdraw(double withdrawAmount) {
    if (withdrawAmount <= 10000 && this.getDeposit() < withdrawAmount) {
      super.Withdraw(withdrawAmount);
      System.out.println("Transaction successful. Current deposit is " + this.getDeposit());
    } else {
      System.out.println("Invalid transaction; Cannot withdraw more than 1000$ in one transaction");
    }
  }

  @Override
  public void queryDeposit() {
    super.queryDeposit();
  }

  @Override
  public void requestLoan(int amount) {
    if (amount > 1000) {
      System.out.println("Invalid Amount requested. Please request a valid amount");
      return;
    }
    super.requestLoan(amount);
  }

  @Override
  public void yearlyIncrement(double rate){
    double amount = (this.getDeposit() - this.getLoan())*(1.0+rate/100.0);
    super.setDeposit(amount);
    super.yearlyIncrement(rate);
  }
}
