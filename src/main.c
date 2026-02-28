#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char *argv[]) {
  printf("Usage: %s -n -f <database file>\n", argv[0]);
  printf("\t -n - create a new db file\n");
  printf("\t -f - (required) path to db file\n");
}

int main(int argc, char *argv[]) { 
  bool newfile = false;
  char *filepath = NULL;
  int c;

  struct dbheader_t *db_header = NULL;

  int dbfd = -1;

  while ((c = getopt(argc, argv, "nf:")) != -1) {
    switch(c) {
      case 'n':
        newfile = true;
        break;

      case 'f':
        filepath = optarg;
        break;

      case '?':
        printf("Unknown option: %c", c);
        break;

      default:
        return -1;
    }
  }

  if (filepath == NULL) {
    printf("filepath is a required argument\n");
    print_usage(argv);
    return 0;
  }

  if (newfile) {
    dbfd = create_db_file(filepath);
    if (dbfd == STATUS_ERROR) {
      printf("unable to create db file.\n");
      return -1;
    }

    if (create_db_header(&db_header) == STATUS_ERROR) {
      printf("Failed to create db header.\n");
      return -1;
    }
  } else {
    dbfd = open_db_file(filepath);
    if (dbfd == STATUS_ERROR) {
      printf("unable to open db file.\n");
      return -1;
    }

    if (validate_db_header(dbfd, &db_header) == -1) {
      printf("Invalid db header.\n");
      return -1;
    }
  }

  output_file(dbfd, db_header);

  close(dbfd);

  printf("Success!\n");
}
