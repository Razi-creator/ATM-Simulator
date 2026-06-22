#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  
#include <cstdio>   
using namespace std;
class ATM {
private:
    string accountHolder;
    int accountNumber;
    double balance;
    string transactions[5];  
    int transactionCount;
public:
    ATM() {
        accountNumber = 0;
        balance = 0.0;
        transactionCount = 0;
    }
    string formatAmount(double value) {
        char buf[20];
        sprintf(buf, "%.2f", value);
        return string(buf);
    }

    void addTransaction(string transaction) {
        if (transactionCount == 5) {
            for (int i = 0; i < 5; i++) {
                transactions[i] = transactions[i + 1];
            }
            
        } else {
            transactions[transactionCount] = transaction;
            transactionCount++;
        }
    }

    void appendToCSV(string transaction) {
        ofstream file("transactions.csv", ios::app);
        if (file.is_open()) {
            file << accountHolder << "," << accountNumber << "," << formatAmount(balance) << "," << transaction << endl;
            file.close();
        }
    }

    void createAccount(string name, int accNo, double initialBalance) {
        accountHolder = name;
        accountNumber = accNo;
        balance = initialBalance;
        transactionCount = 0;

        if (initialBalance > 0) {
            string t = "Deposited: $" + formatAmount(initialBalance);
            addTransaction(t);
            appendToCSV(t);
        }

        cout << "Account created successfully!\n";
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount.\n";
            return;
        }

        balance += amount;
        string t = "Deposited: $" + formatAmount(amount);
        addTransaction(t);
        appendToCSV(t);
        cout << "Deposit successful!"<<endl;
		cout<<"Current Balance: $" << formatAmount(balance) << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount.\n";
            return;
        }
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return;
        }

        balance -= amount;
        string t = "Withdrew: $" + formatAmount(amount);
        addTransaction(t);
        appendToCSV(t);
        cout << "Withdrawal successful!\nCurrent Balance: $" << formatAmount(balance) << endl;
    }

    void showBalance() {
        if (accountNumber == 0) {
            cout << "Please create an account first.\n";
            return;
        }
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: $" << formatAmount(balance) << endl;
    }
    
    void printMiniStatement() {
        if (accountNumber == 0) {
            cout << "Please create an account first.\n";
            return;
        }

        if (transactionCount == 0) {
            cout << "No transactions yet.\n";
            return;
        }

        cout << "Mini Statement:\n";
        for (int i = 0; i < transactionCount; i++) {
            cout << (i + 1) << ". " << transactions[i] << endl;
        }
    }

    void loadTransactionsFromFile() {
        ifstream file("transactions.csv");
        if (!file) {
            cout << "No previous transactions found.\n";
            return;
        }

        string line;
        transactionCount = 0;

        while (getline(file, line)) {
            string name, accStr, balStr, trans;
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            name = line.substr(0, pos1);
            accStr = line.substr(pos1 + 1, pos2 - pos1 - 1);
            balStr = line.substr(pos2 + 1, pos3 - pos2 - 1);
            trans = line.substr(pos3 + 1);

            accountHolder = name;
            accountNumber = atoi(accStr.c_str());
            balance = atof(balStr.c_str());

            addTransaction(trans);
        }

        file.close();
        cout << "Previous transactions loaded successfully.\n";
    }

    int getAccountNumber() {
        return accountNumber;
    }
};
int main() {
    ATM atm;
    int choice;

    cout << "Welcome to Simple ATM!\n";
    atm.loadTransactionsFromFile();

    do {
        cout << "\n1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Mini Statement\n";
        cout << "6. Save Transactions to File\n";
        cout << "7. Load Transactions from File\n";
        cout << "8. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                if (atm.getAccountNumber() != 0) {
                    cout << "Account already exists.\n";
                    break;
                }
                string name;
                int accNo;
                double initBal;
                cout << "Enter account holder name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter account number: ";
                cin >> accNo;
                cout << "Enter initial balance: ";
                cin >> initBal;
                atm.createAccount(name, accNo, initBal);
                break;
            }

            case 2: {
                if (atm.getAccountNumber() == 0) {
                    cout << "Please create an account first.\n";
                    break;
                }
                double amount;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                atm.deposit(amount);
                break;
            }

            case 3: {
                if (atm.getAccountNumber() == 0) {
                    cout << "Please create an account first.\n";
                    break;
                }
                double amount;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                atm.withdraw(amount);
                break;
            }

            case 4:
                atm.showBalance();
                break;

            case 5:
                atm.printMiniStatement();
                break;

            case 6:
                cout << "Transactions are already saved automatically in CSV file.\n";
                break;

            case 7:
                atm.loadTransactionsFromFile();
                break;

            case 8:
                cout << "Thank you for using Simple ATM. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}

