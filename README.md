# Quantum C++
Script-based simulation of a quantum computer using C++.

## Instructions to run
make compile && make run

## Examples
### Deutsch Algorithm
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
### Grover's Algorithm
[Circuit Diagram](https://qui.science.unimelb.edu.au/circuits/64262ff1d5f05000545920b2)
#### Quantum Script Steps:
```
create 3
gate H 0
gate H 1
gate H 2
gate X 1
gate H 2
gate TOFF 0 1 2
gate H 2
gate X 1
gate H 0
gate H 1
gate H 2
gate X 0
gate X 1
gate X 2
gate Z 0 1 2
gate X 0
gate X 1
gate X 2
gate H 0
gate H 1
gate H 2
peek
```
