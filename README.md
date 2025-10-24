# 🏦 Welcome to the C++ POP Bank System! 🌟

Welcome to my C++ Bank Project! This isn't just a simple console application; it's a dedicated exercise in building a robust, maintainable, and scalable system using pure **Procedure-Oriented Programming (POP)**.

This project demonstrates how to solve complex problems by breaking them down into logical, clean, and efficient functions. Dive in to see how fundamental software design principles can be applied effectively, even without using Object-Oriented Programming (OOP).

## ✨ My Core Coding Philosophy

This project was built from the ground up with a deep respect for clean, organized, and reusable code. My entire approach is centered on these key principles:

### 1. Divide and Conquer 
The complex problem of "managing a bank" is broken down into smaller, logical, and manageable parts. You won't find a massive, unreadable `main()` function here!
* The **UI logic** (what the user sees) is separate from...
* The **Business Logic** (how a deposit *works*), which is separate from...
* The **Data Logic** (how data is read/written to files).

This separation makes the entire system easier to test, debug, and upgrade.

### 2. The Single Responsibility Principle (SRP)
Even in POP, SRP is king! 👑 Every single function in this project has **one, and only one, reason to change**.
* A function to `FindClient()` **only** finds a client. It doesn't print menus or update balances.
* A function to `SaveDataToFile()` **only** saves data. It doesn't know *what* the data is.
This approach creates a "toolbox" of reliable, independent functions that are easy to understand and trust.

### 3. DRY (Don't Repeat Yourself)
I am a firm believer in the DRY principle. Any piece of logic that needed to be used more than once (like a specific input validation or a line-parsing format) was immediately extracted into its own **reusable helper function**.

This means if we need to change how we read data, we only change it in *one* place, and the entire application updates instantly. This is the key to maintainability!

## 🚀 Key Features

* **Full Client Management (CRUD):** Add, Find, Update, and Delete client records.
* **Secure User Login:** Manages a separate `Users.txt` file for system user authentication.
* **Core Banking Operations:** Perform Deposits and Withdrawals.
* **Transaction Management:** List all transactions.
* **Data Persistence:** All client and user data is saved and loaded from `.txt` files, ensuring no data is lost between sessions.

## 💻 How It Works: The POP Structure

The project runs on a clear, procedural flow:

1.  **Load:** On startup, the system loads all data from `Clients.txt` and `Users.txt` into memory (using arrays/vectors).
2.  **Interact:** The user is guided through a series of clean, single-responsibility menus.
3.  **Process:** Each user choice calls a specific function (e.g., `ShowDepositScreen()`) which in turn calls other helper functions (e.g., `FindClientByID()`, `UpdateBalance()`).
4.  **Save:** All changes are immediately saved back to the `.txt` files to ensure data persistence.

This project is a gleaming example of how **Procedure-Oriented Programming** can be used to write clean, powerful, and highly organized applications.

---
