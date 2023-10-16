#include "book.h"
#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int next_book_id = 1;

void addBook(Library *library, Book book) {
    BookNode *new_node = (BookNode *)malloc(sizeof(BookNode));
    if (!new_node) {
        printf("Error allocating memory.\n");
        return;
    }

    book.id = next_book_id++;

    new_node->book = book;
    new_node->next = NULL;

    if (!library->books_head) {
        library->books_head = new_node;
    } else {
        BookNode *current = library->books_head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void deleteBook(Library *library, int book_id) {
    if (!library->books_head) return;

    BookNode *current = library->books_head;
    BookNode *previous = NULL;

    while (current) {
        if (current->book.id == book_id) {
            if (previous) {
                previous->next = current->next;
            } else {
                library->books_head = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void editBook(Library *library, int book_id, Book new_book_data) {
    BookNode *current = library->books_head;

    while (current) {
        if (current->book.id == book_id) {
            new_book_data.id = book_id;
            current->book = new_book_data;
            return;
        }
        current = current->next;
    }
}

void displayBookDetails(Book book) {
    printf("ID: %d\n", book.id);
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Number of Pages: %d\n", book.num_pages);
    printf("Current Page: %d\n", book.current_page);
    printf("Progress: %.2f%%\n", book.progress);
    printf("Review: %s\n", book.review);
    printf("Rating: %.2f\n", book.rating);
    printf("Tags: ");
    for (int i = 0; i < MAX_TAGS && book.tags[i][0]; i++) {
        printf("%s, ", book.tags[i]);
    }
    printf("\n");
}

void updateProgress(Library *library, int book_id, int current_page) {
    // Buscar el libro en la lista de libros usando el book_id
    BookNode *current_book = library->books_head;
    while (current_book) {
        if (current_book->book.id == book_id) {
            break;
        }
        current_book = current_book->next;
    }

    if (!current_book) {
        printf("Libro no encontrado.\n");
        return;
    }

    // Actualizar la página actual
    current_book->book.current_page = current_page;

    // Calcular el progreso
    if (current_book->book.num_pages != 0) {
        current_book->book.progress = (float)current_page / current_book->book.num_pages * 100.0;
        if (current_book->book.progress > 100.0) {
            current_book->book.progress = 100.0;
        }
    } else {
        current_book->book.progress = 0.0;
    }

    printf("Libro '%s' actualizado a la página %d (%.2f%% completo).\n", current_book->book.title, current_page, current_book->book.progress);
}

void searchBooks(Library *library, const char *query, int searchType) {
    BookNode *current = library->books_head;
    int found = 0; // Flag para determinar si se encontró algún libro

    while (current) {
        int match = 0; // Flag para determinar si el libro actual coincide con la consulta
        switch (searchType) {
            case SEARCH_TITLE:
                if (strstr(current->book.title, query) != NULL) {
                    match = 1;
                }
                break;
            case SEARCH_AUTHOR:
                if (strstr(current->book.author, query) != NULL) {
                    match = 1;
                }
                break;
            case SEARCH_TAG:
                for (int i = 0; i < MAX_TAGS && current->book.tags[i][0]; i++) {
                    if (strstr(current->book.tags[i], query) != NULL) {
                        match = 1;
                        break;
                    }
                }
                break;
        }

        if (match) {
            displayBookDetails(current->book);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No books found for the query '%s'.\n", query);
    }
}

void changeBookTags(Library *library, int book_id) {
    BookNode *current = library->books_head;

    // Encuentra el libro por id
    while (current) {
        if (current->book.id == book_id) {
            break;
        }
        current = current->next;
    }

    if (!current) {
        printf("Book not found.\n");
        return;
    }

    printf("Editing tags for '%s'\n", current->book.title);

    int num_tags;
    printf("Enter number of tags (0-%d): ", MAX_TAGS);
    scanf("%d", &num_tags);

    // Reset existing tags
    for (int i = 0; i < MAX_TAGS; i++) {
        current->book.tags[i][0] = '\0';
    }

    for (int i = 0; i < num_tags; i++) {
        printf("Enter tag %d: ", i + 1);
        scanf(" %[^\n]", current->book.tags[i]);
    }

    printf("Tags updated successfully!\n");
}

void listBooks(Library *library) {
    BookNode *current = library->books_head;
    
    if (!current) {
        printf("No books in the library.\n");
        return;
    }
    
    printf("\nListing all books:\n");
    printf("--------------------\n");
    while (current) {
        printf("ID: %d\n", current->book.id);
        printf("Title: %s\n", current->book.title);
        printf("Author: %s\n", current->book.author);
        printf("--------------------\n");
        current = current->next;
    }
}