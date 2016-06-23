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
  printf("scope append\n");
  if(*len == root -> innersLen) {
    printf("resize\n");
    root -> innersLen *= 2;
    root -> inners = realloc(root -> inners, 
        sizeof(scope_t) * (root -> innersLen));
  }

  root -> inners[*len] = *item;
  (*len)++;
}

void _scope_clean(scope_t* root, int progLen, int innersLen) {
  printf("scope clean\n");
  root -> inst = realloc(root -> inst, sizeof(inst_t) * progLen);
  root -> len = progLen;
  root -> inners = realloc(root -> inners, sizeof(scope_t) * innersLen);
  root -> innersLen = innersLen;
}

void bf_print(scope_t* scope, int depth) {
  printf("%*sscope {\n", depth, "");
  printf("%*sinstructions: %*s\n", depth + 2, "", scope -> len,
      scope -> inst);
  printf("%*slen: %d\n", depth + 2, "", scope -> len);
  printf("%*spos: %d\n", depth + 2, "", scope -> pos);
  
  for(int i = 0; i < scope -> innersLen; i++) {
    printf("\n");
    bf_print(&(scope -> inners[i]), depth + 2);
  }

  printf("%*s}\n", depth, "");
}

int bf_generate(scope_t* scope, char* buf, int maxSize, char end) {
  printf("start\n");
  scope -> inst = malloc(sizeof(inst_t) * maxSize);
  scope -> len = 0;
  scope -> pos = 0;
  scope -> offset = 0;
  scope -> inners = malloc(sizeof(scope_t) * BF_EST_INIT_LOOPS);
  scope -> innersLen = BF_EST_INIT_LOOPS;

  int i = 0;
  int scopes = 0;
  for(;; i++) {
    printf("buf[%d]: %c\n", i, buf[i]);
    scope -> inst[i] = buf[i];
    printf("copied: %c\n", buf[i]);
    if((i > 0 || end == '\0') && scope -> inst[i] == BF_LPS) {
      scope_t* sub = malloc(sizeof(scope_t));
      printf("loop detected (%p)\n", sub);
      i += bf_generate(sub, buf + i, maxSize, BF_LPF) - 2;
      printf("loop finished (%p)\n", sub);
      sub -> parent = scope;
      _scope_append(scope, sub, &scopes);

      printf("i: %d\n", i);
    }
    else if(scope -> inst[i] == end) {
      printf("break\n");
      break;
    }
  }

  if(end != '\0') i++;
  _scope_clean(scope, i, scopes);
  printf("end\n");
  return i;
}

void bf_free(scope_t* scope) {
  free(scope -> inst);
  for(int i = 0; i < scope -> innersLen; i++)
    bf_free(&(scope -> inners[i]));

  free(scope -> inners);
  free(scope);
}

