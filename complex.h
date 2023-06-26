#pragma once
#include <math.h>

class ComplexNumber {
private:
    double r;
    double z;

public:
    ComplexNumber();
    ComplexNumber(double, double);
    double get_real();
    double get_img();
    double get_amplitude();
    double get_euler_angle();
    static ComplexNumber conjugate(ComplexNumber);
    static ComplexNumber add(ComplexNumber, ComplexNumber);
    static ComplexNumber dot(ComplexNumber, ComplexNumber);
};