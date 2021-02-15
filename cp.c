#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

void
cp(int fd, int fd1)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(fd1, buf, n) != n) {
      printf(1, "cp: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "cp: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, fd1;

  fd = open(argv[1], 0);
  fd1 = open(argv[2], O_CREATE|O_RDWR);

  cp(fd, fd1);
  close(fd);
  close(fd1);

  exit();
}
