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

Run brainfuck scripts in the following fashion

```bash
./infinifuck ./path/to/brainfuck/script
```

See how the script is interpreted using

```bash
./infinifuck --parse-only ./path/to/brainfuck/script
```

See more information about the execution using

```bash
./infinifuck --verbose ./path/to/brainfuck/script
```

See more options and help using

```bash
./infinifuck --help
```
