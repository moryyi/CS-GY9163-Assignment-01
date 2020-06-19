make clean
make cleanall
make afl
afl-fuzz -i ./afl-tests/testcases/ -o ./afl-tests/findings/ ./afl_test @@