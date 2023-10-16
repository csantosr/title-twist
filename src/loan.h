#ifndef LOAN_H
#define LOAN_H

#define MAX_NICKNAME_LENGTH 50
#define DATE_STRING_LENGTH 11  // Formato "YYYY-MM-DD\0"
#include <time.h>

typedef enum {
    ACTIVE,
    RETURNED
} LoanStatus;

typedef struct {
    int book_id;
    char friend_nickname[MAX_NICKNAME_LENGTH];
    time_t loan_date;
    time_t return_date;
    LoanStatus status;
} Loan;

#endif // LOAN_H
