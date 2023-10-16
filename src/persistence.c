#include <stdio.h>
#include <stdlib.h>
#include "library.h"

void saveLibraryToFile(Library *library, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }

    BookNode *current_book = library->books_head;
    while (current_book) {
        fwrite(&(current_book->book), sizeof(Book), 1, file);
        current_book = current_book->next;
    }

    LoanNode *current_loan = library->loans_head;
    while (current_loan) {
        fwrite(&(current_loan->loan), sizeof(Loan), 1, file);
        current_loan = current_loan->next;
    }

    fclose(file);
}

void loadLibraryFromFile(Library *library, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error al abrir el archivo para cargar.\n");
        return;
    }

    initializeLibrary(library);  // Asegúrese de que la biblioteca esté vacía antes de cargarla

    Book book;
    while (fread(&book, sizeof(Book), 1, file) == 1) {
        addBook(library, book);
    }

    Loan loan;
    while (fread(&loan, sizeof(Loan), 1, file) == 1) {
        // Aquí deberías tener una función para agregar un préstamo a la biblioteca sin duplicar el ID
    }

    fclose(file);
}
