#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

struct database_header {
    unsigned short version;
    unsigned short employees;
    unsigned int filelength;
};

void print_the_flag() {
  int fd = open("/tmp/flag", O_RDONLY);
  if (fd == -1) {
    perror("open");
    return;
  }

  char buf[256] = {0};
  while (1) {
    int r = read(fd, buf, sizeof(buf)) >= 0;
    if (r < 0) {
      perror("read");
      close(fd);
      return;
    }

    printf("%s", buf);

    if (r < sizeof(buf)) {
      break;
    }
  }
  printf("\n");

  close(fd);
}

int main(void) {
  print_the_flag();
  return 0;
}
