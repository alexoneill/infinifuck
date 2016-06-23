//  main.c
//  aoneill - 06/19/16

#include "main.h"

int usage(int argc, char** argv) {
  printf("usage: %s file\n", argv[0]);
  printf("  file: brainfuck scipt to execute\n");

  return 1;
}

void raw_print(char* buf, int len) {
  for(int i = 0; i < len; i++)
    if(0x20 <= buf[i] && buf[i] <= 0x7F)
      printf("%c", buf[i]);
    else
      printf("\\%d", (int) buf[i]);

  printf("\n");
}

int main(int argc, char** argv) {
  if(argc != 2)
    return usage(argc, argv);

  char* filename = argv[1];
  int fd = open(filename, O_RDONLY);
  if(fd == -1) {
    printf("error: Could not open %s. (errno %d)\n", filename, errno);
    return 0;
  }

  // Get number of bytes
  long fileLen = lseek(fd, 0L, SEEK_END);
  lseek(fd, 0L, SEEK_SET);

  char* prog = malloc(sizeof(char) * (fileLen + 1));
  char buf[BUFLEN];
  int len = 0;
  int pos = 0;
  while((len = read(fd, buf, BUFLEN))) {
    for(int i = 0; i < len; i++){
      if(bf_char(buf[i])) {
        prog[pos] = buf[i];
        pos++;
      }
    }
  }
  prog[pos] = '\0';
  pos++;
  prog = realloc(prog, sizeof(char) * pos);

  printf("Raw:\n");
  raw_print(prog, pos);
  printf("=====================\n");

  scope_t scope;
  len = bf_generate(&scope, prog, pos, '\0');

  printf("=====================\n");
  printf("Info:\n");
  printf("len: %d\n", len);
  bf_print(&scope, 0);

  return 0;
}
