#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

struct database_header {
    unsigned short version;
    unsigned short employees;
    unsigned int filelength;
};

int main(void) {
  int fd = open("./my-db.db", O_RDONLY);
  if (fd == -1) {
    perror("open");
    return -1;
  }

  struct database_header head = {0};
  if (read(fd, &head, sizeof(head)) != sizeof(head)) {
    perror("read");
    close(fd);
    return -1;
  }

  printf("Database version: %d\n", head.version);
  printf("Employees: %d\n", head.employees);
  printf("Size: %d\n", head.filelength);

  struct stat fdStat = {0};
  if (fstat(fd, &fdStat) < 0) {
    perror("fstat");
    close(fd);
    return -1;
  }

  printf("size: %lu\n", fdStat.st_size);
  if (fdStat.st_size != head.filelength) {
    printf("HACKER DETECTED!\n");
    close(fd);
    return -1;
  }

  return 0;
}
