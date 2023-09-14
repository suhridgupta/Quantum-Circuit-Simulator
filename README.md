# Quantum C++
Script-based simulation of a quantum computer using C++.

## Instructions to run
make all && ./quantumcpp.out

## Example - Deutsch Algorithm
[Circuit Diagram](https://qui.science.unimelb.edu.au/circuits/6483f94e06a5b100126eaf5a)
#### Quantum Script Steps:
```
create 2
gate X 1
gate H 0
gate H 1
gate X 1
gate H 0
gate H 1
peek
```
