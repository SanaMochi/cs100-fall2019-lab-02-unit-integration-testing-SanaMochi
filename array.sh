#!/bin/sh

INPUTS=("first input" "second input" "third input")

for input in "${INPUTS[@]}"
do
    echo "./c-echo ${input}"
    ./c-echo ${input}
done
