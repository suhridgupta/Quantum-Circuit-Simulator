#include <vector>
#include <string>
#include "complex.h"
#include "definitions.h"
#include <iostream>

using namespace std;

namespace Q_Utils {
    
    STATE inner_product(GATE gate, STATE state) {
        STATE result;
        for(GATE::iterator i = gate.begin(); i != gate.end(); i++) {
            ComplexNumber sum = ComplexNumber();
            for(STATE::iterator j = i->begin(), k = state.begin(); j != i->end(), k != state.end(); j++, k++) {
                ComplexNumber product = ComplexNumber::dot(*j, *k);
                sum = ComplexNumber::add(product, sum);
            }
            result.push_back(sum);
        }
        return result;
    }

    GATE construct_gate(string gate_type, int target_pos, int control_pos, int qubit_size, int state_size) {
        GATE gate (state_size, STATE (state_size, ComplexNumber() ));
        for(int i = 0; i < state_size; i++) {
            int target_qubit_value = 1 & (i >> (qubit_size - target_pos - 1));
            // Calculates the corresponding target qubit toggle position
            // For example, if the given state is |00> and the target_pos is 0, target_toggle returns |10>
            // Use this to modify the cells in the gates for one bit operations
            int target_toggle = i ^ (1 << (qubit_size - target_pos - 1));
            if(gate_type == "X") {
                int row = i;
                int col = target_toggle;
                gate[row][col] = ComplexNumber(1, 0);
            }
            else if(gate_type == "Z") {
                gate[i][i] = target_qubit_value ? ComplexNumber(-1, 0) : ComplexNumber(1, 0);
            }
            else if(gate_type == "H") {
                if(target_qubit_value) {
                    gate[i][target_toggle] = ComplexNumber(1/sqrt(2), 0);
                    gate[i][i] = ComplexNumber(-1/sqrt(2), 0);
                }
                else {
                    gate[i][target_toggle] = ComplexNumber(1/sqrt(2), 0);
                    gate[i][i] = ComplexNumber(1/sqrt(2), 0);
                }
            }
            else if(gate_type == "CNOT") {
                int control_qubit_value = 1 & (i >> (qubit_size - control_pos - 1));
                if(control_qubit_value) {
                    gate[i][target_toggle] = ComplexNumber(1, 0);
                }
                else {
                    gate[i][i] = ComplexNumber(1, 0);
                }
            }

        }
        return gate;
    }

    STATE update_state(STATE state, string gate_type, int target_pos, int control_pos, int qubit_size, int state_size) {
        GATE gate = construct_gate(gate_type, target_pos, control_pos, qubit_size, state_size);
        return inner_product(gate, state);
    }

}