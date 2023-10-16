#ifndef LOAN_H
#define LOAN_H

#define MAX_NICKNAME_LENGTH 50
#define DATE_STRING_LENGTH 11  // Formato "YYYY-MM-DD\0"

typedef enum {
    ACTIVE,
    RETURNED
} LoanStatus;

typedef struct {
    int book_id;
    char friend_nickname[MAX_NICKNAME_LENGTH];
    char loan_date[DATE_STRING_LENGTH];
    char return_date[DATE_STRING_LENGTH];
    LoanStatus status;
} Loan;

#endif // LOAN_H
