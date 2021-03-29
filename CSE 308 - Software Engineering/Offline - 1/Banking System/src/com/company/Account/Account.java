package com.company.Account;

public class Account {
  private final String name;
  private final int year;
  private final String type;
  private int requestedLona;
  private double deposit, loan;
  private boolean requestedLonaStatus, requestedLonaApproval, loanRequestedFlag=false;

  public Account() {
    this.name = "";
    this.type = "";
    this.year = -1;
    this.deposit = -1.0;
    this.loan = this.deposit;
  }

  public Account(String name, String AccountType, double initialDeposit) {
    this.name = name;
    this.type = AccountType;
    this.deposit = initialDeposit;
    this.loan = 0;
    this.year = 0;
  }

  public void Deposit(double depositAmount) {
    this.deposit += depositAmount;
  }

  public void Withdraw(double withdrawAmount) {
    this.deposit -= withdrawAmount;
  }

  public void queryDeposit(){
    System.out.print("Current Balance is " + this.deposit + "$");
    if (loanRequestedFlag) System.out.print(", loan " + this.loan + "$");
    System.out.println();
  }

  public void requestLoan(int amount){
    this.requestedLonaStatus = true;
    this.requestedLonaApproval = false;
    this.requestedLona = amount;
    System.out.println("Loan request successful, sent for approval");
  }

  public String getName() {
    return name;
  }

  public int getYear() {
    return this.year;
  }

  public double getDeposit() {
    return this.deposit;
  }
  public double getLoan(){
    return this.loan;
  }
  public String getType(){
    return this.type;
  }
  public void setDeposit(double depVal) {
    this.deposit = depVal;
  }

  public boolean getRequestedLoanStatus() {
    return this.requestedLonaStatus;
  }
  public int getRequestedLoan(){
    return this.requestedLona;
  }
  public void setLoanStatus(boolean rLS, boolean rLA){
    this.requestedLonaStatus = rLS;
    this.requestedLonaApproval = rLA;
    this.loanApproved();
  }
  public void loanApproved(){
    if(requestedLonaApproval){
      this.loan = this.getRequestedLoan();
      this.deposit += this.loan;
      this.requestedLona = 0;
      this.loanRequestedFlag = true;
      this.requestedLonaApproval = false;
      this.requestedLonaStatus = false;
    }
  }
  public void yearlyIncrement(double rate){
    this.deposit -= 1.0 * this.loan * 10.0 / 100.0;
    this.deposit += this.loan;
  }
}
