//  bf.c
//  aoneill - 06/19/16

#include "bf.h"

int bf_char(inst_t inst) {
  switch(inst) {
    case BF_FWD:
    case BF_BAK:
    case BF_INC:
    case BF_DEC:
    case BF_OUT:
    case BF_INP:
    case BF_LPS:
    case BF_LPF:
      return 1;
    default:
      return 0;
  }
}

void _scope_append(scope_t* root, scope_t* item, int* len) {
  if(*len == root -> innersLen) {
    root -> innersLen *= 2;
    root -> inners = realloc(root -> inners, 
        sizeof(inst_t) * (root -> innersLen));
  }

  root -> inners[*len] = *item;
  (*len)++;
}

void _scope_clean(scope_t* root, int finalLen) {
  root -> inners = realloc(root -> inners, sizeof(inst_t) * finalLen);
  root -> innersLen = finalLen;
}

void bf_print(scope_t* scope, int depth) {
  printf("%*sscope {\n", depth, "  ");
  printf("%*sinstructions: %*s\n", depth + 1, "  ", scope -> len,
      scope -> inst);
  printf("%*slen: %d\n", depth, "  ", scope -> len);
  printf("%*spos: %d\n", depth, "  ", scope -> pos);
  
  for(int i = 0; i < scope -> innersLen; i++) {
    printf("\n");
    bf_print(&(scope -> inners[i]), depth + 1);
  }

  printf("%*s}\n", depth, "  ");
}

int bf_generate(scope_t* scope, char* buf, char end) {
  scope -> inst = malloc(sizeof(inst_t) * BF_EST_INIT_LOOPS);
  scope -> len = 0;
  scope -> pos = 0;
  scope -> offset = 0;

  int i = 0;
  int scopes = 0;
  for(;; i++) {
    scope -> inst[i] = buf[i];
    if(scope -> inst[i] == BF_LPS) {
      scope_t* sub = malloc(sizeof(scope_t));
      i += bf_generate(sub, (scope -> inst) + i, BF_LPF);
      sub -> parent = scope;
      _scope_append(scope, sub, &scopes);
    }
    else if(scope -> inst[i] == end) {

      break;
    }
  }

  i++;
  scope -> len = i;
  _scope_clean(scope, scopes);
  return i;
}

void bf_free(scope_t* scope) {
  free(scope -> inst);
  for(int i = 0; i < scope -> innersLen; i++)
    bf_free(&(scope -> inners[i]));

  free(scope -> inners);
  free(scope);
}

