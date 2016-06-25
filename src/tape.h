//  tape.h
//  aoneill - 06/25/16

#ifndef __TAPE_H__
#define __TAPE_H_

#include <stdio.h>
#include <stdlib.h>

#define _DIR_NEG 0
#define _DIR_POS 1

#define INIT_TAPE_LEN_NEG 2
#define INIT_TAPE_LEN_POS 4

typedef struct cell_t {
  int id;
  int content;

  // Doubly-linked list
  struct cell_t* neg;
  struct cell_t* pos;
} cell_t;

typedef struct {
  cell_t* origin;
  cell_t* current;
  int pos;
} tape_t;

// Tape functions
void tape_init(tape_t*);
void tape_goto(tape_t*, int);
int tape_get(tape_t*);
void tape_set(tape_t*, int);
void tape_inc(tape_t*);
void tape_dec(tape_t*);
void tape_free(tape_t*);
void tape_print(tape_t*);
int tape_verify(tape_t*);

#endif
