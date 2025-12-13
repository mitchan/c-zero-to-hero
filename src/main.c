#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char *argv[]) {
  printf("usage: %s -n -f <database file>\n", argv[0]);
  printf("\t -n - creates a new file\n");
  printf("\t -f - (required) path to database file\n");
}

int main(int argc, char *argv[]) { 
  char *filepath = NULL;
  bool newfile = false;
  int c = 0;

  while ((c = getopt(argc, argv, "nf:")) != -1) {
    switch (c) {
      case 'n':
        newfile = true;
        break;

      case 'f':
        filepath = optarg;
        break;

      case '?':
        printf("unknown option -%c\n", c);
        break;

      default:
        return -1;
    }
  }

  if (filepath == NULL) {
    printf("Filepath is a required argument\n");
    print_usage(argv);
    return -1;
  }

  int db_fd = -1;

  if (newfile) {
    db_fd = create_db_file(filepath);
    if (db_fd ==  STATUS_ERROR) {
      printf("unable to create db file\n");
      return -1;
    }
  } else {
    db_fd = open_db_file(filepath);
    if (db_fd ==  STATUS_ERROR) {
      printf("unable to open db file\n");
      return -1;
    }
  }

  printf("Newfile: %d\n", newfile);
  printf("Filepath: %s\n", filepath);

  return 0;
}
