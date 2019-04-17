#!/bin/bash
make
for i in {1..10}; do ./a.out; done
echo done
