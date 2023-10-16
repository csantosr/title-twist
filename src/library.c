#include "library.h"
#include <stdlib.h>

void initializeLibrary(Library *library) {
    library->books_head = NULL;
    library->loans_head = NULL;
}

void freeLibrary(Library *library) {
    BookNode *current_book = library->books_head;
    while (current_book) {
        BookNode *temp = current_book;
        current_book = current_book->next;
        free(temp);
    }

    LoanNode *current_loan = library->loans_head;
    while (current_loan) {
        LoanNode *temp = current_loan;
        current_loan = current_loan->next;
        free(temp);
    }
}
