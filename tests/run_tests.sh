#!/bin/bash
set -e

echo "Running tests..."

for file in tests/inputs/*.txt
do
    name=$(basename "$file" .txt)
    ./app "$file" > output.txt
    diff output.txt tests/expected/"$name".out
    echo "Test $name passed"
done

echo "All tests passed"
