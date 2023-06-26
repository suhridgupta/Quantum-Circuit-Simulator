#include "complex.h"

ComplexNumber::ComplexNumber() {
    this->r = 0.0;
    this->z = 0.0;
}

ComplexNumber::ComplexNumber(double real, double img) {
    this->r = real;
    this->z = img;
}

double ComplexNumber::get_real() {
    return this->r;
}

double ComplexNumber::get_img() {
    return this->z;
}

double ComplexNumber::get_amplitude() {
    return sqrt(pow(this->r, 2) + pow(this->z, 2));
}

double ComplexNumber::get_euler_angle() {
    return atan(this->z / (0.000001+this->r));      // Delta prevents division by zero
}

ComplexNumber ComplexNumber::conjugate(ComplexNumber a) {
    return ComplexNumber(a.get_real(), -a.get_img());
}

ComplexNumber ComplexNumber::add(ComplexNumber a, ComplexNumber b) {
    double real = a.get_real() + b.get_real();
    double img = a.get_img() + b.get_img();
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::dot(ComplexNumber a, ComplexNumber b) {
    double real = (a.get_real() * b.get_real()) - (a.get_img() * b.get_img());
    double img = (a.get_real() * b.get_img()) + (a.get_img() * b.get_real());
    return ComplexNumber(real, img);
}