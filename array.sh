#!/bin/sh

INPUTS=("first input" "second input" "third input")

for input in "${INPUTS[@]}"
do
    echo "./c-echo ${input}"
    output=$(./c-echo ${input})
    echo "Output: \"${output}\""
    echo "Input: \"${input}\""
    if [ "${output}" = "${input}" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
    fi
done
