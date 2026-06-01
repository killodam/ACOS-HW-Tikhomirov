#!/bin/bash

# sum() — sums all arguments using expr
#   outputs the integer sum on success
#   outputs 0 if any argument is non-numeric (expr fails)
#   all error messages are suppressed (redirected to /dev/null)
sum() {
    local result=0
    local tmp
    for arg in "$@"; do
        tmp=$(expr "$result" + "$arg" 2>/dev/null)
        if [ $? -ne 0 ]; then
            echo 0
            return 1
        fi
        result=$tmp
    done
    echo "$result"
}

# Read two lines of space-separated numbers
read -r line1
read -r line2

# Word-splitting is intentional here (no quotes around $line1/$line2)
sum1=$(sum $line1)
sum2=$(sum $line2)

if [ "$sum1" -eq "$sum2" ]; then
    echo "Equal"
else
    echo "Not equal"
fi
