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
    int state_size = 0;
    while(1) {
        cout << "quantumcpp>";
        getline(cin, input);
        vector<string> input_cmd = split_input(input);
        if(input_cmd[0] == "exit") {
            cout << "Goodbye!" << "\n";
            return 0;
        }
        if(input_cmd[0] == "create_state" || input_cmd[0] == "clear_state") {
            state = {ComplexNumber(1,0), ComplexNumber()};         // One qubit state
        }
        if(input_cmd[0] ==  "gate") {
            GATE gate;
            if(input_cmd.size() < 2) {
                cout << "No gate provided, please try again." << "\n";
                continue;
            }
            else if(input_cmd[1] == "X") {
                gate = Q_Utils::X;
            }
            else if(input_cmd[1] == "Z") {
                gate = Q_Utils::Z;
            }
            else if(input_cmd[1] == "H") {
                gate = Q_Utils::H;
            }
            else {
                cout << "Unknown gate provided, please try again." << "\n";
                continue;
            }
            state = Q_Utils::inner_product(gate, state);
        }
        if(input_cmd[0] == "peek") {
            int counter = 0;
            for(vector<ComplexNumber>::iterator i = state.begin(); i != state.end(); i++) {
                cout << "|" << counter++ << ">: Amplitude: " << i->get_amplitude() << " Angle: " << i->get_euler_angle() << "\n";
            }
        }
        
    }
    return 0;
}