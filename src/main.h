//  main.h
//  aoneill - 06/19/16

#ifndef __MAIN_H__
#define __MAIN_H__

#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "bf.h"
#include "tape.h"

#define BUFLEN 1024

// Flags
static int HELP;
static int PARSE_ONLY;
static int VERBOSE;

static struct option long_options[] = {
  // Long options
  {"help",       no_argument, &HELP,       1},
  {"parse-only", no_argument, &PARSE_ONLY, 1},
  {"verbose",    no_argument, &VERBOSE,    1},
  // Short options
  {"h",          no_argument, 0,          'h'},
  {"p",          no_argument, 0,          'p'},
  {"v",          no_argument, 0,          'v'},
  {0, 0, 0, 0}
};

int usage(int, char**);
int main(int, char**);

#endif
