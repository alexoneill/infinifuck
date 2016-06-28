infinifuck
==========

Infinite tape for [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck),
the ever frustrating, minimalist language.

Building
--------

Clone this repository, and do the following

```bash
cd infinifuck/
make all
```

Usage
-----

```bash
$ ./infinifuck --help
usage: ./infinifuck [flags] file
  args:
    file: brainfuck script to execute
  flags:
    -h, --help:       Display this help message
    -p, --parse-only: Parse the script then exit
    -v, --verbose:    Be verbose while running
```

Testing
-------

Run the (simple) test suite with

```bash
./tests/driver.sh ./infinifuck
```
