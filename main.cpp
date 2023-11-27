#include <iostream>
#include <string>
#include <iomanip>


class Account {
private:
    std::string accountNumber;
    std::string AccountName;
    double balance;

public:
    Account(const std::string& accountNumber, const std::string AccountName, double balance)
        : accountNumber(accountNumber), AccountName(AccountName), balance(balance) {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (balance <= amount) {
            balance -= amount;
        } else {
            std::cout << "Insufficient funds" << std::endl;
        }
    }
    
    void increaseBalance(double amount) {
        balance += amount;
    }

    void decreaseBalance(double amount) {
        balance -= amount;
    }

    double getBalance() const {
        return balance;
    }

    virtual void print() const {
        std::cout << "Account Details (ID: " << accountNumber << "):" << std::endl;
        std::cout << "Holder: " << AccountName << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
    }
};

class SavingsAccount : public Account {
    private:
        double interestRate;

    public:
        SavingsAccount(const std::string& accountNumber, const std::string AccountName, double balance, double interestRate)
            : Account(accountNumber, AccountName, balance), interestRate(interestRate) {}

        double calculateInterest() const {
            return getBalance() * interestRate;
    }
    void withdraw(double amount) override {
        if (Account::getBalance() - amount < 500) {  // Assume 500 as minimum balance
            std::cout << "Cannot withdraw. Minimum balance requirement not met.\n";
        } else {
            Account::withdraw(amount);
        }
    }
    void print() const override {
        Account::print();
        std::cout << "Interest Rate: "  << interestRate * 100 << std::endl;
    }
};

class CurrentAccount : public Account {
    private:
        double overdraftLimit;
    
    public:
        CurrentAccount(const std::string& accountNumber, const std::string AccountName, double balance, double overdraftLimit)
            : Account(accountNumber, AccountName, balance), overdraftLimit(overdraftLimit) {}

        void withdraw(double amount) override {
            if (Account::getBalance() - amount < overdraftLimit) {
                std::cout << "Cannot withdraw. Overdraft limit reached.\n";
            } else {
                Account::withdraw(amount);
            }
        }
        void print() const override {
            Account::print();
            std::cout << "Overdraft Limit: $" << overdraftLimit << std::endl;
        }
};


CurrentAccount& operator+(CurrentAccount& CurrentAccount, SavingsAccount& savingsAccount) {
    double transferAmount = 300;
    if (savingsAccount.getBalance() >= transferAmount) {
        savingsAccount.decreaseBalance(transferAmount);
        CurrentAccount.increaseBalance(transferAmount);
    } else {
        std::cout << "Insufficient funds in savings account" << std::endl;
    }
    return CurrentAccount;
}


int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.print();
    current.print();

    savings.deposit(500);
    current.withdraw(1000);

    std::cout << "\nAccount Details after deposit and withdrawal:\n";
    
    savings.print();
    current.print();

    // Transfer 300 from savings to current
    current = current + savings;

    std::cout << "\nAccount Details after transfer:\n";
    
    savings.print();
    current.print();

    return 0;
}
