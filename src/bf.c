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
        sizeof(scope_t) * (root -> innersLen));
  }

  root -> inners[*len] = *item;
  (*len)++;
}

void _scope_clean(scope_t* root, int progLen, int innersLen) {
  if(progLen > 0 && root -> inst[progLen - 1] == '\0')
    progLen--;
  
  root -> inst = realloc(root -> inst, sizeof(inst_t) * progLen);
  root -> len = progLen;
  root -> inners = realloc(root -> inners, sizeof(scope_t) * innersLen);
  root -> innersLen = innersLen;
}

int _generator(scope_t* scope, char* buf, int maxSize, int offset, char end, int depth) {
  printf("%*s", depth, "");
  printf("-= start =-\n");
  printf("%*s", depth, "");
  printf("buf: ");
  raw_println(buf, maxSize);

  scope -> inst = malloc(sizeof(inst_t) * maxSize);
  scope -> len = 0;
  scope -> pos = 0;
  scope -> offset = offset;
  scope -> inners = malloc(sizeof(scope_t) * BF_EST_INIT_LOOPS);
  scope -> innersLen = BF_EST_INIT_LOOPS;
  scope -> innersPos = 0;

  int instPos = 0;
  int i = 0;
  int scopes = 0;
  if(maxSize > 0 && buf[0] != '\0') {
    for(;; i++) {
      printf("%*s", depth, "");
      printf("-=-=-\n");
      printf("%*s", depth, "");
      printf("i: %d\n", i);
      printf("%*s", depth, "");
      printf("global offset: %d\n", offset + i);
      scope -> inst[instPos] = buf[i];

      printf("%*s", depth, "");
      printf("(end: %c) inst[%d] = '%c'\n", end, instPos, buf[i]);
      instPos++;

      if((i > 0 || end == '\0') && buf[i] == BF_LPS) {
        scope_t* sub = malloc(sizeof(scope_t));
        printf("%*s", depth, "");
        printf("loop detected (%p)\n", sub);
        printf("%*s", depth, "");
        printf("i: %d\n", i);
        i += _generator(sub, buf + i, maxSize, offset + i, BF_LPF, depth + 2) - 1;

        printf("%*s", depth, "");
        printf("loop finished (%p)\n", sub);
        printf("%*s", depth, "");
        printf("i: %d\n", i);
        
        scope -> inst[instPos] = buf[i];
        printf("%*s", depth, "");
        printf("inst[%d] = '%c'\n", instPos, buf[i]);
        instPos++;

        sub -> parent = scope;
        _scope_append(scope, sub, &scopes);

        printf("%*s", depth, "");
        printf("sub len: %d\n", sub -> len);
      }
      else if(buf[i] == end) {
        printf("%*s", depth, "");
        printf("break\n");
        break;
      }

      if(offset + i > 200) {
        volatile int a = 1 / 0;
      }
    }
  }
  scope -> totalLen = i + 1;

  _scope_clean(scope, instPos, scopes);
  printf("%*s", depth, "");
  printf("-= end (ret: %d) =-\n", scope -> totalLen);
  return scope -> totalLen;
}

int bf_generate(scope_t* scope, char* buf, int maxSize) {
  return _generator(scope, buf, maxSize, 0, '\0', 0);
}

void bf_free(scope_t* scope) {
  free(scope -> inst);
  for(int i = 0; i < scope -> innersLen; i++)
    bf_free(&(scope -> inners[i]));

  free(scope -> inners);
  free(scope);
}

void bf_print(scope_t* scope, int depth) {
  printf("%*sscope {\n", depth, "");
  printf("%*sinstructions: ", depth + 2, "");
  raw_println(scope -> inst, scope -> len);
  printf("%*slen: %d\n", depth + 2, "", scope -> len);
  printf("%*stotal: %d\n", depth + 2, "", scope -> totalLen);
  printf("%*spos: %d\n", depth + 2, "", scope -> pos);
  printf("%*sscope: %d\n", depth + 2, "", scope -> innersPos);
  
  for(int i = 0; i < scope -> innersLen; i++) {
    printf("\n");
    bf_print(&(scope -> inners[i]), depth + 2);
  }

  printf("%*s}\n", depth, "");
}

