//  main.c
//  aoneill - 06/19/16

#include "main.h"

int usage(int argc, char** argv) {
  printf("usage: %s [flags] file\n", argv[0]);
  printf("  args:\n");
  printf("    file: brainfuck script to execute\n");
  printf("  flags:\n");
  printf("    -h, --help:       Display this help message\n");
  printf("    -p, --parse-only: Parse the script then exit\n");
  printf("    -v, --verbose:    Be verbose while running\n");

  return 1;
}

int parseArgs(int argc, char** argv, int* start) {
  if(argc < 2)
    return usage(argc, argv);

  int optIndex = 0;
  int optCode = 0;
  while((optCode = getopt_long(argc, argv, "hpv",
                               long_options, &optIndex)) != -1) {
    switch(optCode) {
      // Handle long options
      case 0: break;

      // Parse only
      case 'h':
        HELP = 1;
        break;

      // Parse only
      case 'p':
        PARSE_ONLY = 1;
        break;

      // Verbose
      case 'v':
        VERBOSE = 1;
        break;

      // Error 
      case '?':
        break;

      default:
        return usage(argc, argv);
    }
  }

  if(HELP == 1 || optind == argc)
    return usage(argc, argv);

  *start = optind;
  return 0;
}

int main(int argc, char** argv) {
  // Parse arguments
  int start;
  int status = 0;
  if((status = parseArgs(argc, argv, &start)) != 0)
    return status;

  // Open script
  char* filename = argv[start];
  int fd = open(filename, O_RDONLY);
  if(fd == -1) {
    printf("error: Could not open %s. (errno %d)\n", filename, errno);
    return 0;
  }

  // Get number of bytes
  long fileLen = lseek(fd, 0L, SEEK_END);
  lseek(fd, 0L, SEEK_SET);

  // Read into memory
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
  // Null terminate
  prog[pos] = '\0';
  pos++;

  // Remove extra space, parse scope
  scope_t scope;
  prog = realloc(prog, sizeof(char) * pos);
  len = bf_generate(&scope, prog, pos);

  // Helpful for testing
  if(PARSE_ONLY) {
    bf_print(&scope, 0);
    return 0;
  }

  // Initialize tape
  tape_t tape;
  tape_init(&tape);

  // Cleanup
  tape_free(&tape);
  bf_free(&scope);
  free(prog);

  return 0;
}
