# ATM-Simulator
A console-based banking application with CSV file handling.

# 📖 Overview
This project is a lightweight, console-based ATM simulation program written entirely in C++. It provides a simple interactive menu that allows users to perform standard banking operations, managing their balance and tracking their transaction history. To ensure data is not lost between sessions, the application automatically reads and writes transaction logs to a local CSV file.  

# ✨ FeaturesAccount Creation: 
Users can initialize a new bank account by entering an account holder name, an account number, and a starting balance.  
## Deposits & Withdrawals:
Users can add funds or withdraw money. The system includes validation to prevent withdrawing more money than the available balance or entering negative amounts.  
## Balance Inquiry:
Instantly display the account holder's name, account number, and current formatted balance.  
## Mini Statement: 
The system keeps track of the 5 most recent transactions in memory and can display them as a mini statement. 
Persistent Data Storage: Every transaction is automatically appended to a transactions.csv file. When the application starts, it reads this file to reload previous account details and transactions. 

🛠️ Technical DetailsLanguage: 
## C++  Libraries Used: 
<iostream>, <fstream> (for file handling), <string>, <cstdlib>, and <cstdio>.  
## Data Format: 
Stores records in a comma-separated format containing the account name, account number, balance, and transaction details.
