#ifndef BOOK_H
#define BOOK_H

#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100
#define MAX_REVIEW_LENGTH 500
#define MAX_TAGS 10
#define MAX_TAG_LENGTH 50

typedef struct
{
  int id;
  char title[MAX_TITLE_LENGTH];
  char author[MAX_AUTHOR_LENGTH];
  int num_pages;
  int current_page;
  float progress;
  char review[MAX_REVIEW_LENGTH];
  float rating;
  char tags[MAX_TAGS][MAX_TAG_LENGTH];
} Book;

#endif // BOOK_H
