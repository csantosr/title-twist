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

#define SEARCH_TITLE 1
#define SEARCH_AUTHOR 2
#define SEARCH_TAG 3

void initializeLibrary(Library *library);
void freeLibrary(Library *library);
void addBook(Library *library, Book book);
void deleteBook(Library *library, int book_id);
void editBook(Library *library, int book_id, Book new_book_data);
void displayBookDetails(Book book);
void loanBook(Library *library, int book_id, char *friend_nickname);
void returnBook(Library *library, int book_id);
void updateProgress(Library *library, int book_id, int current_page);
void searchBooks(Library *library, const char *query, int searchType);
void changeBookTags(Library *library, int book_id);
void listBooks(Library *library);

#endif // LIBRARY_H