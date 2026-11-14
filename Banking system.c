/* Banking System
   Compile: gcc bank.c -o bank
   The account is saved in the file account.dat */

#include <stdio.h>

struct Account {
    char name[50];
    float balance;
};

struct Account acc;      /* the bank account */

void saveAccount() {
    FILE *fp = fopen("account.dat", "wb");
    if (fp == NULL) {
        printf("(Could not save to a file.)\n");
        return;
    }
    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);
}

void deposit() {
    float amount = 0;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid amount.\n");
    } else {
        acc.balance = acc.balance + amount;
        saveAccount();
        printf("Deposited. New balance: %.2f\n", acc.balance);
    }
}

void withdraw() {
    float amount = 0;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid amount.\n");
    } else if (amount > acc.balance) {
        printf("Insufficient balance.\n");
    } else {
        acc.balance = acc.balance - amount;
        saveAccount();
        printf("Withdrawn. New balance: %.2f\n", acc.balance);
    }
}

void enquiry() {
    printf("Account holder: %s\n", acc.name);
    printf("Balance: %.2f\n", acc.balance);
}

int main() {
    int choice;
    FILE *fp = fopen("account.dat", "rb");

    if (fp != NULL) {                        /* saved account found */
        fread(&acc, sizeof(acc), 1, fp);
        fclose(fp);
    } else {                                 /* first run: open a new account */
        printf("Enter your name: ");
        scanf(" %49[^\n]", acc.name);
        printf("Enter opening balance: ");
        scanf("%f", &acc.balance);
        if (acc.balance < 0)
            acc.balance = 0;
        saveAccount();
    }

    do {
        printf("\n1. Deposit\n2. Withdraw\n3. Balance enquiry\n0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
            choice = 0;                      /* if a letter is typed, exit */

        if (choice == 1)
            deposit();
        else if (choice == 2)
            withdraw();
        else if (choice == 3)
            enquiry();
        else if (choice != 0)
            printf("Invalid choice.\n");
    } while (choice != 0);

    printf("Thank you. Goodbye!\n");
    return 0;
}
