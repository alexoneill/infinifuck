//  util.c
//  aoneill - 06/23/16

#include "util.h"

void raw_print(char* buf, int len) {
  for(int i = 0; i < len; i++)
    if(0x20 <= buf[i] && buf[i] <= 0x7F)
      printf("%c", buf[i]);
    else
      printf("\\%d", (int) buf[i]);
}

void raw_println(char* buf, int len) {
  raw_print(buf, len);
  printf("\n");
}
