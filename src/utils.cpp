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
        for(int state_iteration = 0; state_iteration < state_size; state_iteration++) {
            // Checks if the target qubit is the selected row value or not
            // For example, if the current state_iteration is 0b11 and the target_pos is 0b01, then the target qubit is set
            // Another example, if the current state_iteration is 0b10 and the target_pos is 0b01, then the target qubit is not set
            // This is used to determine whether or not to modify the cell values for one bit operations
            bool target_qubit_set = (state_iteration & target_pos) == target_pos;
            // Calculates the corresponding target qubit toggle position
            // For example, if the current state is 0b00 and the target_pos is 0b10, target_toggle returns |10>
            // Use this to modify the cells in the gates for one bit operations
            int target_toggle = state_iteration ^ target_pos;
            // Checks if the control qubits are all set or not
            // If the gate does not have control qubits, it defaults to true
            bool control_qubits_set = control_pos == -1 ? true : (control_pos & state_iteration) == control_pos;

            if(gate_type == "X") {
                int row = state_iteration;
                int col = target_toggle;
                if(control_qubits_set) {
                    gate[state_iteration][target_toggle] = ComplexNumber(1, 0);
                }
                else {
                    gate[state_iteration][state_iteration] = ComplexNumber(1, 0);
                }
            }
            else if(gate_type == "Z") {
                gate[state_iteration][state_iteration] = control_qubits_set && target_qubit_set ? ComplexNumber(-1, 0) : ComplexNumber(1, 0);
            }
            else if(gate_type == "H") {
                if(control_qubits_set) {
                    if(target_qubit_set) {
                        gate[state_iteration][target_toggle] = ComplexNumber(1/sqrt(2), 0);
                        gate[state_iteration][state_iteration] = ComplexNumber(-1/sqrt(2), 0);
                    }
                    else {
                        gate[state_iteration][target_toggle] = ComplexNumber(1/sqrt(2), 0);
                        gate[state_iteration][state_iteration] = ComplexNumber(1/sqrt(2), 0);
                    }
                }
                else {
                    gate[state_iteration][state_iteration] = ComplexNumber(1, 0);
                }
            }
            else if(gate_type == "CNOT" || gate_type == "TOFF") {
                if(control_qubits_set) {
                    gate[state_iteration][target_toggle] = ComplexNumber(1, 0);
                }
                else {
                    gate[state_iteration][state_iteration] = ComplexNumber(1, 0);
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