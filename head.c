#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
head(int fd, char *name)
{
  int i, n;
  int l, w, c, inword;
  char printBuf[512];

  l = w = c = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    int idx = 0;
    for(i=0; i<n; i++){
      //printf(1, "%c", buf[i]);
      c++;
      if(l == 10)
        exit();
      if(buf[i] == '\n') {
        printf(1, "%s\n", printBuf);
        memset(&printBuf[0], 0, sizeof(printBuf));
        idx = 0;
        l++;
      }
      else {
        printBuf[idx] = buf[i];
        printBuf[idx+1] = '\0';
        idx = idx + 1;
      }
      if(strchr(" \r\t\n\v", buf[i])){
        inword = 0;
      }
      else if(!inword){
        w++;
        inword = 1;
      }
      //printf(1, "%c", buf[i]);
    }
  }
  if(n < 0){
    printf(1, "wc: read error\n");
    exit();
  }
  printf(1, "%d %d %d %s\n", l, w, c, name);
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    head(0, "");
    exit();
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "wc: cannot open %s\n", argv[i]);
      exit();
    }
    head(fd, argv[i]);
    close(fd);
  }
  exit();
}
