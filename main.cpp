#include <iostream>
#include <string>
#include <vector>
#include "utils.h"
#include "complex.h"
#include "definitions.h"

using namespace std;

vector<string> split_input(string input) {
    vector<string>result;
    string word = "";
    for(string::iterator i = input.begin(); i != input.end(); i++) {
        if(*i == ' ') {
            if(word != "") {
                result.push_back(word);
                word = "";
            }
        }
        else {
            word += *i;
        }
    }
    if(word != "") {
        result.push_back(word);
    }
    return result;
}

int main() {
    string input = "";
    STATE state;
    int qubit_size = -1;
    int state_size = -1;
    while(1) {
        cout << "quantumcpp>";
        getline(cin, input);
        vector<string> input_cmd = split_input(input);
        if(input_cmd.size() == 0) {
            continue;
        }
        string command = input_cmd[0];
        if(command == "exit") {
            cout << "Goodbye!" << "\n";
            return 0;
        }
        else if(command == "help") {
            cout << "Available Commands: " << "\n";
            cout << "create <size> - Creates a quantum state of <size> number of qubits." << "\n";
            cout << "gate <X|Z|H|CNOT> ?<control> <target> - Applies an operation to the created state. <control> is an optional parameter for multi-qubit gates." << "\n";
            cout << "peek - View the amplitude and angles of the state." << "\n";
            cout << "exit - Exit the quantum script." << "\n";
            continue;
        }
        else if(command == "create") {
            qubit_size = stoi(input_cmd[1]);
            state_size = pow(2, qubit_size);
            state.resize(state_size);
            fill(state.begin(), state.end(), ComplexNumber());
            state[0] = ComplexNumber(1, 0);
        }
        else if(command == "reset") {
            state.resize(state_size);
            fill(state.begin(), state.end(), ComplexNumber());
            state[0] = ComplexNumber(1, 0);
        }
        else if(command ==  "gate") {
            GATE gate;
            if(input_cmd.size() < 2) {
                cout << "No gate provided, please try again." << "\n";
                continue;
            }
            if(input_cmd.size() < 3) {
                 cout << "No qubit provided, please try again." << "\n";
                continue;
            }
            string gate_type = input_cmd[1];
            int target_pos = -1, control_pos = -1;
            if(gate_type == "CNOT") {
                if(qubit_size < 2) {
                    cout << "Cannot apply CNOT to this state." << "\n";
                    continue;
                }
                control_pos = stoi(input_cmd[2]);
                target_pos = stoi(input_cmd[3]);
                if(control_pos == target_pos) {
                    cout << "Control and Target qubits cannot be the same." << "\n";
                    continue;
                }
            }
            else {
                target_pos = stoi(input_cmd[2]);
            }
            if(target_pos >= qubit_size || control_pos >= qubit_size) {
                cout << "Control and Target qubits are out of range. Please enter a value between 0-" << qubit_size - 1 << "." << "\n";
                continue;
            }
            state = Q_Utils::update_state(state, gate_type, target_pos, control_pos, qubit_size, state_size);
        }
        else if(command == "peek") {
            if(qubit_size == -1) {
                cout << "State not initialised, try creating the state first. create <size>"<< "\n";
                continue;
            }
            int counter = 0;
            for(vector<ComplexNumber>::iterator i = state.begin(); i != state.end(); i++) {
                cout << "|" << counter++ << ">: Amplitude: " << i->get_amplitude() << " Angle: " << i->get_euler_angle() << "\n";
            }
        }
        else {
            cout << "Unknown command, please try again." << "\n";
            continue;
        }
        
    }
    return 0;
}