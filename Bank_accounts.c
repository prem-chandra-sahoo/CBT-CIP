#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

// Account types
#define SAVINGS 1
#define CURRENT 2
#define FIXED_DEPOSIT 3

// Account structure
struct Account {
    int account_number;
    char name[100];
    int account_type;
    float balance;
    char pin[5];  // Pin for user authentication
    int is_active; // To check if the account is active
};


struct Account* accounts[MAX_ACCOUNTS];
int account_count = 0;


void create_account() {
    struct Account* new_account = (struct Account*)malloc(sizeof(struct Account));
    if (new_account == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &new_account->account_number);
    getchar(); // To consume the newline character
    printf("Enter Account Holder's Name: ");
    fgets(new_account->name, 100, stdin);
    new_account->name[strcspn(new_account->name, "\n")] = '\0'; // Remove newline

    printf("Enter Account Type (1 for SAVINGS, 2 for CURRENT, 3 for FIXED DEPOSIT): ");
    scanf("%d", &new_account->account_type);

    printf("Create a PIN (4 digits): ");
    scanf("%4s", new_account->pin); // Read PIN as string to handle it safely

    new_account->balance = 0;  // Account starts with a balance of 0
    new_account->is_active = 1;  // New account is active by default

    accounts[account_count++] = new_account;
    printf("Account Created Successfully!\n");
}

struct Account* find_account(int account_number) {
    for (int i = 0; i < account_count; i++) {
        if (accounts[i]->account_number == account_number && accounts[i]->is_active) {
            return accounts[i];
        }
    }
    return NULL;
}

int validate_pin(struct Account* account) {
    char pin_input[5];
    printf("Enter PIN: ");
    scanf("%4s", pin_input);
    if (strcmp(account->pin, pin_input) == 0) {
        return 1;
    } else {
        printf("Invalid PIN!\n");
        return 0;
    }
}


void deposit() {
    int account_number;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &account_number);
    struct Account* account = find_account(account_number);

    if (account != NULL) {
        if (validate_pin(account)) {
            printf("Enter Deposit Amount: ");
            scanf("%f", &amount);
            if (amount > 0) {
                account->balance += amount;
                printf("Deposited %.2f. New Balance: %.2f\n", amount, account->balance);
            } else {
                printf("Invalid deposit amount.\n");
            }
        }
    } else {
        printf("Account not found!\n");
    }
}

// Function to withdraw funds
void withdraw() {
    int account_number;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &account_number);
    struct Account* account = find_account(account_number);

    if (account != NULL) {
        if (validate_pin(account)) {
            printf("Enter Withdrawal Amount: ");
            scanf("%f", &amount);
            if (amount > 0 && amount <= account->balance) {
                account->balance -= amount;
                printf("Withdrew %.2f. New Balance: %.2f\n", amount, account->balance);
            } else {
                printf("Insufficient funds or invalid amount.\n");
            }
        }
    } else {
        printf("Account not found!\n");
    }
}

// Function to check balance
void check_balance() {
    int account_number;

    printf("Enter Account Number: ");
    scanf("%d", &account_number);
    struct Account* account = find_account(account_number);

    if (account != NULL) {
        if (validate_pin(account)) {
            printf("Account Balance: %.2f\n", account->balance);
        }
    } else {
        printf("Account not found!\n");
    }
}

// Function to calculate interest
void calculate_interest() {
    int account_number;
    printf("Enter Account Number: ");
    scanf("%d", &account_number);
    struct Account* account = find_account(account_number);

    if (account != NULL) {
        if (validate_pin(account)) {
            float interest_rate;
            float interest;

            switch (account->account_type) {
                case SAVINGS:
                    interest_rate = 0.05;  // 5% interest for savings
                    break;
                case CURRENT:
                    interest_rate = 0.02;  // 2% interest for current
                    break;
                case FIXED_DEPOSIT:
                    interest_rate = 0.08;  // 8% interest for fixed deposit
                    break;
                default:
                    printf("Invalid account type.\n");
                    return;
            }

            interest = account->balance * interest_rate;
            printf("Interest for this account: %.2f\n", interest);
        }
    } else {
        printf("Account not found!\n");
    }
}

// Function to display account details
void display_account_details() {
    int account_number;
    printf("Enter Account Number: ");
    scanf("%d", &account_number);
    struct Account* account = find_account(account_number);

    if (account != NULL) {
        if (validate_pin(account)) {
            printf("Account Number: %d\n", account->account_number);
            printf("Account Holder's Name: %s\n", account->name);
            printf("Account Type: ");
            switch (account->account_type) {
                case SAVINGS: printf("SAVINGS\n"); break;
                case CURRENT: printf("CURRENT\n"); break;
                case FIXED_DEPOSIT: printf("FIXED DEPOSIT\n"); break;
                default: printf("Unknown\n"); break;
            }
            printf("Balance: %.2f\n", account->balance);
        }
    } else {
        printf("Account not found!\n");
    }
}

// Function to close an account
void close_account() {
    int account_number;
    printf("Enter Account Number to Close: ");
    scanf("%d", &account_number);
    struct Account* account = find_account(account_number);

    if (account != NULL) {
        if (validate_pin(account)) {
            account->is_active = 0;  // Mark account as inactive
            printf("Account closed successfully.\n");
        }
    } else {
        printf("Account not found!\n");
    }
}

// Function to display the menu
void menu() {
    int choice;
    do {
        printf("\n--- Bank Account Management System ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit Funds\n");
        printf("3. Withdraw Funds\n");
        printf("4. Check Balance\n");
        printf("5. Calculate Interest\n");
        printf("6. Display Account Details\n");
        printf("7. Close Account\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                check_balance();
                break;
            case 5:
                calculate_interest();
                break;
            case 6:
                display_account_details();
                break;
            case 7:
                close_account();
                break;
            case 8:
                printf("Exiting... Thank you for using the system.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);
}

int main() {
    menu();
    return 0;
}
