#pragma once
#include <vector>
#include <string>
#include "complex.h"
#include "definitions.h"

using namespace std;

namespace Q_Utils {
    STATE inner_product(GATE, STATE);
    GATE construct_gate(string, int, int, int, int);
    STATE update_state(STATE, string, int, int, int, int);
}