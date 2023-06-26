#pragma once
#include <vector>
#include <math.h>
#include "complex.h"
#include "definitions.h"

namespace Q_Utils {
    GATE I {
            { ComplexNumber(1, 0), ComplexNumber() },
            { ComplexNumber(), ComplexNumber(1, 0) }
            };
    GATE X {
            { ComplexNumber(), ComplexNumber(1, 0) },
            { ComplexNumber(1, 0), ComplexNumber() }
            };
    GATE Z {
            { ComplexNumber(1, 0), ComplexNumber() },
            { ComplexNumber(), ComplexNumber(-1, 0)}
            };
    GATE H {
            { ComplexNumber(1/sqrt(2), 0), ComplexNumber(1/sqrt(2), 0)  },
            { ComplexNumber(1/sqrt(2), 0), ComplexNumber(-1/sqrt(2), 0) }
            };
    STATE inner_product(GATE, STATE);
}