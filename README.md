# CS-GY9163-Assignment-01

[![Build Status](https://travis-ci.org/qb1ng/CS-GY9163-Assignment-01.svg?branch=master)](https://travis-ci.org/qb1ng/CS-GY9163-Assignment-01)

## How to build and use

1. Run `make` to generate target program `spell_check`
2. Execute the program : `spell_check <text-file> <dictionary-file>`

## How to test

1. To test, run `make test`
2. `build-essential` and `check` are required

## AFL fuzzing test

1. To fuzz this program with AFL, run `make afl`
2. `afl` is required
3. This `make` command switches the normal `gcc` to `afl-gcc` provided by *AFL* fuzzer