//  util.c
//  aoneill - 06/23/16

#include "util.h"

void raw_print(char* buf, int len) {
  // Print every character up to the length
  for(int i = 0; i < len; i++)
    if(0x20 <= buf[i] && buf[i] <= 0x7F)
      printf("%c", buf[i]);
    else
      // Print the int equivalent
      printf("\\%d", (int) buf[i]);
}

void raw_println(char* buf, int len) {
  // Print with a carriage return
  raw_print(buf, len);
  printf("\n");
}
