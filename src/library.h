#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"
#include "loan.h"

typedef struct BookNode {
    Book book;
    struct BookNode* next;
} BookNode;

typedef struct LoanNode {
    Loan loan;
    struct LoanNode* next;
} LoanNode;

typedef struct {
    struct BookNode* books_head;
    struct LoanNode* loans_head;
} Library;

void initializeLibrary(Library *library);
void freeLibrary(Library *library);
void addBook(Library *library, Book book);
void deleteBook(Library *library, int book_id);
void editBook(Library *library, int book_id, Book new_book_data);
void displayBookDetails(Book book);

#endif // LIBRARY_H