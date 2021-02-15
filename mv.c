#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


void mv(char *fd, char *fd1)
{
    link(fd, fd1);
    unlink(fd);
}

int
main(int argc, char *argv[])
{

  mv(argv[1], argv[2]);

  exit();
}
