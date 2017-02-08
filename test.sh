#!/bin/sh

echo foobarbaz > search-file.txt

echo > search-results.txt
./search foo search-file.txt >> search-results.txt
./search bar search-file.txt >> search-results.txt
./search baz search-file.txt >> search-results.txt

echo > expected-results.txt
echo 0 >> expected-results.txt
echo 3 >> expected-results.txt
echo 6 >> expected-results.txt

cmp search-results.txt expected-results.txt
