#include "library.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

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

void loanBook(Library *library, int book_id, char *friend_nickname) {
    // Buscar el libro en la lista de libros
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

    // Crear un nuevo préstamo
    LoanNode *new_loan = (LoanNode *)malloc(sizeof(LoanNode));
    if (!new_loan) {
        printf("Error al asignar memoria para el nuevo préstamo.\n");
        return;
    }

    // Asignar los detalles del préstamo
    new_loan->loan.book_id = book_id;
    strncpy(new_loan->loan.friend_nickname, friend_nickname, MAX_NICKNAME_LENGTH - 1);
    new_loan->loan.friend_nickname[MAX_NICKNAME_LENGTH - 1] = '\0';  // Asegurarse de que es null-terminado

    time_t now;
    time(&now);
    new_loan->loan.loan_date = now;
    new_loan->loan.return_date = 0; // No se ha devuelto aún
    new_loan->loan.status = ACTIVE;
    new_loan->next = NULL;

    // Añadir el nuevo préstamo a la lista de préstamos
    if (!library->loans_head) {
        library->loans_head = new_loan;
    } else {
        LoanNode *current_loan = library->loans_head;
        while (current_loan->next) {
            current_loan = current_loan->next;
        }
        current_loan->next = new_loan;
    }

    printf("Libro %s prestado a %s.\n", current_book->book.title, friend_nickname);
}

void returnBook(Library *library, int book_id) {
    // Buscar el préstamo en la lista de préstamos basado en el book_id
    LoanNode *current_loan = library->loans_head;
    while (current_loan) {
        if (current_loan->loan.book_id == book_id && current_loan->loan.status == ACTIVE) {
            break;
        }
        current_loan = current_loan->next;
    }

    if (!current_loan) {
        printf("Préstamo no encontrado o ya devuelto.\n");
        return;
    }

    // Cambiar el estado del préstamo a "devuelto"
    current_loan->loan.status = RETURNED;

    // Registrar la fecha de devolución
    time_t now;
    time(&now);
    current_loan->loan.return_date = now;

    printf("Libro con ID %d registrado como devuelto.\n", book_id);
}