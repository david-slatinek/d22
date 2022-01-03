#!/bin/bash

make clean >>/dev/null
make compile >>/dev/null

for file in ./*.in; do
    echo "Running: $file"

    for _ in {1..10}; do
        time ./main "$file"
        echo
    done
    printf '\n%.0s' {1..5}
done

make clean >>/dev/null
