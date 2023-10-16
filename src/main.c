#include "library.h"
#include "book.h"
#include "persistence.h"
#include <stdio.h>

void printMenu() {
    printf("TitleTwist CLI:\n");
    printf("1. Add Book\n");
    printf("2. Delete Book\n");
    printf("3. Edit Book\n");
    printf("4. Display Book Details\n");
    printf("5. Exit\n");
    printf("> ");
}

int main() {
    Library library;
    loadLibraryFromFile(&library, "./library.dat");

    int choice;
    int id;

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Book book;
                printf("Enter book title: ");
                scanf(" %[^\n]", book.title);
                printf("Enter book author: ");
                scanf(" %[^\n]", book.author);
                printf("Enter number of pages: ");
                scanf("%d", &book.num_pages);
                book.current_page = 0;  // Initialized to 0
                book.progress = 0.0;    // Initialized to 0%
                printf("Enter book review: ");
                scanf(" %[^\n]", book.review);
                printf("Enter book rating (0 to 5): ");
                scanf("%f", &book.rating);
                // As an example, we'll skip the tags for simplicity. They can be added similarly.
                addBook(&library, book);
                printf("Book added successfully!\n");
                saveLibraryToFile(&library, "./library.dat");
                break;
            }
            case 2:
                printf("Enter book ID to delete: ");
                scanf("%d", &id);
                deleteBook(&library, id);
                printf("Book deleted (if it existed).\n");
                saveLibraryToFile(&library, "./library.dat");
                break;
            case 3: {
                Book book;
                printf("Enter book ID to edit: ");
                scanf("%d", &id);
                printf("Enter new book title: ");
                scanf(" %[^\n]", book.title);
                printf("Enter new book author: ");
                scanf(" %[^\n]", book.author);
                printf("Enter new number of pages: ");
                scanf("%d", &book.num_pages);
                printf("Enter new book review: ");
                scanf(" %[^\n]", book.review);
                printf("Enter new book rating (0 to 5): ");
                scanf("%f", &book.rating);
                editBook(&library, id, book);
                printf("Book edited (if it existed).\n");
                saveLibraryToFile(&library, "./library.dat");
                break;
            }
            case 4:
                printf("Enter book ID to display: ");
                scanf("%d", &id);
                BookNode *current = library.books_head;
                while (current) {
                    if (current->book.id == id) {
                        displayBookDetails(current->book);
                        break;
                    }
                    current = current->next;
                }
                if (!current) {
                    printf("Book with ID %d not found.\n", id);
                }
                break;
            case 5:
                printf("Exiting... \n");
                saveLibraryToFile(&library, "./library.dat");
                freeLibrary(&library);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    saveLibraryToFile(&library, "./library.dat");
    freeLibrary(&library);

    return 0;
}
