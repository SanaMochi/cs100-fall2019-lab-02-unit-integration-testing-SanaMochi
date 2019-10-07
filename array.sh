#!/bin/sh

INPUTS=("first input" "second input" "third input")

echo "Executing ./c-echo ${INPUTS[2]}"
./c-echo ${INPUTS[2]}
echo "Executing ./c-echo ${INPUTS[1]}"
./c-echo ${INPUTS[1]}
echo "Executing ./c-echo ${INPUTS[0]}"
./c-echo ${INPUTS[0]}
