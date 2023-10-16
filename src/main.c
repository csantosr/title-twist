#include "library.h"
#include "book.h"
#include "persistence.h"
#include <stdio.h>

void printMenu()
{
    printf("TitleTwist CLI:\n");
    printf("1. Add Book\n");
    printf("2. Delete Book\n");
    printf("3. Edit Book\n");
    printf("4. Display Book Details\n");
    printf("5. Update Progress\n");
    printf("6. Search Books\n");
    printf("7. Change Book Tags\n");
    printf("8. List all books\n");
    printf("9. Filter by tag\n");
    printf("10. Display all loans\n");
    printf("11. Filter loans by status\n");
    printf("12. Exit\n");
    printf("> ");
}

int main()
{
    Library library;
    loadLibraryFromFile(&library, "./library.dat");

    int choice;
    int id;

    while (1)
    {
        printMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            Book book;
            printf("Enter book title: ");
            scanf(" %[^\n]", book.title);
            printf("Enter book author: ");
            scanf(" %[^\n]", book.author);
            printf("Enter number of pages: ");
            scanf("%d", &book.num_pages);
            book.current_page = 0; // Initialized to 0
            book.progress = 0.0;   // Initialized to 0%
            printf("Enter book review: ");
            scanf(" %[^\n]", book.review);
            printf("Enter book rating (0 to 5): ");
            scanf("%f", &book.rating);
            int num_tags;
            printf("Enter number of tags (0-%d): ", MAX_TAGS);
            scanf("%d", &num_tags);

            for (int i = 0; i < num_tags; i++)
            {
                printf("Enter tag %d: ", i + 1);
                scanf(" %[^\n]", book.tags[i]);
            }
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
        case 3:
        {
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
            int num_tags;
            printf("Enter number of tags (0-%d): ", MAX_TAGS);
            scanf("%d", &num_tags);

            for (int i = 0; i < num_tags; i++)
            {
                printf("Enter tag %d: ", i + 1);
                scanf(" %[^\n]", book.tags[i]);
            }
            editBook(&library, id, book);
            printf("Book edited (if it existed).\n");
            saveLibraryToFile(&library, "./library.dat");
            break;
        }
        case 4:
            printf("Enter book ID to display: ");
            scanf("%d", &id);
            BookNode *current = library.books_head;
            while (current)
            {
                if (current->book.id == id)
                {
                    displayBookDetails(current->book);
                    break;
                }
                current = current->next;
            }
            if (!current)
            {
                printf("Book with ID %d not found.\n", id);
            }
            break;
        case 5:
        {
            printf("Enter book ID to update progress: ");
            scanf("%d", &id);
            int current_page;
            printf("Enter the current page: ");
            scanf("%d", &current_page);
            updateProgress(&library, id, current_page);
            saveLibraryToFile(&library, "./library.dat");
            break;
        }
        case 6:
        {
            printf("Enter search query: ");
            char query[MAX_TITLE_LENGTH];
            scanf(" %[^\n]", query);
            printf("Choose search type (1: Title, 2: Author, 3: Tag): ");
            int type;
            scanf("%d", &type);
            searchBooks(&library, query, type);
            break;
        }
        case 7:
        {
            printf("Enter book ID to change tags: ");
            int id;
            scanf("%d", &id);
            changeBookTags(&library, id);
            break;
        }
        case 8:
        {
            listBooks(&library);
            break;
        }
        case 9:
        {
            char tag[MAX_TAG_LENGTH];
            printf("Enter the tag to filter by: ");
            scanf(" %[^\n]", tag);
            filterBooksByTag(&library, tag);
            break;
        }
        case 10:
            displayAllLoans(&library);
            break;
        case 11:
        {
            int status;
            printf("Enter loan status (1 for Active, 2 for Returned): ");
            scanf("%d", &status);

            if (status == 1)
            {
                filterLoansByStatus(&library, ACTIVE);
            }
            else if (status == 2)
            {
                filterLoansByStatus(&library, RETURNED);
            }
            else
            {
                printf("Invalid status choice.\n");
            }
            break;
        }
        case 12:
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
