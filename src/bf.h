//  bf.h
//  aoneill - 06/19/16

#ifndef __BF_H__
#define __BF_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BF_FWD 0x3E // > Forward
#define BF_BAK 0x3C // < Backwards
#define BF_INC 0x2B // + Increment
#define BF_DEC 0x2D // - Decrement
#define BF_OUT 0x2E // . Output byte
#define BF_INP 0x2C // , Input byte
#define BF_LPS 0x5B // [ Loop start
#define BF_LPF 0x5D // ] Loop finish

#define BF_EST_INIT_LOOPS 4

typedef char inst_t;

typedef struct scope_t {
  inst_t* inst;
  int len;
  int pos;

  int offset;
  struct scope_t* parent;
  struct scope_t* inners;
  int innersLen;
} scope_t;

int bf_char(char);
int bf_syntax(char* buf, int len);
int bf_generate(scope_t*, char*, char);
void bf_free(scope_t*);

#endif
