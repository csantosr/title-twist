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
        printf("%s ", book.tags[i]);
    }
    printf("\n");
}
