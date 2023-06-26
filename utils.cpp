#include <vector>
#include "complex.h"
#include "definitions.h"
#include <iostream>

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

}